/*
 * 
*/
#include "system.h"
#include "pacer.h"
#include "button.h"
#include "pio.h"
#include "com.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "display.h"
#include "../fonts/font5x7_1.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 3
#define NAVSWITCH_RATE 50

/* Define row constants */
#define COL_NUM 5
#define ROW_NUM 7
#define INITIAL_COL 2
#define INITIAL_ROW 3
#define COL_INCREMENT 1
#define ROW_INCREMENT 1

struct pad 
{
    tinygl_point_t pos;
    /* Current direction.  */
};
typedef struct pad pad_t;

struct ball 
{
    tinygl_point_t pos;
    /* Current direction.  */
};
typedef struct ball ball_t;


/* Define PIO pins driving LED matrix rows and columns.  */
static pio_t ledmat_rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, LEDMAT_ROW4_PIO,
    LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO, LEDMAT_ROW7_PIO
};

static pio_t ledmat_cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


static void ledmat_pixel_set (int col, int row, bool state)
{
    if (state)
    {
        pio_output_low (ledmat_rows[row]);
        pio_output_low (ledmat_cols[col]);
    }
    else
    {
        pio_output_high (ledmat_rows[row]);
        pio_output_high (ledmat_cols[col]);
    }
}


/** Initialise LED matrix PIO pins.  */
static void ledmat_init (void)
{
    uint8_t row;
    uint8_t col;

    for (row = 0; row < 7; row++)
    {
        pio_config_set (ledmat_rows[row], PIO_OUTPUT_HIGH);
        pio_output_high (ledmat_rows[row]);
    }

    for (col = 0; col < 5; col++)
    {
        pio_config_set (ledmat_cols[col], PIO_OUTPUT_HIGH);
        pio_output_high (ledmat_cols[col]);
    }
}


int main (void)
{

    int row;
    int col;
    int rowinc;
    int colinc;

    system_init ();
    ir_uart_init ();
    ledmat_init ();
    pacer_init (LOOP_RATE);
    ir_uart_putc('A');

	tinygl_init (LOOP_RATE);
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

	row = INITIAL_ROW;
	col = INITIAL_COL;
	rowinc = 1;
	colinc = 1;
    ledmat_pixel_set (col, row, 1);

	pad_t pad;
	ball_t ball;
	ball.pos.x = col;
	ball.pos.y = row;
	pad.pos.x = 4;
	pad.pos.y = TINYGL_HEIGHT / 2;
    while (1)
    {
		//check = 1;
		tinygl_draw_point (pad.pos, 0); 
		tinygl_draw_point (ball.pos, 0);       
		//bottom_pad();
		col += colinc;
		row += rowinc;
		ball.pos.x = col;
		ball.pos.y = row;
		navswitch_update();
		
		if (navswitch_push_event_p (NAVSWITCH_NORTH) && pad.pos.y > 0)
		{
			pad.pos.y--;
		}
		if (navswitch_push_event_p (NAVSWITCH_SOUTH) && pad.pos.y < TINYGL_HEIGHT -1)
		{
			pad.pos.y++;
		}
		tinygl_draw_point (pad.pos, 1);
        if (running)
		{
			pacer_wait ();
			if (row > 6 || row < 0)
			{
				row -= rowinc * 2;
				rowinc = -rowinc;
				ball.pos.y = row;
			/* update pad position somewhere here???*/
			}	
			if (col > 3 || col < -4)
			{
				col -= colinc * 2;
				colinc = -colinc;
				ball.pos.x = col;
			/* update pad position somewhere here???*/
			}
		}
		tinygl_draw_point (ball.pos, 1);
		if (col <= -1)
		{
			char letter = 'B';
		/* sent signnal to the 2nd run borad*/
			ir_uart_putc(letter);
		}
		tinygl_update ();

	}

    /* TODO Finish the game */
	return 0;
}
