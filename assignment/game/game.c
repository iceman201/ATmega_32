/*
 * 
 */
#include "system.h"
#include "pacer.h"
#include "button.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"
#include "com.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 500

#define TINYGL_RATE 150
#define NAVSWITCH_RATE 50
#define GAME_RATE 100

/* Define row constants */
#define COL_NUM 5
#define ROW_NUM 7
#define INITIAL_COL 3
#define INITIAL_ROW 3
#define INITIAL_COL_INCREMENT -1
#define INITIAL_ROW_INCREMENT 1

struct _pad 
{
    tinygl_point_t pos;
    /* Current direction.  */
};
typedef struct _pad pad_t;

struct _ball 
{
    tinygl_point_t pos;
    /* Current direction.  */
};
typedef struct _ball ball_t;


int main (void)
{
    /* Initialization function calls */
    system_init ();
    ir_uart_init ();
    pacer_init (LOOP_RATE);
    tinygl_init (TINYGL_RATE);
    
    /* Declare variables */
    uint16_t tick;
    pad_t pad;
    ball_t ball;
    int8_t rowinc;
    int8_t colinc;
    
    
    tinygl_font_set (&font5x7_1);
    uint8_t running = 1;
    //~ if (ir_uart_getc() == 'A' && check == 0){
        //~ x = 3;
        //~ y = 2;
    //~ }
    //~ 
    //~ if (ir_uart_getc() == 'B'){
        //~ x = 1;
        //~ y = -1;
    //~ }
    tick = 0;
    colinc = INITIAL_COL_INCREMENT;
    rowinc = INITIAL_ROW_INCREMENT;
    ball.pos.x = INITIAL_COL;
    ball.pos.y = INITIAL_ROW;
    pad.pos.x = 4;
    pad.pos.y = TINYGL_HEIGHT / 2;
    tinygl_draw_point (pad.pos, 1); // Draw the pad
    tinygl_draw_point (ball.pos, 1); // Draw the ball
    ir_uart_putc('A');
    
    while (1)
    {
        pacer_wait ();
        navswitch_update ();
        tick++;
        
        /* Handle pad movement */
        tinygl_draw_point (pad.pos, 0); /* Clear the previous pad point */
        if (navswitch_push_event_p (NAVSWITCH_NORTH) && pad.pos.y > 0)
        {
            pad.pos.y--;
        }
        if (navswitch_push_event_p (NAVSWITCH_SOUTH) && pad.pos.y < TINYGL_HEIGHT -1)
        {
            pad.pos.y++;
        }
        tinygl_draw_point (pad.pos, 1); /* Draw the new pad point */
        
        /* Handle ball movement */
        if (running && (tick > GAME_RATE))
        {
            tick = 0;
            tinygl_draw_point (ball.pos, 0);
            ball.pos.x += colinc;
            ball.pos.y += rowinc;
            if (ball.pos.y > 6 || ball.pos.y < 0)
            {
                ball.pos.y -= rowinc * 2;
                rowinc = -rowinc;
            }    
            if (ball.pos.x > 3 || ball.pos.x < -4)
            {
                ball.pos.x -= colinc * 2;
                colinc = -colinc;
            }
            tinygl_draw_point (ball.pos, 1);
        }
        
        //~ if (col <= -1)
        //~ {
            //~ char letter = 'B';
        //~ /* sent signnal to the 2nd run borad*/
            //~ ir_uart_putc(letter);
        //~ }
        
        tinygl_update ();
    }

    /* TODO Finish the game */
    return 0;
}
