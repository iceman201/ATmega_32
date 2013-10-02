#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
    char character = 'A';

    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init ();
	ir_uart_init ();
    /* TODO: Initialise IR driver.  */
	char letter;

    pacer_init (PACER_RATE);

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        
        if (navswitch_push_event_p (NAVSWITCH_NORTH)){
            letter = character++;
			ir_uart_putc(letter);
		}
        else if (navswitch_push_event_p (NAVSWITCH_SOUTH)){
            letter = character--;
			ir_uart_putc(letter);
		}
        /* TODO: Transmit the character over IR on a NAVSWITCH_PUSH
           event.  */
		
        display_character (character);
        
    }

    return 0;
}
