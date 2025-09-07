OBJS = reciter.o sam.o render.o main-x86.o debug.o
CC = gcc
CFLAGS = -Wall -Werror -Os -fsanitize=address,undefined
LFLAGS = -fsanitize=address,undefined

sam: $(OBJS)
	$(CC) -o sam.bin $(OBJS) $(LFLAGS)
%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

AVROBJS=reciter.oavr sam.oavr render.oavr debug.oavr main.oavr
AVRCC=avr-gcc
AVROBJCOPY=avr-objcopy
F_CPU=16000000UL# 16MHz
MCU=atmega64# atmega64
SECTIONS=-Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff# All memory sections are located in external memory, ~59KB
AVRCFLAGS=-Wall -Werror -Os -mmcu=$(MCU) -DF_CPU=${F_CPU} -DNODEBUG
AVRLFLAGS=$(AVRCFLAGS)

avr-sam: $(AVROBJS)
	$(AVRCC) $(AVROBJS) $(AVRLFLAGS) $(SECTIONS) -o avr-sam.bin
	$(AVROBJCOPY) -O ihex avr-sam.bin avr-sam.hex
%.oavr: src/%.c
	$(AVRCC) -o $@  $(AVRCFLAGS) -c $<

clean:
	rm -f *.o *.oavr *.hex *.bin
