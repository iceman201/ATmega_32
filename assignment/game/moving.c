#include <stdlib.h>
#include "things.h"
#include "tinygl.h"

tinygl_point_t pos;


void pad_move (int8_t dy)
{
    int8_t other;
    tinygl_point_t newpos;

    newpos = tinygl_point (4, pos.y + dy);
   
    tinygl_draw_point (pos, 0);
    pos = newpos;
    tinygl_draw_point (newpos, 1);
}
