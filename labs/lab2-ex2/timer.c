#include <avr/io.h>
#include "timer.h"

/* Initialise timer.  */
void timer_init (void)
{
    /* TODO */
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCNT1 = 0;
}


/* Wait for the specified length of time.  */
void timer_delay_ms (uint16_t milliseconds)
{

	int TICKS = 0;
	int cpu = 0;

	cpu = 7.8125 * 1000;
	TICKS = cpu / (1000/milliseconds);
	
	//TICKS = 7813/(1000 / milliseconds);
	
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
}
