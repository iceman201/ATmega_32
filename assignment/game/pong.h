/** @file pong.h

    @brief helper module for the pong game

    This module contains some functions to abstract complexity from the main game program.
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
} pong_message_t;

/* Different states of the program */
typedef enum 
{
    STATE_SETUP_SENDING,
    STATE_SETUP_RECIEVING,
    STATE_PLAYING,
    STATE_FINISH_WON,
    STATE_FINISH_LOST
} pong_state_t;

/* Borders of the board */
typedef enum
{
    MIN_Y =  0,
    MAX_Y =  6,
    MIN_X = -4,
    MAX_X =  3
} pong_border_t;

/* The pad controlled by the player */
typedef struct _pad 
{
    tinygl_point_t pos;
} pong_pad_t;

/* The ball */
typedef struct _ball 
{
    tinygl_point_t pos;
    int rowinc;
    int colinc;
} pong_ball_t;

/* Implements the pacer_wait function */
void pong_wait (void);

/** Turns the blue LED on */
void pong_led_on (void);

/** Turns the blue LED off */
void pong_led_off (void);

/** Transmits a message over IR 
    @param pong_message m message */
void pong_send (pong_message_t m);

/** Tries to recieve a message over IR 
    @return pong_message m message */
pong_message_t pong_get (void);

/** Displays a loss message on the LED Matrix 
    and frequently send a loss message.
    !!This function blocks indefinitely!! */
void pong_lose (void);

/** Displays a win message on the LED Matrix.
    !!This function blocks indefinitely!! */
void pong_win (void);

/** Initialize stuff */
void pong_init (uint16_t rate);

#endif