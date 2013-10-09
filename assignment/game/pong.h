/** @file basic_function.h
    @brief Infrared (IR) communications for pong.

    This module implements and IR communication system
    for the UCFK4 for playing a game similar to pong
    across two boards.
*/

#ifndef PONG_H
#define PONG_H

#include "led.h"
#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"

/* Messages to be sent between boards */
typedef enum
{
    MESSAGE_SENDING = 'A',
    MESSAGE_RECIEVING = 'B',
    MESSAGE_PLAYING = 'C',
    MESSAGE_LOST = 'D'
} pong_message;

/* Different states of the program */
typedef enum 
{
    STATE_SETUP_SENDING,
    STATE_SETUP_RECIEVING,
    STATE_PLAYING,
    STATE_FINISH_WON,
    STATE_FINISH_LOST
} pong_state;

/* The pad controlled by the player */
typedef struct _pad 
{
    tinygl_point_t pos;
} pong_pad;

/* The ball */
typedef struct _ball 
{
    tinygl_point_t pos;
} pong_ball;

/* Implements the pacer_wait function */
void pong_wait (void);

/** Turns the blue LED on */
void pong_led_on (void);

/** Turns the blue LED off */
void pong_led_off (void);

/** Transmits a message over IR 
    @param pong_message m message */
void pong_send (pong_message m);

/** Tries to recieve a message over IR 
    @return pong_message m message */
pong_message pong_get (void);

/** Displays a loss message on the LED Matrix 
    and frequently send a loss message.
    !!This function blocks indefinitely!! */
void pong_lose (void);

/** Displays a win message on the LED Matrix.
    !!This function blocks indefinitely!! */
void pong_win (void);

/** Initialize stuff */
void pong_init (uint8_t rate);

#endif