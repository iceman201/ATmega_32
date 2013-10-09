/********************************************
 * 2013 Semester 2                          *
 * ENCE 260  Assignment                     *
 * Group number:   40                       *
 * Game name :                              *
 * Student name: David Barclay & Liguo Jiao *
 ********************************************/
 
#include "pacer.h"
#include "pong.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../../fonts/font5x7_1.h"

/* Define polling rate in Hz.  */
#define LOOP_RATE 500

/* Define game board constants */
enum {
    INITIAL_ROW_S =  3,    INITIAL_COL_S =  2,
    INITIAL_ROW_R =  3,    INITIAL_COL_R =  -3,
    INITIAL_ROW_INCREMENT =  1,
    INITIAL_COL_INCREMENT =  1,
    INITIAL_PAD_X = 4,
    INITIAL_PAD_Y = 4,
    MIN_Y =  0,    MAX_Y =  6,
    MIN_X = -4,    MAX_X =  3,
};

int main (void)
{
    uint8_t rowinc;
    uint8_t colinc;
    uint16_t tick;
    pong_state state;
    pong_pad pad; 
    pong_ball ball;
    
    system_init ();
    pacer_init (LOOP_RATE);
    navswitch_init ();
    tinygl_init (LOOP_RATE);
    pong_init ();

    tick = 0;
    rowinc = INITIAL_ROW_INCREMENT;
    colinc = INITIAL_COL_INCREMENT;
    pad.pos.x = INITIAL_PAD_X;
    pad.pos.y = INITIAL_PAD_Y;
    ball.pos.x = INITIAL_COL_S;
    ball.pos.y = INITIAL_ROW_S;
    state = STATE_SETUP_SENDING;

    while (1)
    {
        // Sending state loop
        while (state == STATE_SETUP_SENDING)
        {
            pacer_wait ();
            navswitch_update ();
            if (navswitch_down_p (NAVSWITCH_PUSH))
            {
                state = STATE_SETUP_RECIEVING;
                ball.pos.x = INITIAL_COL_R;
                ball.pos.y = INITIAL_ROW_R;
                rowinc = -INITIAL_ROW_INCREMENT;
                colinc = -INITIAL_ROW_INCREMENT;
                pong_led_off ();
            }
            pong_send (MESSAGE_SENDING);
            if (pong_get () == MESSAGE_RECIEVING)
            {
                state = STATE_PLAYING;
                pong_send (MESSAGE_PLAYING);
                pong_led_off ();
            }
        }
        // Recieving state loop
        tick = 0;
        while (state == STATE_SETUP_RECIEVING)
        {
            pacer_wait ();
            tick++;
            if (tick == 10)
            {
                pong_send (MESSAGE_RECIEVING);
                tick = 0;
            }
            if (pong_get () == MESSAGE_PLAYING)
            {
                state = STATE_PLAYING;
            }
        }        
        /* Game loop */
        while (state == STATE_PLAYING) 
        {
            pacer_wait ();
            navswitch_update();

            // Send playing message
            if (!(tick%10))
            {
                pong_send (MESSAGE_PLAYING);
            }            
            
            // Do pad movement
            tinygl_draw_point (pad.pos, 0);
            if (navswitch_push_event_p (NAVSWITCH_NORTH) && pad.pos.y > 0)
            {
                pad.pos.y--;
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH) && pad.pos.y < TINYGL_HEIGHT -1)
            {
                pad.pos.y++;
            }
            tinygl_draw_point (pad.pos, 1);

            // Do ball movement
            tick++;
            if (tick > 300)
            {
                tick = 0;
                tinygl_draw_point (ball.pos, 0); // Remove the old point
                ball.pos.x += colinc;
                ball.pos.y += rowinc;
                if (ball.pos.y > MAX_Y || ball.pos.y < MIN_Y)
                {
                    ball.pos.y -= rowinc * 2;
                    rowinc = -rowinc;
                }  
                if (ball.pos.x > MAX_X || ball.pos.x < MIN_X)
                {
                    ball.pos.x -= colinc * 2;
                    colinc = -colinc;
                }
                tinygl_draw_point (ball.pos, 1); // Draw the new point
            }
            tinygl_update ();

            // Check for game loss
            if ((ball.pos.x == MAX_X) && (ball.pos.y != pad.pos.y))
            {
                state = STATE_FINISH_LOST;
            }
            // Check for loss signal
            if ( pong_get () == MESSAGE_LOST )
            {
                state = STATE_FINISH_WON;
            }
        }

        /* End program */
        if (state == STATE_FINISH_LOST)
        {
            pong_lose ();
        }
        if (state == STATE_FINISH_WON)
        {
            pong_win ();
        }      
    }   
    return 0;
}
