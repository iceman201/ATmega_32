/** @file   font.h
    @author M. P. Hayes, UCECE
    @date   1 March 2007
    @brief  Font definition.
*/

#ifndef FONT_H
#define FONT_H

#include "system.h"

typedef const uint8_t font_data_t;

/** Font structure.  */
typedef const struct
{
    /** Flags for future options.  */
    uint8_t flags;
    /** Width of font element.  */
    uint8_t width;
    /** Height of font element.  */
    uint8_t height;
    /** Index of first entry in font.  */
    uint8_t offset;
    /** Number of font entries in table.  */
    uint8_t size;
    /** Number of bytes per font entry.  */
    uint8_t bytes;
    /** Font element data.  */
    font_data_t data[];
} font_t;


/** Return the first character in the font.  */
#define FONT_FIRST(font) ((font)->offset)

/** Return the last character in the font.  */
#define FONT_LAST(font) ((font)->offset + (font)->size - 1)


#endif
