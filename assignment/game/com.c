/** 

*/

#include "com.h"
#include "ir_uart.h"

#define DIR_POSITION 3
#define LOSS_POSITION 5

/*
 
*/

void send_ball (const int row, const int dir){
	ir_uart_putc((char)(row & (dir << DIR_POSITION)))
}

void receive_ball (const int row, const int dir) {
	ir_uart_getc((char)(row & (dir << DIR_POSITION)))
}

void sent_loss (void){
	ir_uart_putc((char)(1<<LOSS_POSITION))
}


