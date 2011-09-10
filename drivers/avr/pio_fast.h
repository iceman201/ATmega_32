/** @file   pio-fast.h
    @author M. P. Hayes, UCECE
    @date   11 Jan 2006
    @brief  Fast PIO hardware abstraction for AVR microcontroller.
    @note   Macros and inline functions are used to avoid function
            call overhead and to allow compile-time constant folding. 
*/
#ifndef PIO_FAST_H
#define PIO_FAST_H

#include "system.h"
#ifdef AVR
#include <avr/io.h>
#endif


/** Define a PIO as a unique 16 bit number encoding the low part of
    the PORT address offset in the low byte and the bit mask in the
    high byte.  PORTB is used for the pattern since PORTA is not
    always defined for some AVRs.  */
#define PIO_DEFINE(PORT, PORTBIT) ((((PORT) - PORT_B) * 3) | (BIT(PORTBIT) << 8))


/** Private macro to lookup bitmask.  */
#define PIO_BITMASK_(PIO) ((PIO) >> 8)


/** Private macro to lookup port register.  */
#define PIO_PORT_(PIO) (&PORTB + ((PIO) & 0xff))


/** Private macro to map a pio to its corresponding data direction
   register (DDR).  NB, the DDR and PORT registers must be separated
   by the same number of bytes in all cases.  PORTB is used for the
   pattern since PORTA is not always defined for some AVRs.  */
#define PIO_DDR_(PIO) (*(PIO_PORT_ (PIO) + (&DDRB - &PORTB)))


/** Private macro to map a pio to its input register (PIN).  NB, the
   PIN and PORT registers must be separated by the same number of
   bytes in all cases.  PORTB is used for the pattern since PORTA is
   not always defined for some AVRs.  */
#define PIO_PIN_(PIO) (*(PIO_PORT_ (PIO) + (&PINB - &PORTB)))


/** Private macro to access a pio data register.  */
#define PIO_DATA_(PIO) (*PIO_PORT_ (PIO))


/** Configure pio.
    @param pio PIO to configure
    @param config PIO configuration type
    @return non-zero for success.  */
static inline
bool pio_config_set (pio_t pio, pio_config_t config)
{
    switch (config)
    {
    case PIO_OUTPUT_LOW:
        PIO_DATA_ (pio) &= ~PIO_BITMASK_ (pio);
        PIO_DDR_ (pio) |= PIO_BITMASK_ (pio);
        return 1;

    case PIO_OUTPUT_HIGH:
        PIO_DATA_ (pio) |= PIO_BITMASK_ (pio);
        PIO_DDR_ (pio) |= PIO_BITMASK_ (pio);
        return 1;

    case PIO_INPUT:
        PIO_DDR_ (pio) &= ~PIO_BITMASK_ (pio);
        PIO_DATA_ (pio) &= ~PIO_BITMASK_ (pio);
        return 1;

    case PIO_PULLUP:
        PIO_DDR_ (pio) &= ~PIO_BITMASK_ (pio);
        PIO_DATA_ (pio) |= PIO_BITMASK_ (pio); 
        return 1;

    default:
        return 0;
    }
}


/** Return pio configuration
    @param pio 
    @return config  */
static inline
pio_config_t pio_config_get (pio_t pio)
{
    bool ddr;
    bool port;

    ddr = PIO_DDR_ (pio) & PIO_BITMASK_ (pio);
    port = PIO_DATA_ (pio) & PIO_BITMASK_ (pio);
    
    if (ddr)
    {
        if (port)
            return PIO_OUTPUT_HIGH;
        else
            return PIO_OUTPUT_LOW;
    }
    
    if (port)
        return PIO_PULLUP;
    
    return PIO_INPUT;
}


/** Set pio high.
    @param pio  */
static inline
void pio_output_high (pio_t pio)
{
    PIO_DATA_ (pio) |= PIO_BITMASK_ (pio);
}


/** Set pio low. 
    @param pio  */
static inline
void pio_output_low (pio_t pio)
{
    PIO_DATA_ (pio) &= ~PIO_BITMASK_ (pio);
}


/** Toggle pio.
    @param pio  */
static inline
void pio_output_toggle (pio_t pio)
{
    PIO_DATA_ (pio) ^= PIO_BITMASK_ (pio);
}


/** Read input state from pio. 
    @param pio
    @return input state of pio  */
static inline
bool pio_input_get (pio_t pio)
{
    return (PIO_PIN_ (pio) & PIO_BITMASK_ (pio)) != 0;
}


/** Get output state of pio. 
    @param pio
    @return output state of pio  */
static inline
bool pio_output_get (pio_t pio)
{
    return (PIO_DATA_ (pio) & PIO_BITMASK_ (pio)) != 0;
}


/** Set pio to desired state.
    @param pio
    @param state value to write pio  */
static inline
void pio_output_set (pio_t pio, bool state)
{
    state ? pio_output_high (pio) : pio_output_low (pio);
}
#endif
