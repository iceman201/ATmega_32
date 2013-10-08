/*
 * 
 */
#include "system.h"
#include "pacer.h"
#include "button.h"
#include "pio.h"
#include "basic_function.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"

/* Define polling rate in Hz.  */
#define LOOP_RATE 500
#define NAVSWITCH_RATE 50
#define MESSAGE_RATE 10
/* Define row constants */
#define INITIAL_ROW 3
#define INITIAL_COL 2
#define ROW_INCREMENT 1
#define COL_INCREMENT 1

struct pad 
{
    tinygl_point_t pos;
};
struct ball 
{
    tinygl_point_t pos;
};

typedef struct pad pad_t;
typedef struct ball ball_t;

int main (void)
{
    uint8_t rowinc;
    uint8_t colinc;
	uint8_t running;
	uint16_t tick;
	uint8_t Lost;
	tick = 0; running = 1; Lost = 0;
	rowinc = ROW_INCREMENT;
	colinc = COL_INCREMENT;
    system_init ();
    pacer_init (LOOP_RATE);
    ir_uart_init ();
	tinygl_init (LOOP_RATE);
    pad_t pad; 
	ball_t ball;
	pad.pos.x = 4;
	pad.pos.y = 4;
	
    //if (ir_uart_getc() == 'A' && check == 0){
	ball.pos.x = INITIAL_COL;
	ball.pos.y = INITIAL_ROW;
	//~ }
	//~ 
	//~ if (ir_uart_getc() == 'B'){
		//~ ball.pos.x = 1;
		//~ ball.pos.y = -1;
	//~ }
    while (1)
    {
		pacer_wait ();
		navswitch_update();
		if (!Lost) {
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
			tick++;
			if (running && tick > 300)
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
				if (ball.pos.x == -1)
				{
					ir_uart_putc('S');
				}
				tinygl_draw_point (ball.pos, 1);
			}
			if (check_lose (ball.pos.x, ball.pos.y, pad.pos.y) == 0)
			{
				Lost = 1;
			}
		} 
		else {
			you_lose(LOOP_RATE, MESSAGE_RATE);
		}
		tinygl_update ();	
	}
}	
