OBJS=reciter.o sam.o render.o main.o debug.o
CC=gcc
CFLAGS=-Wall -Werror -Os -fsanitize=address,undefined
LFLAGS=-fsanitize=address,undefined

sam: $(OBJS)
	$(CC) -o sam $(OBJS) $(LFLAGS)
%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

AVROBJS=reciter.oavr sam.oavr render.oavr debug.oavr
AVRCC=avr-gcc
MCU=avr5 # atmega64
HEAP=--defsym=__heap_start=0x801100,--defsym=__heap_end=0x80ffff # All heap space is located in external memory, ~59KB
AVRCFLAGS = -Wall -Werror -Os -mmcu=$(MCU) -DNODEBUG
AVRLFLAGS = $(AVRCFLAGS) -r -o sam-avr.o -Wl,$(HEAP)

avr-sam: $(AVROBJS)
	$(AVRCC) $(AVROBJS) $(AVRLFLAGS)

%.oavr: src/%.c
	$(AVRCC) -o $@  $(AVRCFLAGS) -c $<

clean:
	rm -f *.o
	rm -f *.oavr
