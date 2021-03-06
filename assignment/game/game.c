/********************************************
 * 2013 Semester 2                          *
 * ENCE 260  Assignment                     *
 * Group number:   40                       *
 * Game name : Simple Pong                  *
 * Student:       dlb70 - David Barclay     *
 * ID - NAME      lji30 - Liguo Jiao        *
 ********************************************/

/** @file   game.c
    @author Group 40
    @date   10/10/2013
    @brief  A simple pong-like game

    @reference  Some of the code for ball movement was appropriated 
                from Michael Hayes' bounce program.
*/

#include "pong.h"
#include "navswitch.h"
#include "tinygl.h"

#define LOOP_RATE (uint16_t)(500)
#define GAME_RATE 300
#define MESSAGE_RATE 10

/* Define initial game variables  */
enum {
    INITIAL_STATE   =   STATE_SETUP_SENDING,
    INITIAL_ROW_S   =   3,
    INITIAL_COL_S   =   2,
    INITIAL_ROW_R   =   3,
    INITIAL_COL_R   =   -3,
    INITIAL_ROW_INC =   1,
    INITIAL_COL_INC =   1,
    INITIAL_PAD_X   =   4,
    INITIAL_PAD_Y   =   4
};

int main (void)
{
    /* Initialise stuff  */
    system_init ();
    pacer_init (LOOP_RATE);
    navswitch_init ();
    tinygl_init (LOOP_RATE);
    pong_init (LOOP_RATE);

    /* Initialise variables  */
    uint16_t tick;
    pong_state_t state;
    pong_pad_t pad; 
    pong_ball_t ball;

    /* Set initialised variables  */
    tick = 0;
    ball.rowinc = INITIAL_ROW_INC;
    ball.colinc = INITIAL_COL_INC;
    pad.pos.x = INITIAL_PAD_X;
    pad.pos.y = INITIAL_PAD_Y;
    ball.pos.x = INITIAL_COL_S;
    ball.pos.y = INITIAL_ROW_S;
    state = INITIAL_STATE;

    /* Main game loop, this will only get cycled once as the end functions block  */
    while (1)
    {

        while (state == STATE_SETUP_SENDING)
        {
            pong_wait ();
            navswitch_update ();
            if (navswitch_down_p (NAVSWITCH_PUSH))
            {
                state = STATE_SETUP_RECIEVING;
                ball.pos.x = INITIAL_COL_R;
                ball.pos.y = INITIAL_ROW_R;
                ball.rowinc = -INITIAL_ROW_INC;
                ball.colinc = -INITIAL_ROW_INC;
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

        tick = 0;
        while (state == STATE_SETUP_RECIEVING)
        {
            pong_wait ();
            tick++;
            if (tick == MESSAGE_RATE)
            {
                pong_send (MESSAGE_RECIEVING);
                tick = 0;
            }
            if (pong_get () == MESSAGE_PLAYING)
            {
                state = STATE_PLAYING;
            }
        }

        tick = 0;
        while (state == STATE_PLAYING) 
        {
            pong_wait ();
            navswitch_update();

            if (!(tick % MESSAGE_RATE))
            {
                pong_send (MESSAGE_PLAYING);
            }            
            
            // Do pad movement
            tinygl_draw_point (pad.pos, 0);
            if (navswitch_push_event_p (NAVSWITCH_NORTH) && (pad.pos.y > 0))
            {
                pad.pos.y--;
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH) && (pad.pos.y < (TINYGL_HEIGHT -1)))
            {
                pad.pos.y++;
            }
            tinygl_draw_point (pad.pos, 1);

            // Do ball movement
            tick++;
            if (tick > GAME_RATE)
            {
                tick = 0;
                tinygl_draw_point (ball.pos, 0);
                ball.pos.x += ball.colinc;
                ball.pos.y += ball.rowinc;
                if ((ball.pos.y > MAX_Y) || (ball.pos.y < MIN_Y))
                {
                    ball.pos.y -=  ball.rowinc * 2;
                    ball.rowinc = -ball.rowinc;
                }  
                if ((ball.pos.x > MAX_X) || (ball.pos.x < MIN_X))
                {
                    ball.pos.x -=  ball.colinc * 2;
                    ball.colinc = -ball.colinc;
                }
                tinygl_draw_point (ball.pos, 1);
            }
            
            tinygl_update ();

            if ((ball.pos.x == MAX_X) && (ball.pos.y != pad.pos.y))
            {
                state = STATE_FINISH_LOST;
            }
            if (pong_get () == MESSAGE_LOST)
            {
                state = STATE_FINISH_WON;
            }
        }

        /* End program  */
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
