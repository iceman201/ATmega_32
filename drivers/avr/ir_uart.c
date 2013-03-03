/** @file   ir_uart.c
    @author Michael Hayes
    @date   10 December 2004
*/
#include "system.h"
#include "ir_uart.h"
#include "usart1.h"
#include "timer0.h"
#include "pio.h"


/* Return non-zero if there is a character ready to be read.  */
bool
ir_uart_read_ready_p (void)
{
    return usart1_read_ready_p ();
}


/* Read character from IR_UART.  This blocks if nothing
   is available to read.  */
int8_t
ir_uart_getc (void)
{
    return usart1_getc ();
}


/* Return non-zero if a character can be written without blocking.  */
bool
ir_uart_write_ready_p (void)
{
    return usart1_write_ready_p ();
}


/* Return non-zero if transmitter finished.  */
bool
ir_uart_write_finished_p (void)
{
    return usart1_write_finished_p ();
}


/* Write character to IR_UART.  This returns zero if
   the character could not be written.  */
int8_t
ir_uart_putc (char ch)
{
    usart1_putc (ch);

    /* The character gets echoed on the UCFK4 so we should
       probably gobble it here.  */

    return 1;
}


/* Write string to IR_UART.  */
void
ir_uart_puts (const char *str)
{
    usart1_puts (str);
}


/* Initialise ir_uart and set baud rate.  */
uint8_t
ir_uart_init (void)
{
    usart1_cfg_t usart1_cfg = 
        {
            .baud_divisor = USART1_BAUD_DIVISOR (IR_UART_BAUD_RATE),
            .bits = 8
        };


    /* Need to configure DDR so pin is an output.
       The state is controlled by the timer.  */
    pio_config_set (IR_TX_HIGH_PIO, PIO_OUTPUT_HIGH);
    timer0_init ();

    timer0_period_set (F_CPU / (IR_MODULATION_FREQ * 2));
    timer0_mode_set (TIMER0_MODE_CTC);
    timer0_output_set (TIMER0_OUTPUT_B, TIMER0_OUTPUT_MODE_TOGGLE);

    timer0_start ();

    return usart1_init (&usart1_cfg);
}
