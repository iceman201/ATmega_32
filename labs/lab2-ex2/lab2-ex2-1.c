#include "system.h"
#include "led.h"
#include "pio.h"
#include "timer.h"

int main (void)
{
    system_init ();
    led_init ();
    
    pio_config_set(LEDMAT_COL1_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL2_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL3_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL4_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL5_PIO,PIO_OUTPUT_HIGH);
	
	pio_config_set(LEDMAT_ROW1_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW2_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW3_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW4_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW5_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW6_PIO,PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW7_PIO,PIO_OUTPUT_HIGH);
	
    /* Initialise timer.  */
    timer_init ();
    
    while (1)
    {
		//~ pio_output_low(LEDMAT_COL3_PIO);    
		//~ pio_output_low(LEDMAT_ROW5_PIO);

		pio_output_high(LEDMAT_COL1_PIO);
		pio_output_high(LEDMAT_ROW1_PIO);
		pio_output_high(LEDMAT_ROW7_PIO);
		pio_output_high(LEDMAT_COL5_PIO);		
		timer_delay_ms (1);
		pio_output_low(LEDMAT_COL1_PIO);
		pio_output_low(LEDMAT_ROW1_PIO);
		timer_delay_ms (1);
		pio_output_high(LEDMAT_COL1_PIO);
		pio_output_high(LEDMAT_ROW1_PIO);
		timer_delay_ms (1);
		pio_output_low(LEDMAT_COL5_PIO);
		pio_output_low(LEDMAT_ROW1_PIO);
		timer_delay_ms (1);
		pio_output_high(LEDMAT_COL5_PIO);
		pio_output_high(LEDMAT_ROW1_PIO);
		timer_delay_ms (1);
		pio_output_low(LEDMAT_COL1_PIO);
		pio_output_low(LEDMAT_ROW1_PIO);
		pio_output_low(LEDMAT_ROW7_PIO);
		pio_output_high(LEDMAT_COL5_PIO);
		timer_delay_ms (1);
        /* Wait 500ms.  */
    //    timer_delay_ms (500);      
    }
}
