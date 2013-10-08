/** @file com.h
    @brief Infrared (IR) communications for pong.

    This module implements and IR communication system
    for the UCFK4 for playing a game similar to pong
    across two boards.
*/
int start_disaplay (int LOOP_RATE, int MESSAGE_RATE);
int check_lose (int ball_x, int ball_y, int pad_y);
int you_lose(int LOOP_RATE, int MESSAGE_RATE);
