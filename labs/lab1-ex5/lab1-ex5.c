#include "pio.h"
#include "system.h"

// High for cutoff the current
// Low for link in the current
#define LED_PIO PIO_DEFINE (PORT_C, 2)

int main (void)
{
//	int count = 1;
    system_init ();
	PORTC= (1<<2);
	
	pio_config_set(LEDMAT_COL1_PIO,PIO_OUTPUT_LOW);
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
	
    while (1)
    {
		pio_output_low(LEDMAT_COL1_PIO);    
		pio_output_low(LEDMAT_ROW1_PIO);
		pio_output_low(LEDMAT_ROW2_PIO);
		pio_output_low(LEDMAT_ROW3_PIO);
		pio_output_low(LEDMAT_ROW5_PIO);
		pio_output_low(LEDMAT_ROW6_PIO);
		pio_output_low(LEDMAT_COL3_PIO);
		pio_output_low(LEDMAT_ROW4_PIO);
		pio_output_low(LEDMAT_COL2_PIO);    
		pio_output_low(LEDMAT_COL5_PIO);
		pio_output_low(LEDMAT_COL4_PIO);
		
		pio_output_low(LEDMAT_ROW7_PIO);
		
		//~ if (PIND & (1<<7)){
			//~ pio_output_toggle(LED_PIO);
		//~ }
		//~ while(!PIND & (0<<7)){		//~ }
	//~ 
			
		//~ if (PIND &= (0<<7)){
			//~ count = 0;
		//~ }
		//~ if ((PIND &= (1<<7))&& count == 0){
			//~ PORTC &= ~(1<<2);
			//~ count = 1;
		//~ }
		
        /* TODO.  Use PIO module to turn on LEDs in
           LED matrix.  */

    }
}
