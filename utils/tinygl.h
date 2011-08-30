/** @file   tinygl.h
    @author M. P. Hayes, UCECE
    @date   24 August 2010
    @brief  Tiny graphics library.

    @defgroup tinygl Tiny graphics library
       
       <h3>Introduction to Tinygl</h3>

       Tinygl is a tiny graphics library for a simple dot matrix
       display.  This file declares the data types and graphics
       primitives provided by tinygl.  The basic graphics primitive is
       a point.  This specifies a pair of (x, y) coordinates on the
       display.  Each point has an associated pixel value.  Currently,
       this can be 0 for off and 1 for on.


       <h3>A simple Tinygl application</h3>

       Here's a simple application that draws a line from (1, 2) to
       (3, 5).  The paced loop runs at 1 kHz and this sets the display
       refresh period to 200 Hz since there are 5 columns.

       @code
       #include "pacer.h"
       #include "tinygl.h"

       void main (void)
       {
           pacer_init (1000);
           tinygl_init (1000);

           tinygl_draw_line (tinygl_point (1, 2), tinygl_point (3, 5));

           while (1)
           {
               pacer_wait ();
               tinygl_update ();
           }
       }
       @endcode

       <h3>A Tinygl text application</h3>

       Here's another simple application that displays a message.

       @code
       #include "pacer.h"
       #include "tinygl.h"
       #include "../fonts/font5x7_1.h"

       void main (void)
       {
           pacer_init (1000);
           tinygl_init (1000);

           tinygl_font_set (&font5x7_1);
           tinygl_text_speed_set (10);
           tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL_LEFT);
           tinygl_text ("HELLO WORLD ");

           while (1)
           {
               pacer_wait ();
               tinygl_update ();
           }
       }
       @endcode

*/

#ifndef TINYGL_H
#define TINYGL_H

#include "system.h"
#include "display.h"
#include "font.h"

/** Define size of display.  */
#define TINYGL_WIDTH DISPLAY_WIDTH
#define TINYGL_HEIGHT DISPLAY_HEIGHT


/** Define a pixel value.  Currently the only supported values are 0
    for off and 1 for on.  */
typedef uint8_t tinygl_pixel_value_t;


/** Define a display coordinate.  Note these are signed to allow
    relative coordinates.  */
typedef int8_t tinygl_coord_t;


/** Define a point as a pair of coordinates.  The display origin is the
    top left corner.  */
typedef struct tinygl_point
{
    tinygl_coord_t x;
    tinygl_coord_t y;
} tinygl_point_t;


/** Define text display modes.  */
typedef enum 
{
    /* Stepping text.  */
    TINYGL_TEXT_MODE_STEP, 
    /** Scrolling text.  */
    TINYGL_TEXT_MODE_SCROLL_LEFT,
    /** Rotated scrolling text.  */
    TINYGL_TEXT_MODE_ROTATE_SCROLL_DOWN,
    /* Stepping rotated text.  */
    TINYGL_TEXT_MODE_ROTATE_STEP
} tinygl_text_mode_t;


/** Construct a point from a pair of coordinates.
    @param x x coordinate
    @param y y coordinate   
    @return point.  */
static inline tinygl_point_t tinygl_point (tinygl_coord_t x, tinygl_coord_t y)
{
    tinygl_point_t point = {x, y};

    return point;
}


/** Display a message repeatedly.
    @param string null terminated message to display.  */
void tinygl_text (const char *string);


/** Set the message update speed.
    @param speed text advance speed (characters per 10 s).  */
void tinygl_text_speed_set (uint8_t speed);


/** Set the message display mode.
    @param mode display mode.  */
void tinygl_text_mode_set (tinygl_text_mode_t mode);


/** Set the font to use for text.
    @param pfont pointer to font description.  */
void tinygl_font_set (font_t *pfont);


/** Draw character using current font.
    @param ch character to draw
    @param offset coordinates of top left position
    @param rotate non-zero to rotate character.  */
void tinygl_draw_char (char ch, tinygl_point_t offset, bool rotate);


/** Draw point.
    @param point coordinates of point
    @param pixel_value pixel value to draw point.  */
void tinygl_draw_point (tinygl_point_t point, tinygl_pixel_value_t pixel_value);


/** Draw line.
    @param point1 coordinates of start of line
    @param point2 coordinates of end of line
    @param pixel_value pixel value to draw line.  */
void tinygl_draw_line (tinygl_point_t point1, tinygl_point_t point2, 
                       tinygl_pixel_value_t pixel_value);


/** Draw box.
    @param tl coordinates of top left corner of box
    @param br coordinates of bottom right of box
    @param pixel_value pixel value to draw box.  */
void tinygl_draw_box (tinygl_point_t tl, tinygl_point_t br,
                      tinygl_pixel_value_t pixel_value);


/** Clear display.  */
void tinygl_clear (void);


/** Update display and advance message.  */
void tinygl_update (void);


/** Initialise things.
    @param rate rate in Hz that tinygl_update called.  */
void tinygl_init (uint16_t rate);


#endif /* TINYGL_H  */
