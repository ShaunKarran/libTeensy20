CFLAGS = -std=c99
DEBUG_CFLAGS = -Wall $(CFLAGS)
TARGET = bin/test.hex
OBJECT = build/test.o
SOURCES =	src/test.c 	\
								\
			lib/gfx.c 			\
			lib/lcd_5110.c 		\
			lib/timer.c 		\
			
MCU = atmega32u4
F_CPU = 8000000UL

all: $(SOURCES)

	@avr-gcc $(CFLAGS) -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) $(SOURCES) -o $(OBJECT)
	@avr-objcopy -O ihex $(OBJECT) $(TARGET)

	@echo "\nBuild Complete.\n"

debug: $(SOURCES)

	@avr-gcc $(DEBUG_CFLAGS) -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) $(SOURCES) -o $(OBJECT)
	@avr-objcopy -O ihex $(OBJECT) $(TARGET)

	@echo "\nDebug Build Complete.\n"

clean:

	@rm $(OBJECT)
	@rm $(TARGET)

	@echo "\n$(OBJECT) Removed.\n$(TARGET) Removed.\n"

# Use -I to include librarys from multiple directories.
# Starting a line with @ will stop it from echoing in the console.