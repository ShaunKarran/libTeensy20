CFLAGS = -std=c99
TARGET = bin/lcd_test.hex
OBJECT = build/lcd_test.o
SOURCES = test/lcd_test.c src/lcd_5110.c
MCU = atmega32u4
F_CPU = 16000000UL

all: $(SOURCES)

	@avr-gcc $(CFLAGS) -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) $(SOURCES) -o $(OBJECT)
	@avr-objcopy -O ihex $(OBJECT) $(TARGET)

	@echo "\nBuild Complete.\n"

clean:

	rm $(OBJECT)
	rm $(TARGET)

# Use -I to include librarys from multiple directories.
# Starting a line with @ will stop it from echoing in the console.