#include "basic_function.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

#define MESSAGE_RATE 10

void com_send (char m)
{
	ir_uart_putc (m);
}

char com_get (void)
{
	if ( ir_uart_read_ready_p () )
	{
		return ir_uart_getc ();
	}
	else 
	{
		return 0;
	}
}

void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text (buffer);
}

void you_lose (void)
{
	tinygl_text_speed_set(MESSAGE_RATE);
	tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
	tinygl_text("HAHA YOU LOSE!\0");
	while (1) {
		pacer_wait ();
		tinygl_update ();
	}
}

void you_win (void)
{
	tinygl_text_speed_set(MESSAGE_RATE);
	tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
	tinygl_text("YAY YOU WIN!\0");
	while (1) {
		pacer_wait ();
		tinygl_update ();
	}
}

