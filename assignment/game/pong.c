#include "pong.h"
#include "led.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

#define MESSAGE_RATE 10

void pong_led_on (void)
{
	led_set (LED1, 1);
}

void pong_led_off (void)
{
	led_set (LED1, 0);
}

void pong_send (pong_message m)
{
    ir_uart_putc (m);
}

pong_message pong_get (void)
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

void pong_lose (void)
{
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("HAHA YOU LOSE!\0");
    while (1) {
        pacer_wait ();
        pong_send (MESSAGE_LOST);
        tinygl_update ();
    }
}

void pong_win (void)
{
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("YAY YOU WIN!\0");
    while (1) {
        pacer_wait ();
        tinygl_update ();
    }
}

void pong_init (void)
{
	led_init ();
	ir_uart_init ();
	tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}