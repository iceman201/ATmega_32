/** 
    @brief Display module for pong game.
*/

#ifndef DISPLAY_H
#define DISPLAY_H

/* Initialise the LED matrix */
void display_init ();

/* Display an 'S' character on the LED Matrix */
void display_transmitting ();

/* Display an 'R' character on the LED Matrix */
void display_recieving ();

/* Display an 'W' character indicating a win */
void display_win ();

/* Display an 'L' character indicating a loss */
void display_loss ();

/* refresh the game display */
void display_update ();

#endif
