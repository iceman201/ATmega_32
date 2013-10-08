#include "basic_function.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

int start_disaplay (int LOOP_RATE, int MESSAGE_RATE)
{
    pacer_init (LOOP_RATE);
	tinygl_init (LOOP_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set(MESSAGE_RATE);
	tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
	tinygl_text("D&L PONG GAME, PUSH START\0");
	while(1){
		pacer_wait();
		tinygl_update ();
	}
	return 0;
}

int you_lose(int LOOP_RATE, int MESSAGE_RATE)
{
    pacer_init (LOOP_RATE);
	tinygl_init (LOOP_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set(MESSAGE_RATE);
	tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
	tinygl_text("HAHA YOU LOSE\0");
	while(1){
		pacer_wait();
		tinygl_update ();
	}
	return 0;
}

int check_lose (int ball_x, int ball_y, int pad_y)
{
	if (ball_x == 3 && ball_y == pad_y)
	{
		return 1;
	}
	else if (ball_x == 3 && ball_y != pad_y)
	{
		return 0;
	}
}
