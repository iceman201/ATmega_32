/** @file com.h
    @brief Infrared (IR) communications for pong.

    This module implements and IR communication system
    for the UCFK4 for playing a game similar to pong
    across two boards.
*/

#ifndef COM_H
#define IR_SERIAL_H



#endif



void send_ball (const int row, const int dir);
/* for sent the byte which is the ball position */

void receive_ball (const int row, const int dir);
/* for receive the byte which is the ball position */

void sent_loss (void);
/* sent the loss signnal to opposite player if the player loss*/

void sent_start (void);

