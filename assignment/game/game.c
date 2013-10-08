/********************************************
 * 2013 Semester 2                          *
 * ENCE 260  Assignment                     *
 * Group number:   40                       *
 * Game name : 								*
 * Student name: David Barclay & Liguo Jiao *
 ********************************************/
 
#include "pacer.h"
#include "basic_function.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "led.h"
#include "../../fonts/font5x7_1.h"

/* Define polling rate in Hz.  */
#define LOOP_RATE 500
#define MESSAGE_RATE 10

/* Define game board constants */
enum {
	INITIAL_ROW_S =  3,	INITIAL_COL_S =  2,
	INITIAL_ROW_R =  3,	INITIAL_COL_R =  -3,
	INITIAL_ROW_INCREMENT =  1,
	INITIAL_COL_INCREMENT =  1,
	INITIAL_PAD_X = 4,
	INITIAL_PAD_Y = 4,
	MIN_Y =  0,	MAX_Y =  6,
	MIN_X = -4,	MAX_X =  3,
};

typedef enum {SETUP_SENDING,SETUP_RECIEVING,PLAYING,FINISH_WON,FINISH_LOST} state_t;

typedef struct _pad 
{
    tinygl_point_t pos;
} pad_t;

typedef struct _ball 
{
    tinygl_point_t pos;
} ball_t;

int main (void)
{
    uint8_t rowinc;
    uint8_t colinc;
    uint16_t tick;
    state_t state;
    pad_t pad; 
    ball_t ball;
    
    system_init ();
    led_init ();
    pacer_init (LOOP_RATE);
    ir_uart_init ();
    navswitch_init ();
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
	tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    tick = 0;
    rowinc = INITIAL_ROW_INCREMENT;
    colinc = INITIAL_COL_INCREMENT;
    pad.pos.x = INITIAL_PAD_X;
    pad.pos.y = INITIAL_PAD_Y;
    ball.pos.x = INITIAL_COL_S;
    ball.pos.y = INITIAL_ROW_S;
    state = SETUP_SENDING;

    while (1)
    {
		// Sending state loop
        while (state == SETUP_SENDING)
        {
			pacer_wait ();
			navswitch_update ();
            if (navswitch_down_p (NAVSWITCH_PUSH))
            {
                state = SETUP_RECIEVING;
                ball.pos.x = INITIAL_COL_R;
                ball.pos.y = INITIAL_ROW_R;
                rowinc = -INITIAL_ROW_INCREMENT;
                colinc = -INITIAL_ROW_INCREMENT;
				led_set (LED1, 0);
            }
            com_send (MESSAGE_SENDING);
            if (com_get () == MESSAGE_RECIEVING)
            {
				state = PLAYING;
				com_send (MESSAGE_PLAYING);
				led_set (LED1, 0);
			}
        }
        // Recieving state loop
        tick = 0;
        while (state == SETUP_RECIEVING)
        {
			pacer_wait ();
			tick++;
            if (tick == 260)
            {
				com_send (MESSAGE_RECIEVING);
				tick = 0;
			}
            if (com_get () == MESSAGE_PLAYING)
            {
				state = PLAYING;
				led_set (LED1, 1);
				//~ led_set (LED1, 0);
			}
        }        
        /* Game loop */
        while (state == PLAYING) 
        {
            pacer_wait ();            
            // Send playing message
			if (!(tick%10))
			{
				com_send (MESSAGE_PLAYING);
			}            
            navswitch_update();
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
				state = FINISH_LOST;
			}
			// Check for loss signal
			if ( com_get () == MESSAGE_LOST )
			{
				state = FINISH_WON;
			}
        }
        tick = 0;
        /* End program with loss message */
        if (state == FINISH_LOST)
        {
//			tinygl_text("HAHA YOU LOSE!\0");
			while (1)
			{
				pacer_wait();
				tick++;
				if (tick == 20)
				{
					com_send (MESSAGE_LOST);
					tick = 0;
				}
				you_lose();
//				tinygl_update ();
			}
        }
        /* End program with win message */
        if (state == FINISH_WON)
        {
//			tinygl_text("YAY YOU WIN!\0");
			while (1)
			{
				pacer_wait ();
				you_win ();
//				tinygl_update ();
			}
	    }	  
    }   
    return 0;
}
