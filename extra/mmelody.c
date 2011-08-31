/** @file   mmelody.c
    @author M. P. Hayes, UCECE
    @date   20 April 2007
    @brief  Play simple melodies.
*/
#include "system.h"
#include "mmelody.h"


/* By default notes are in the scale C4 -> C5.
   Note the first 12 frets on a six string guitar covers 3 octaves
   from the pitch E2 (82.41 Hz) to the pitch E5 (659.26 Hz).

   Tunes are specified using the notation C4C5F4G4C4 but for brevity
   this can be simplified to C4C5F4GC where the previously specified
   octave number persists.  A problem with this notation is the
   verbosity when we have something like B2C3B2C3.  Most melodies will
   only require 2 and 3 at the most octaves.  The ABC music notation
   uses CDEFGABcdefgabc'd'e'f'g'a'b'c' to denote 3 octaves from C2 to
   C5?  This uses numbers to indicate note duration, for example, C2
   denotes a C of twice the standard duration.

   By default notes are crotchets (quarter notes) and tempos are
   defined in beats per minute.  If we assume 4/4 time, then each beat
   has a quarter-note duration.

   The note duration can be halved with a comma suffix, e.g., A,

   The note duration can be extended by a half with a dot suffix, e.g., A.

   The note duration can be doubled with a slash suffix, e.g., A/

   The note duration can be trebled with two slash suffixes, e.g., A//
   (this can be continued to lengthen the note).

   If there are lots of quavers (eighth notes), then the default note
   duration can be switched using *8.  *4 returns to quarter note timing.

   Rests are specified with a space character.  The timing modifiers ,
   . and / can be used.

   <ABC> is equivalent to ABCABC

   <ABC>3 is equivalent to ABCABCABC
   
   ABC: performs an infinite repeat of ABC

   <ABC]1DE]2FG> represents ABCDEABCFG where ]n denotes alternate
   endings.  

   A+ sounds an octave higher

   A- sounds an octave lower

   @120 sets the tempo to 120 beats per minute

   This could be made a lot more flexible but the orginal
   implementation had a tight memory constraint.  Possible extensions:

   * For emphasis perhaps use ^ to indicate louder, for example, C^.
     Similarly, to make a note quieter it could have a v suffix.

   * Use | for bar markers; these can be ignored.
   
   * Time signatures.

   * Nested loops, e.g., <AB<ABC>>

   * sixteenth notes?  Perhaps A,,

   * Perhaps lower case for eighth notes.
*/

enum {MMELODY_SCALE_SIZE = 12};


static void
mmelody_ticker_set (mmelody_t mmelody)
{
    uint16_t speed;

    /* Notes per four minutes.  */
    speed = mmelody->speed * mmelody->note_fraction;

    /* This is the duration of an eighth-note.

       With note_fraction = 4, speed = 50, and poll_rate of 200 this
       gives a result of 120.  */
    mmelody->note_ticks = mmelody->poll_rate * 60 * 2 / speed;
}


static void
mmelody_note_on (mmelody_t mmelody, mmelody_note_t note, uint8_t duration)
{
    /* The duration is in terms of eighth notes.  */

    mmelody->play_callback (mmelody->play_callback_data, note,
                            mmelody->volume);
    mmelody->note = note;

    /* Determine ticks between sounding notes (this needs to be a
       minimum of 1).  */
    mmelody->ticks2 = mmelody->note_ticks / 16;
    if (!mmelody->ticks2)
        mmelody->ticks2 = 1;

    /* Determine ticks before turning the note off.  */
    mmelody->ticks1 = mmelody->note_ticks * duration - mmelody->ticks2;
}


static void
mmelody_note_off (mmelody_t mmelody)
{
    mmelody->play_callback (mmelody->play_callback_data, 
                            mmelody->note, 0);
    mmelody->note = 0;
}


/* Specify the default note length in fractions of a measure (bar).
   A value of 4 is the default which makes each note a quarter note.  */
static void 
mmelody_note_fraction_set (mmelody_t mmelody, uint8_t note_fraction)
{
    mmelody->note_fraction = note_fraction;    
    mmelody_ticker_set (mmelody);
}


static mmelody_note_t
mmelody_char_to_note (uint8_t ch)
{
    /* A = 9, B = 11, C = 0, D = 2, E = 4, F = 5, G = 7  */
    static const mmelody_note_t const lookup[] = {9, 11, 0, 2, 4, 5, 7};

    return lookup[ch - 'A'];
}


/* Scan next part of melody until a note or end of melody is found.  */
static const char *
mmelody_scan (mmelody_t mmelody, const char *str)
{
    while (1)
    {
        uint8_t num;
        char cmd;
        char modifier;
        bool have_hash;
        bool have_num;
        mmelody_note_t note = 0;
        uint8_t duration = 1;
        
        /* Play rest at end of melody.  */
        if (! *str)
        {
            mmelody_note_off (mmelody);
            return str;
        }

        cmd = *str++;

        have_hash = *str == '#';
        if (have_hash)
            str++;

        modifier = 0;
        if (*str == '+' || *str == '-')
            modifier = *str++;

        have_num = 0;
        num = 0;
        while (*str >= '0' && *str <= '9')
        {
            have_num = 1;
            num = num * 10 + *str++ - '0';
        }

        switch (cmd)
        {
            /* Repeat sequence from start.  */
        case ':':
            str = mmelody->start;
            continue;

            /* Define start of loop.  */
        case '<':
            /* We could implement a small stack to allow nested
               loops.  */
            mmelody->loop_start = str;
            mmelody->loop_count = 0;
            continue;
            
            /* Loop.  */
        case '>':
            mmelody->loop_count++;
            if (!num)
                num = 2;

            if (mmelody->loop_count < num)
            {
                /* Jump to start of loop.  If no start of loop symbol,
                   jump to start.  */
                str = mmelody->loop_start;
                if (!str)
                    str = mmelody->start;
            }
            continue;

            /* Alternate endings.  */
        case '[':
            if (mmelody->loop_count == num - 1)
                continue;

            /* Skip to next alternate ending, the end of loop, or end of
               melody.  */
            while (*str && *str != '[' && *str != '>')
                str++;
            continue;

        case '*':
            if (num)
                mmelody_note_fraction_set (mmelody, num);
            continue;

        case '@':
            if (num)
                mmelody_speed_set (mmelody, num);
            continue;

        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
            note = mmelody_char_to_note (cmd);

            if (have_hash)
                note++;

            if (have_num)
                mmelody->octave = num;

            if (modifier == '+')
                note += MMELODY_SCALE_SIZE;

            if (modifier == '-')
                note -= MMELODY_SCALE_SIZE;

            /* Convert note to MIDI note number.  */
            note += (mmelody->octave + 1) * MMELODY_SCALE_SIZE;

            /* Fall through.  */
        case ' ':

            while (*str == '/')
            {
                duration++;
                str++;
            }
            if (*str == '.')
            {
                /* Dotted quarter note.  */
                duration += duration * 2;
                str++;
            }
            else if (*str == ',')
            {
                /* Eighth note.  */
                str++;
                /* What about dotted eighth notes?  */
            }
            else
            {
                /* Quarter note.  */
                duration *= 2;
            }

            mmelody_note_on (mmelody, note, duration);
            return str;
            break;
            
        default:
            return str;
            break;
        }
    }
    return str;
}


void 
mmelody_play (mmelody_t mmelody, const char *str)
{
    mmelody->cur = mmelody->start = str;
    mmelody->loop_start = 0;
    mmelody->loop_count = 0;
    mmelody->octave = MMELODY_OCTAVE_DEFAULT;
    /* Default to quarter notes.  */
    mmelody_note_fraction_set (mmelody, 4);
    /* Stop what is currently sounding.  */
    mmelody_note_off (mmelody);

    mmelody->ticks1 = 0;
    mmelody->ticks2 = 1;
}


/* Set (base) speed in beats per minute (BPM).  */
void 
mmelody_speed_set (mmelody_t mmelody, mmelody_speed_t speed)
{
    /* With 8 bits for the tempo (in bpm), the max tempo is 255 bpm.
       This corresponds to 4.25 beats per second.  If the minimum time
       to release a note is 1 / 8 of a quarter note, then we need to
       poll at a rate of at least 4.25 * 8 = 34 times per second.

       The duration of a beat varies with the time signature:
       2/2 : minum (half note)
       4/4 : crotchet (quarter note)
       6/8, 9/8, 12/8 : dotted crotchet (one and a half quarter notes)

       Currently, there is no time signature support so we assume 4/4.
       This means a beat is quarter note and a bar is four quarter notes.
    */
    mmelody->speed = speed;
    mmelody_ticker_set (mmelody);
}


/* Set volume as percentage of maximum.  */
void 
mmelody_volume_set (mmelody_t mmelody, mmelody_volume_t volume)
{
    mmelody->volume = volume;
}


bool
mmelody_active_p (mmelody_t mmelody)
{
    return mmelody->cur != 0;
}


void
mmelody_update (mmelody_t mmelody)
{
    if (!mmelody->cur)
        return;

    if (mmelody->ticks1)
    {
        mmelody->ticks1--;
        if (!mmelody->ticks1)
            mmelody_note_off (mmelody);
    }
    else
    {
        if (mmelody->ticks2)
        {
            mmelody->ticks2--;
            if (!mmelody->ticks2)
                mmelody->cur = mmelody_scan (mmelody, mmelody->cur);
        }
    }
}


mmelody_t
mmelody_init (mmelody_obj_t *mmelody, 
              uint16_t poll_rate,
              mmelody_callback_t play_callback,
              void *play_callback_data)
{
    mmelody->poll_rate = poll_rate;
    mmelody->play_callback = play_callback;
    mmelody->play_callback_data = play_callback_data;
    mmelody->volume = 100;
    mmelody->note = 0;
    mmelody->ticks1 = 0;
    mmelody->ticks2 = 0;
    mmelody_speed_set (mmelody, MMELODY_SPEED_DEFAULT);
    mmelody_note_fraction_set (mmelody, 4);

    return mmelody;
}
