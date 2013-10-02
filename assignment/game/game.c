#include "system.h"
#include "pacer.h"
#include "pio.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 10

/* Define row constants */
#define COL_NUM 5
#define ROW_NUM 7
#define INITIAL_COL 2
#define INITIAL_ROW 3
#define COL_INCREMENT 1
#define ROW_INCREMENT 1

/* initialises the game */
void game_init () {
    row = INITIAL_ROW;
    col = INITIAL_COL;
    rowinc = ROW_INCREMENT;
    colinc = COL_INCREMENT;
}

/* calculates the next game tick */
void game_tick () {
    
}


int main (void)
{
    int row;
    int col;
    int rowinc;
    int colinc;

    system_init ();
    display_init ();
    
    pacer_init (LOOP_RATE);

    /* Paced loop.  */
    while (1)
    {

    /* TODO Set up the game */

    /* while the game has not ended */
        while (state == PLAYING) {
        /* Wait for next tick.  */
        pacer_wait ();
        
        game_tick ();
        display_update ();

        }

    /* TODO Finish the game */
        
    }
}
