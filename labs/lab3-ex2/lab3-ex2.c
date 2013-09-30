#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

int main (void)
{
    system_init();
    pacer_init (PACER_RATE);

    /* TODO: Initialise tinygl. */
	tinygl_init (PACER_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set(MESSAGE_RATE);
    /* TODO: Set the message using tinygl_tlab3-ext().  */
    //const char test = "HI\0";
    /* TODO: Call the tinygl update function. */
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("HOLY SHIT\0");
    while(1)
    {
        pacer_wait();

        tinygl_update ();
    }
    return 0;
}
