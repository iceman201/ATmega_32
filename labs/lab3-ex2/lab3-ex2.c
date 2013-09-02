#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

int main (void)
{
    system_init();

    /* TODO: Initialise tinygl. */

    /* TODO: Set the message using tinygl_tlab3-ext().  */
    

    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait();
        
        /* TODO: Call the tinygl update function. */
        
    }
    return 0;
}
