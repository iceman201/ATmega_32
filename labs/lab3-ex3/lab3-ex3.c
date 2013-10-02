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
    char character = 'W';

    system_init ();
	ir_uart_init ();
	
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);

    /* TODO: Initialise navigation switch driver.  */

    pacer_init (PACER_RATE);
	int counter = 0;
    while(1)
    {
        pacer_wait ();
        tinygl_update ();
        //ir_uart_read_ready_p()
        navswitch_update();
        /* TODO: Call the navswitch update function.  */
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)&&counter==0){
        /* TODO: Increment character if NORTH is pressed.  */
			display_character('H');
			counter+=1;
			ir_uart_putc(character);
		}
        /* TODO: Decrement character if SOUTH is pressed.  */
        else if (navswitch_push_event_p(NAVSWITCH_SOUTH)&&counter==1){
			display_character ('E');
			counter+=1;
		}
		else if (navswitch_push_event_p(NAVSWITCH_SOUTH)&&counter==2){
			display_character ('L');
			counter+=1;
		}
		else if (navswitch_push_event_p(NAVSWITCH_SOUTH)&&counter==3){
			display_character ('L');
			counter+=1;
		}
		else if (navswitch_push_event_p(NAVSWITCH_SOUTH) && counter==4){
			display_character ('O');
			counter+=1;
		}
		else if (navswitch_push_event_p(NAVSWITCH_NORTH) && counter==5){
			display_character ('l');
			counter+=1;
		}
		else if (navswitch_push_event_p(NAVSWITCH_NORTH) && counter==6){
			display_character ('l');
			counter+=1;
		}
		else if (navswitch_push_event_p(NAVSWITCH_NORTH) && counter==7){
			display_character ('e');
			counter+=1;
		}
		else if (navswitch_push_event_p(NAVSWITCH_NORTH) && counter==8){
			display_character ('h');
			counter+=1;
		}
		else if (counter == 9){
			counter = 0;
		}
		
    }
    return 0;
}
