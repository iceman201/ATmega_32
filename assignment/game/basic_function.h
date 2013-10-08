/** @file basic_function.h
    @brief Infrared (IR) communications for pong.

    This module implements and IR communication system
    for the UCFK4 for playing a game similar to pong
    across two boards.
*/

#define MESSAGE_SENDING 'A'
#define MESSAGE_RECIEVING 'B'
#define MESSAGE_PLAYING 'C'
#define MESSAGE_LOST 'D'

/* 
 * Transmits a message over IR 
 **/
void com_send (char m);

/* 
 * Tries to recieve a message over IR
 * If no message is recieved, returns \0
 **/
char com_get (void);

/* 
 * Displays a loss message.
 * This function blocks the micro.
 */
void display_character (char character);

void you_lose (void);

/* 
 * Displays a win message.
 * This function blocks the micro.
 */
void you_win (void);
