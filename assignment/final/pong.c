#include "pong.h"
#include "led.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

#define MESSAGE_RATE 10

/* Implements the pacer_wait function */
void pong_wait (void)
{
    pacer_wait ();
}

/** Turns the blue LED on */
void pong_led_on (void)
{
    led_set (LED1, 1);
}

/** Turns the blue LED off */
void pong_led_off (void)
{
    led_set (LED1, 0);
}

void pong_send (pong_message_t m)
{
    ir_uart_putc (m);
}

pong_message_t pong_get (void)
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
    int tick = 0;
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("YOU LOSE! HAHA!\0");
    while (1) {
        pacer_wait ();
        tick++;
        if (tick == 20) 
        {
            pong_send (MESSAGE_LOST);
            tick = 0;
        }
        tinygl_update ();
    }
}

void pong_win (void)
{
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("YOU WIN! YAAAY!\0");
    while (1) {
        pacer_wait ();
        tinygl_update ();
    }
}

void pong_init (uint16_t rate)
{
    led_init ();
    pacer_init (rate);
    ir_uart_init ();
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}