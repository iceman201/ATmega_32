#include "system.h"
#include "button.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"


int main (void)
{
    system_init();
    
    /* TODO: Initialise the button driver, tinygl, and the pacer.  */


    while(1)
    {
        pacer_wait();

	/* TODO: Implement the functionality of the tasks in the
           stopwatch1 program.  */

    }
    return 0;
}
