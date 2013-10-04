/*
 * 
*/
#include "system.h"
#include "pacer.h"
#include "button.h"
#include "pio.h"
//#include "display.h"
#include "com.h"
//#include "navswitch.h"
//#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 3

/* Define row constants */
#define COL_NUM 5
#define ROW_NUM 7
#define INITIAL_COL 2
#define INITIAL_ROW 3
#define COL_INCREMENT 1
#define ROW_INCREMENT 1

/* the batten position it will change by navswiching*/
typedef struct {
	int col;
	int row;
} batten;


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


/** Turn single LED within matrix on or off.
    @param col LED column number
    @param row LED row number
    @param state LED state  */
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
/*  bottom_pad 
 * 	just got a idea and wrtten it down dont know how to link with whole code
void bottom_pad(void){
	navswitch_update();
	tinnygl_draw_point(pad,0);
	if (navswitch_push_event_p (NAVSWITCH_NORTH)&& pad.x < TINYGL_HEIGHT -1)
	{
		pad.x++;
	}
	if (navswitch_push_event_p (NAVSWITCH_SOUTH)&& pad.x < TINYGL_HEIGHT -1)
	{
		pad.x--;
	}
	tinygl.draw_point(pad,1);
}
*/
int main (void)
{

    int row;
    int col;
    int x; int y;
    int rowinc;
    int colinc;
	int check = 0;
	
    system_init ();
    ir_uart_init ();
    ledmat_init ();
    pacer_init (LOOP_RATE);
    ir_uart_putc('A');
    
    /*the two if loop is for run this code two time at different board
     *  and distinguish them which one is the second run
     */

    if (ir_uart_getc() == 'A' && check == 0){
		x = 3;
		y = 2;
	}
	
	if (ir_uart_getc() == 'B'){
		x = 1;
		y = -1;
	}
	row = x;
	col = y;
	rowinc = 1;
	colinc = 1;
    
    ledmat_pixel_set (col, row, 1);
	ledmat_pixel_set (4, row, 1);
    while (1)
    {
		navswitch_update();
		if (navswitch_push_event_p())
		{
			/*start*/
			break;
		}
    }
    while (1)
    {
			check = 1;
			pacer_wait ();
			ledmat_pixel_set (col, row, 0);        
			
			col += colinc;
			row += rowinc;
			
			/* update pad position somewhere here???*/ 
			if (row > 6 || row < 0)
			{
				row -= rowinc * 2;
				rowinc = -rowinc;
				/* update pad position somewhere here???*/
			}
			
			if (col > 3 || col < -4)
			{
				col -= colinc * 2;
				colinc = -colinc;
				/* update pad position somewhere here???*/
			}
			if (col <= -1)
			{
				char letter = 'B';
				/* sent signnal to the 2nd run borad*/
				ir_uart_putc(letter);
				
			}
			
			ledmat_pixel_set (col, row, 1);        	

	}

    /* TODO Finish the game */
        
    
}
