/** @file   pio.h
    @author M. P. Hayes, UCECE
    @date   11 Jan 2006
    @brief  PIO hardware abstraction for AVR microcontroller.

    @defgroup pio PIO driver
       
    This module implements a driver for general purpose I/O ports.
    Its purpose is to provide a microcontroller independent
    abstraction of a PIO pin.  Here's an example:

    @code
    #include "pio.h"
    
    #define LED_PIO PIO_DEFINE (PORT_B, 5)

    void main (void)
    {
        system_init ();
        pio_config_set (LED_PIO, PIO_OUTPUT_LOW);

        pio_output_high (LED_PIO);

        while (1);
    }
    @endcode

    In this example, when port B5 is configured as an output it is set
    low.
*/
#ifndef PIO_H
#define PIO_H

#include "system.h"
#ifdef AVR
#include <avr/io.h>
#endif


/** Define port names; note not all the ports are available on some AVRs.  */

enum {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G};

typedef uint16_t pio_t;


/** Define PIO pin types.  The two flavours of PIO_OUTPUT are to
    ensure the port is configured without glitching due to the time
    taken before calling pio_output_set.  */
typedef enum pio_config_enum 
{
    PIO_INPUT = 1,          /** Configure as input pin.  */
    PIO_PULLUP,             /** Configure as input pin with pullup enabled.  */
    PIO_OUTPUT_LOW,         /** Configure as output, initially low.  */
    PIO_OUTPUT_HIGH,        /** Configure as output, initially high.  */
} pio_config_t;


#ifdef DEBUG

/* Define a PIO as a structure in terms of a port and a bit.  */
#define PIO_DEFINE(PORT, PORTBIT) ((PORT) * 8 + (PORTBIT))


/** Configure pio.
    @param pio PIO to configure
    @param config PIO configuration type
    @return non-zero for success.  */
bool pio_config_set (pio_t pio, pio_config_t config);


/** Return pio configuration
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


/** Get output state of pio. 
    @param pio
    @return output state of pio  */
bool pio_output_get (pio_t pio);


/** Set pio to desired state.
    @param pio
    @param state value to write pio  */
void pio_output_set (pio_t pio, bool state);

#else

/* Use fast PIO implementation instead.  */
#include "pio_fast.h"

#endif

#endif
