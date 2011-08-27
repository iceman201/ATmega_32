CC = gcc
CFLAGS = -O2 -Wall -W -g

FONTDEFS = $(wildcard *.txt)
FONTS = $(FONTDEFS:.txt=.h)


all: fontgen $(FONTS)


%.h: %.txt fontgen
	./fontgen $(@:.h=) < $^  > $@

fontgen: fontgen.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm *.o fontgen
