/** @file   hello2.c
    @author M. P. Hayes, UCECE
    @date   24 August 2009
    @brief  Simple message display program using tinygl
    
    @defgroup hello2 Simple message display program using tinygl
*/

#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 300

/* Define text update rate (characters per 10s).  */
#define MESSAGE_RATE 10


int main (void)
{
    system_init ();
    tinygl_init (LOOP_RATE);

    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);

    tinygl_text ("HELLO WORLD");

    pacer_init (LOOP_RATE);

    /* Paced loop.  */
    while (1)
    {
        /* Wait for next tick.  */
        pacer_wait ();

        tinygl_update ();
    }

    return 0;
}
