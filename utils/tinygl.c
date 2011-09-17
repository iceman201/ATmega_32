/** @file   tinygl.c
    @author M. P. Hayes, UCECE
    @date   24 August 2010
    @brief  Tiny graphics library.
*/
#include <string.h>
#include "system.h"
#include "tinygl.h"
#include "display.h"
#include "font.h"


enum {TINYGL_SPEED_DEFAULT = 20};

static uint16_t update_rate;
static uint16_t text_advance_period;
static font_t *font;
static tinygl_text_mode_t text_mode = TINYGL_TEXT_MODE_STEP;
static uint8_t message_index;
static uint8_t scroll_pos = 0;
static char message1[TINYGL_MESSAGE_SIZE] = "";


/** Draw point.
    @param point coordinates of point
    @param pixel_value pixel value for line.  */
void tinygl_draw_point (tinygl_point_t point, tinygl_pixel_value_t pixel_value)
{
    display_pixel_set (point.x, point.y, pixel_value);
}


/** Draw line.
    @param point1 coordinates of start of line
    @param point2 coordinates of end of line
    @param pixel_value pixel value for line.  */
void tinygl_draw_line (tinygl_point_t point1, tinygl_point_t point2,
                       tinygl_pixel_value_t pixel_value)
{
    int dx;
    int dy;
    int x_inc;
    int y_inc;

    /* Draw a line using Bresenham's algorithm.  */

    dx = point2.x - point1.x;
    dy = point2.y - point1.y;

    x_inc = dx >= 0 ? 1 : -1;
    y_inc = dy >= 0 ? 1 : -1;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;

    if (dx >= dy)
    {
        int error;

        error = dx / 2;

        for (; point1.x != point2.x; point1.x += x_inc)
        {
            tinygl_draw_point (point1, pixel_value);

            error -= dy;
            if (error < 0)
            {
                error += dx;
                point1.y += y_inc;
            }
        }
    }
    else
    {
        int error;

        error = dy / 2;
        for (; point1.y != point2.y; point1.y += y_inc)
        {
            tinygl_draw_point (point1, pixel_value);

            error -= dx;
            if (error < 0)
            {
                error += dy;
                point1.x += x_inc;
            }
        }
    }
    tinygl_draw_point (point1, pixel_value);
}


/** Draw box.
    @param tl coordinates of top left corner of box
    @param br coordinates of bottom right of box
    @param pixel_value pixel value for box.  */
void tinygl_draw_box (tinygl_point_t tl, tinygl_point_t br,
                      tinygl_pixel_value_t pixel_value)
{
    tinygl_draw_line (tl, tinygl_point (br.x, tl.y), pixel_value);
    tinygl_draw_line (tl, tinygl_point (tl.x, br.y), pixel_value);
    tinygl_draw_line (tinygl_point (br.x, tl.y), br, pixel_value);
    tinygl_draw_line (tinygl_point (tl.x, br.y), br, pixel_value);
}


/** Clear display.  */
void tinygl_clear (void)
{
    display_clear ();

    /* Stop message display.  */
    message1[0] = 0;
    message_index = 0;
}


/** Determine if pixel on or off.
    @param ch character to display
    @param col column of font element
    @param row row of font element
    @return 1 if pixel on; if pixel out of bounds return 0.  */
static bool tinygl_font_pixel_get (char ch, uint8_t col, uint8_t row)
{
    return font_pixel_get (font, ch, col, row);
}


/** Draw character using current font.
    @param ch character to draw
    @param offset coordinates of top left position
    @param rotate non-zero to rotate character.  */
void tinygl_draw_char (char ch, tinygl_point_t offset, bool rotate)
{
    uint8_t x;
    uint8_t y;

    if (rotate)
    {
        for (x = 0; x < font->height; x++)
        {
            for (y = 0; y < font->width; y++)
            {
                tinygl_draw_point (tinygl_point (x + offset.x, 
                                   TINYGL_HEIGHT - 1 - (y + offset.y)),
                                   tinygl_font_pixel_get (ch, y, x));
            }
        }
    }
    else
    {
        for (x = 0; x < font->width; x++)
        {
            for (y = 0; y < font->height; y++)
            {
                tinygl_draw_point (tinygl_point (x + offset.x, y + offset.y),
                                   tinygl_font_pixel_get (ch, x, y));
            }
        }
    }
}



/** Draw string (well, as much as possible) using current font.
    @param str string to draw
    @param offset coordinates of top left position
    @param rotate non-zero to rotate string
    @return number of whole characters drawn.  */
uint8_t tinygl_draw_string (const char *str, tinygl_point_t offset, bool rotate)
{
    uint8_t count = 0;

    while (*str)
    {
        if (rotate)
        {
            if (offset.y + font->width > TINYGL_HEIGHT)
                break;
            tinygl_draw_char (*str, offset, 1);
            offset.y += font->width + 1;            
        }
        else
        {
            if (offset.x + font->width > TINYGL_WIDTH)
                break;
            tinygl_draw_char (*str, offset, 0);
            offset.x += font->width + 1;
        }
        count++;
        str++;
    }
    return count;
}



/** Display a character.
    @param ch character to display
    @return 1 if character fully displayed.  */
static bool tinygl_display_char (char ch)
{
    uint8_t x;
    uint8_t y;

    if (!font)
        return 0;

    switch (text_mode)
    {
    case TINYGL_TEXT_MODE_SCROLL_LEFT:
        display_scroll_left ();
        
        for (y = 0; y < font->height; y++)
        {
            tinygl_draw_point (tinygl_point (TINYGL_WIDTH - 1, y),
                               tinygl_font_pixel_get (ch, scroll_pos, y));
        }
        break;

    case TINYGL_TEXT_MODE_STEP:
        if (scroll_pos != 0)
            break;

        tinygl_draw_char (ch, tinygl_point (0, 0), 0);
        break;

    case TINYGL_TEXT_MODE_ROTATE_SCROLL_DOWN:
        display_scroll_down ();
        
        for (x = 0; x < font->height; x++)
        {
            tinygl_draw_point (tinygl_point (x, 0),
                               tinygl_font_pixel_get (ch, scroll_pos, x));
        }
        break;

    case TINYGL_TEXT_MODE_ROTATE_STEP:
        if (scroll_pos != 0)
            break;

        tinygl_draw_char (ch, tinygl_point (0, 0), 1);
        break;
    }
        
    scroll_pos++;
    if (scroll_pos > font->width)
        scroll_pos = 0;
    return scroll_pos == 0;
}


/** Advance message.  */
static void tinygl_text_advance (void)
{
    if (!message1[message_index])
    {
        message_index = 0;
    }
    
    if (message1[message_index])
    {
        if (tinygl_display_char (message1[message_index]))
            message_index++;
    }
}


/** Display a message repeatedly.
    @param string null terminated message to display.  */
void tinygl_text (const char *string)
{
    message_index = 0;
    scroll_pos = 0;
    strncpy (message1, string, sizeof (message1));
}


/** Set the message update speed.
    @param speed text advance speed (characters per 10 s).  */
void tinygl_text_speed_set (uint8_t speed)
{
    text_advance_period = update_rate / (speed * TINYGL_WIDTH) * 10;
}


/** Set the message display mode.
    @param mode display mode.  */
void tinygl_text_mode_set (tinygl_text_mode_t mode)
{
    text_mode = mode;
}


/** Set the font to use for text.
    @param pfont pointer to font description.  */
void tinygl_font_set (font_t *pfont)
{
    font = pfont;
}


/** Update display (refresh display and update message).  */
void tinygl_update (void)
{
    static uint16_t tick = 0;

    tick++;
    if (tick >= text_advance_period)
    {
        tick = 0;

        tinygl_text_advance ();
    }

    display_update ();
}


/** Initialise things.
    @param rate rate in Hz that tinygl_update called.  */
void tinygl_init (uint16_t rate)
{
    update_rate = rate;

    display_init ();

    tinygl_text_speed_set (TINYGL_SPEED_DEFAULT);

    tinygl_clear ();
}
