#include <avr/io.h>
#include "system.h"


static void led_init (void)
{
    /* Initialise port to drive LED 1.  */

    /* TODO.  */
}


static void led_on (void)
{
    /* Set port to turn LED 1 on.  */

    /* TODO.  */
}


static void led_off (void)
{
    /* Set port to turn LED 1 off.  */

    /* TODO.  */
}



static void button_init (void)
{
    /* Initialise port to read button 1.  */

    /* TODO.  */
}


static int button_pressed_p (void)
{
    /* Return non-zero if button pressed_p.  */

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
