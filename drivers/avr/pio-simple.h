/** @file   pio-simple.h
    @author M. P. Hayes, UCECE
    @date   11 Jan 2006
    @brief  PIO hardware abstraction.
*/
#ifndef PIO_H
#define PIO_H

#include "system.h"
#include <avr/io.h>

typedef enum pio_port_enum 
{
    PORT_A, PORT_B, PORT_C, PORT_D, PORT_E
} pio_port_t;

typedef uint8_t pio_bit_t;

typedef struct pio_struct
{
    pio_port_t port;
    pio_bit_t bit;
} pio_t;

typedef enum pio_config_enum 
{
    PIO_INPUT = 1, PIO_OUTPUT_LOW, PIO_OUTPUT_HIGH, PIO_PULLUP
} pio_config_t;


/* Define a PIO as a structure in terms of a port and a bit.  */
#define PIO_DEFINE(PORT, PORTBIT) (pio_t){PORT, PORTBIT}


/** Configure pio.
    @param pio  */
bool pio_config_set (pio_t pio, pio_config_t config);


/** Configure pio.
    @param pio 
    @return config  */
pio_config_t pio_config_get (pio_t pio);


/** Set pio high.
    @param pio  */
void pio_output_high (pio_t pio);


/** Set pio low. 
    @param pio  */
void pio_output_low (pio_t pio);


/** Toggle pio.
    @param pio  */
void pio_output_toggle (pio_t pio);


/** Read input state from pio. 
    @param pio
    @return input state of pio  */
bool pio_input_get (pio_t pio);


/** Set pio to desired state
    @param pio
    @param state value to write pio  */
void pio_output_set (pio_t pio, bool state);


/** Get output state of pio. 
    @param pio
    @return output state of pio  */
bool pio_output_get (pio_t pio);

#endif
