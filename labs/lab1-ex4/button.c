#include "pio.h"
#include "button.h"

#define BUTTON1 PIO_DEFINE (PORT_D, 7)

/** Return non-zero if button pressed.  */
int button_pressed_p (void)
{
    /* TODO.  */
    return PIND & (1<<7);
}


/** Initialise button1.  */
void button_init (void)
{
	pio_config_set (BUTTON1, PIO_INPUT);
    /* TODO.  */
}

