#include <avr/io.h>
#include "system.h"
#include "led.h"
#include "timer.h"

int main (void)
{
	timer_tick_t now;
    system_init ();
    led_init ();
    timer_init ();
    /* TODO: Initialise timer/counter1.  */
    now = timer_get ();
    while (1)
    {
        /* Turn LED on.  */
       led_set (LED1, 1);
	   now = timer_wait_until(now + (timer_tick_t)(TIMER_RATE * 0.5));	
	   led_set (LED1, 0);
	   now = timer_wait_until(now + (timer_tick_t)(TIMER_RATE * 0.75));        
        /* TODO: wait for 500 milliseconds.  */
    }
}
