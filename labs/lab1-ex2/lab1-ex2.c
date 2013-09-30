#include <avr/io.h>
#include "system.h"


static void led_init (void)
{
    /* Initialise port to drive LED 1.  */
	DDRC = DDRC | (1 << 2);
    /* TODO.  */
}
static void led_on (void)
{
    /* Set port to turn LED 1 on.  */
	PORTC |= (1<<2);
    /* TODO.  */
}
static void led_off (void)
{
    /* Set port to turn LED 1 off.  */
	PORTC &= -(0<<2);
    /* TODO.  */
}
static void button_init (void)
{
    /* Initialise port to read button 1.  */
	DDRD = DDRD | (0 << 7);
    /* TODO.  */
}
static int button_pressed_p (void)
{
    /* Return non-zero if button pressed_p.  */
	return PIND &= (1<<7);
    /* TODO.  */
}


int main (void)
{
    system_init ();

    led_init ();
    button_init ();

    while (1)
    {
        if (button_pressed_p ())
        {
            led_on ();
        }
        else
        {
            led_off ();
        }
    }
}
