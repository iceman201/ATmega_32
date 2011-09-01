/** @file   mmelody.h
    @author M. P. Hayes, UCECE
    @date   20 April 2007
    @brief  Play simple melodies.
*/
#ifndef MMELODY_H
#define MMELODY_H

#include "system.h"

typedef uint8_t mmelody_speed_t;
typedef uint8_t mmelody_scale_t;
typedef uint8_t mmelody_note_t;
typedef uint8_t mmelody_volume_t;


enum {MMELODY_OCTAVE_DEFAULT = 4};
enum {MMELODY_SPEED_DEFAULT = 200};


typedef struct
{
    uint16_t ticks1;
    uint8_t ticks2;
    uint8_t unit_ticks;
    uint8_t release_ticks;
    /* Pointer to current position in string.  */    
    const char *cur;
    /* Pointer to start of string.  */
    const char *start;
    const char *loop_start;
    int8_t loop_count;
    /* Fraction of a whole note, e.g., 4 for quarter note.  */
    uint8_t symbol_fraction;
    /* Last note emitted.  */
    uint8_t note;
    /* Tempo in beats per minute.  */
    mmelody_speed_t speed;
    mmelody_volume_t volume;
    uint8_t octave;
    void (* play_callback) (void *data, uint8_t note, uint8_t volume);
    void *play_callback_data;
    uint16_t poll_rate;
} mmelody_private_t;

typedef mmelody_private_t mmelody_obj_t;
typedef mmelody_obj_t *mmelody_t;


typedef void (* mmelody_callback_t) (void *data, uint8_t note, uint8_t volume);

mmelody_t
mmelody_init (mmelody_obj_t *dev, 
              uint16_t poll_rate,
              mmelody_callback_t play_callback,
              void *play_callback_data);

/** Start playing a new melody.  */
void 
mmelody_play (mmelody_t mmelody, const char *str);


/** Update melody sequencer.  */
void
mmelody_update (mmelody_t mmelody);


/** Set (base) speed in beats per minute (BPM).  */
void 
mmelody_speed_set (mmelody_t mmelody, mmelody_speed_t speed);


/** Set volume as percentage of maximum.  */
void 
mmelody_volume_set (mmelody_t mmelody, mmelody_volume_t volume);


/** Return non-zero if playing.  */
bool
mmelody_active_p (mmelody_t mmelody);


#endif
