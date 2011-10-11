../../drivers/avr/timer.h: 

../../drivers/avr/timer.c: ../../drivers/avr/timer.h

../../drivers/avr/timer.o: ../../drivers/avr/timer.c

../../drivers/avr/pio.h: 

../../drivers/ledmat.h: 

../../drivers/ledmat.c: ../../drivers/avr/pio.h ../../drivers/ledmat.h

../../drivers/ledmat.o: ../../drivers/ledmat.c

../../drivers/navswitch.h: 

../../drivers/avr/delay.h: 

../../drivers/navswitch.c: ../../drivers/navswitch.h ../../drivers/avr/delay.h ../../drivers/avr/pio.h

../../drivers/navswitch.o: ../../drivers/navswitch.c

../../drivers/display.h: 

../../utils/font.h: 

../../utils/tinygl.h: ../../drivers/display.h ../../utils/font.h

../../utils/tinygl.c: ../../utils/tinygl.h ../../drivers/display.h ../../utils/font.h

../../utils/tinygl.o: ../../utils/tinygl.c

../../utils/pacer.h: 

../../drivers/avr/ir_uart.h: 

../../fonts/font5x7_1.h: ../../utils/font.h

ir_uart_test3.c: ../../drivers/navswitch.h ../../utils/tinygl.h ../../utils/pacer.h ../../drivers/avr/ir_uart.h ../../fonts/font5x7_1.h

ir_uart_test3.o: ir_uart_test3.c

../../utils/font.c: ../../utils/font.h

../../utils/font.o: ../../utils/font.c

../../drivers/avr/pio.c: ../../drivers/avr/pio.h

../../drivers/avr/pio.o: ../../drivers/avr/pio.c

../../utils/pacer.c: ../../drivers/avr/timer.h ../../utils/pacer.h

../../utils/pacer.o: ../../utils/pacer.c

../../drivers/display.c: ../../drivers/ledmat.h ../../drivers/display.h

../../drivers/display.o: ../../drivers/display.c

../../drivers/avr/system.c: 

../../drivers/avr/system.o: ../../drivers/avr/system.c

../../drivers/avr/prescale.h: 

../../drivers/avr/prescale.c: ../../drivers/avr/prescale.h

../../drivers/avr/prescale.o: ../../drivers/avr/prescale.c

../../drivers/avr/usart1.h: 

../../drivers/avr/timer0.h: 

../../drivers/avr/ir_uart.c: ../../drivers/avr/ir_uart.h ../../drivers/avr/usart1.h ../../drivers/avr/timer0.h ../../drivers/avr/pio.h

../../drivers/avr/ir_uart.o: ../../drivers/avr/ir_uart.c

../../drivers/avr/bits.h: 

../../drivers/avr/timer0.c: ../../drivers/avr/timer0.h ../../drivers/avr/bits.h ../../drivers/avr/prescale.h

../../drivers/avr/timer0.o: ../../drivers/avr/timer0.c

../../drivers/avr/usart1.c: ../../drivers/avr/usart1.h

../../drivers/avr/usart1.o: ../../drivers/avr/usart1.c

ir_uart_test3.out: ../../drivers/avr/timer.o ../../drivers/ledmat.o ../../drivers/navswitch.o ../../utils/tinygl.o ir_uart_test3.o ../../utils/font.o ../../drivers/avr/pio.o ../../utils/pacer.o ../../drivers/display.o ../../drivers/avr/system.o ../../drivers/avr/prescale.o ../../drivers/avr/ir_uart.o ../../drivers/avr/timer0.o ../../drivers/avr/usart1.o

