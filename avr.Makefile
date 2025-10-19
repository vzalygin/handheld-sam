OBJS=reciter.o sam.o render.o debug.o main.o
CC=avr-gcc
OBJCOPY=avr-objcopy

F_CPU=16000000UL# 16MHz
MCU=atmega64# atmega64
SECTIONS=-Wl,-Map=handheld-sam.map,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff# All memory sections are located in external memory, ~59KB

CFLAGS=-Wall -Os -mmcu=$(MCU) -DF_CPU=${F_CPU} -DNODEBUG -gdwarf-2 -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
LFLAGS=-mmcu=$(MCU)

avr-sam: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(SECTIONS) -o avr-sam.elf
	$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature avr-sam.elf avr-sam.hex

%.o: src/%.c dep
	$(CC) -o $@  $(CFLAGS) -MD -MP -MT $@ -MF dep/$@.d -c $<

dep:
	mkdir dep

clean:
	rm -fr *.o *.hex *.elf *.map dep
