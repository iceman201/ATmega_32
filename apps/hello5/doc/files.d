../../drivers/avr/timer.h: 

../../drivers/avr/timer.c: ../../drivers/avr/timer.h

../../drivers/avr/timer.o: ../../drivers/avr/timer.c

../../drivers/navswitch.h: 

../../drivers/display.h: 

../../utils/font.h: 

../../utils/tinygl.h: ../../drivers/display.h ../../utils/font.h

../../utils/pacer.h: 

../../fonts/font3x5_1.h: ../../utils/font.h

hello5.c: ../../drivers/navswitch.h ../../utils/tinygl.h ../../utils/pacer.h ../../fonts/font3x5_1.h

hello5.o: hello5.c

../../drivers/avr/delay.h: 

../../drivers/avr/pio.h: 

../../drivers/navswitch.c: ../../drivers/navswitch.h ../../drivers/avr/delay.h ../../drivers/avr/pio.h

../../drivers/navswitch.o: ../../drivers/navswitch.c

../../drivers/ledmat.h: 

../../drivers/ledmat.c: ../../drivers/avr/pio.h ../../drivers/ledmat.h

../../drivers/ledmat.o: ../../drivers/ledmat.c

../../utils/font.c: ../../utils/font.h

../../utils/font.o: ../../utils/font.c

../../drivers/avr/pio.c: ../../drivers/avr/pio.h

../../drivers/avr/pio.o: ../../drivers/avr/pio.c

../../utils/pacer.c: ../../drivers/avr/timer.h ../../utils/pacer.h

../../utils/pacer.o: ../../utils/pacer.c

../../drivers/display.c: ../../drivers/ledmat.h ../../drivers/display.h

../../drivers/display.o: ../../drivers/display.c

../../utils/tinygl.c: ../../utils/tinygl.h ../../drivers/display.h ../../utils/font.h

../../utils/tinygl.o: ../../utils/tinygl.c

../../drivers/avr/system.c: 

../../drivers/avr/system.o: ../../drivers/avr/system.c

hello5.out: ../../drivers/avr/timer.o hello5.o ../../drivers/navswitch.o ../../drivers/ledmat.o ../../utils/font.o ../../drivers/avr/pio.o ../../utils/pacer.o ../../drivers/display.o ../../utils/tinygl.o ../../drivers/avr/system.o

