#include <avr/io.h>
#include "system.h"

int main (void)
{
    system_init ();

    /* Initialise port to drive LED 1.  */
    
    /* TODO.  */
	DDRC = DDRC | 0x04;
	
    while (1)
    {
		if ((PIND & (1<<7))){
			/* Turn LED 1 on.  */
			PORTC |= (1<<2);
			/* TODO.  */
		}
		else{
			PORTC & -(0<<2);
		}
	}
}
