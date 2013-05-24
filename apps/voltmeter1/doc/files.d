../../drivers/avr/timer.h: 

../../drivers/avr/timer.c: ../../drivers/avr/timer.h

../../drivers/avr/timer.o: ../../drivers/avr/timer.c

../../drivers/avr/system.c: 

../../drivers/avr/system.o: ../../drivers/avr/system.c

../../utils/task.h: ../../drivers/avr/timer.h

../../drivers/display.h: 

../../utils/font.h: 

../../utils/tinygl.h: ../../drivers/display.h ../../utils/font.h

adc.h: 

../../fonts/font3x5_1.h: ../../utils/font.h

voltmeter1.c: ../../utils/task.h ../../utils/tinygl.h adc.h ../../fonts/font3x5_1.h

voltmeter1.o: voltmeter1.c

../../utils/font.c: ../../utils/font.h

../../utils/font.o: ../../utils/font.c

../../drivers/avr/pio.h: 

../../drivers/avr/delay.h: 

adc.c: ../../drivers/avr/pio.h ../../drivers/avr/delay.h adc.h

adc.o: adc.c

../../drivers/avr/pio.c: ../../drivers/avr/pio.h

../../drivers/avr/pio.o: ../../drivers/avr/pio.c

../../drivers/ledmat.h: 

../../drivers/display.c: ../../drivers/ledmat.h ../../drivers/display.h

../../drivers/display.o: ../../drivers/display.c

../../drivers/ledmat.c: ../../drivers/avr/pio.h ../../drivers/ledmat.h

../../drivers/ledmat.o: ../../drivers/ledmat.c

../../utils/tinygl.c: ../../utils/tinygl.h ../../drivers/display.h ../../utils/font.h

../../utils/tinygl.o: ../../utils/tinygl.c

../../utils/task.c: ../../utils/task.h ../../drivers/avr/timer.h

../../utils/task.o: ../../utils/task.c

voltmeter1.out: ../../drivers/avr/timer.o ../../drivers/avr/system.o voltmeter1.o ../../utils/font.o adc.o ../../drivers/avr/pio.o ../../drivers/display.o ../../drivers/ledmat.o ../../utils/tinygl.o ../../utils/task.o

