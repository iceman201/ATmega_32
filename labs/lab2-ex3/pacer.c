#include <avr/io.h>
#include "pacer.h"

static uint16_t pacer_period;

/* Initialise the pacer module.  */
void pacer_init (uint16_t pacer_frequency)
{
    /* TODO: initialise timer/counter peripheral the
       same way as in lab2/lab2-ex2/timer.c but also calculate 
       the timer/counter value from the pacer frequency */
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCNT1 = 0;
}


/* Pace a while loop.  */
void pacer_wait (void)
{
	int TICKS = 0;
	int cpu = 0;

	cpu = 7.8125 * 1000;
	TICKS = cpu / (1000/milliseconds);
	
	while (TCNT1 < TICKS){
    /* TODO: Calculate the timer/counter value needed 
       for the given number of milliseconds. */
		//pacel = milliseconds * 0.001;
		//cpu = 0.78125 * 10000;
		//TICKS = pacel / cpu;
		continue;
    
    /* TODO: Wait for the timer/couter to reach the 
       value calculated above.  */
    }
    TCNT1 = 0;
    
    /* TODO: Implement the same way as the timer_delay () function 
       lab2-except reset TCNT1 after the while loop. */

}
