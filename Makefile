###############################################################################
# Makefile for the project handheld-sam
###############################################################################

## General Flags
PROJECT=handheld-sam
MCU=atmega128a
MCU_SHORT=m128
F_CPU=8000000UL

#Dirs
BUILDDIR=build
SRCDIR=src
INCLUDEDIR=include

# Source files
SOURCES=$(SRCDIR)/debug_sam.c $(SRCDIR)/main.c $(SRCDIR)/memmanagment.c $(SRCDIR)/reciter.c $(SRCDIR)/ReciterTabs.c $(SRCDIR)/render.c $(SRCDIR)/RenderTabs.c $(SRCDIR)/sam.c $(SRCDIR)/SamTabs.c $(SRCDIR)/uart.c

# Objects and deps
TARGET=$(BUILDDIR)/$(PROJECT).elf
TARGET_HEX=$(BUILDDIR)/$(PROJECT).hex
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
DEPS=$(OBJECTS:.o=.d)

## Compilers
CC =avr-gcc
CPP=avr-g++

## Options common to compile, link and assembly rules
COMMON=-mmcu=$(MCU)

## Compile options
CFLAGS=$(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DF_CPU=$(F_CPU) -Os \
          -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MF $(BUILDDIR)/$(*F).d
CFLAGS += -I$(INCLUDEDIR)

## Assembly specific flags
ASMFLAGS=$(COMMON) $(CFLAGS) -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS=$(COMMON)
LDFLAGS += -Wl,--section-start=.noinit=0x801100,--defsym=__heap_start=0x802100,--defsym=__heap_end=0x80ffff

## Hex/Eep flags
HEX_FLASH_FLAGS=-R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS=-j .eeprom \
                   --set-section-flags=.eeprom="alloc,load" \
                   --change-section-lma .eeprom=0 \
                   --no-change-warnings

## Build all
all: $(TARGET) \
     $(TARGET:.elf=.hex) \
     $(TARGET:.elf=.eep) \
     $(TARGET:.elf=.lss) \
     size

## Ensure build directory exists
$(BUILDDIR):
	mkdir $(BUILDDIR)

## Compile all .c → build/*.o
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

## Link
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -Wl,-Map,$(TARGET:.elf=.map) $(OBJECTS) $(LIBDIRS) $(LIBS) -o $@

## Make HEX
$(BUILDDIR)/%.hex: $(BUILDDIR)/%.elf
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS) $< $@

## EEPROM HEX
$(BUILDDIR)/%.eep: $(BUILDDIR)/%.elf
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

## LSS
$(BUILDDIR)/%.lss: $(BUILDDIR)/%.elf
	avr-objdump -h -S $< > $@

size: $(TARGET)
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

flash: all
	avrdude -c usbasp -p $(MCU_SHORT) -U flash:w:$(TARGET_HEX):i

## Clean
.PHONY: clean
clean:
	-rm -rf $(BUILDDIR)

## Include dependency files
-include $(DEPS)
