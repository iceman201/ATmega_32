#include <avr/io.h>
#include "system.h"
#include "led.h"


int main (void)
{
    system_init ();
    led_init ();
    
    /* TODO: Initialise timer/counter1.  */
    
    while (1)
    {
        
        /* Turn LED on.  */
        led_set (LED1, 1);
        
        /* TODO: wait for 500 milliseconds.  */
        
        /* Turn LED off.  */
        led_set (LED1, 0);
        
        /* TODO: wait for 500 milliseconds.  */
        
    }
    
}
