# Set cpu speed to 8000000, 16000000(overclock) Hz.
CPU_SPEED = 8000000

AVRFLAGS = -mmcu=atmega32u4 -Os -DF_CPU=$(CPU_SPEED)

# Flags for both C and C++.
CXXFLAGS = -I./src -I./include

# Flags for C only.
CFLAGS = -std=c99

# Flags for C++ only. Use second if first doesnt work.
CPPFLAGS = -std=c++11
#CPPFLAGS = -std=c++0x

# Compilers
CC = avr-gcc
CPP = avr-g++
OBJCOPY = avr-objcopy

# Useful directories.
TARGETDIR = bin
BUILDDIR = build
SOURCEDIR = src

# Sources files separated by language.
CFILES = $(wildcard $(SOURCEDIR)/*.c)
CPPFILES = $(wildcard $(SOURCEDIR)/*.cpp)

# List of source files with file type changed to .o
SOURCES = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

# List of object files for each source file.
OBJS = $(foreach src,$(SOURCES),$(BUILDDIR)/$(notdir $(src)))

all:
	$(CC) $(AVRFLAGS) $(CFLAGS) $(CFILES) test/ds18b20_test.c -I ./include -o build/build.o
	$(CC) $(AVRFLAGS) -nostartfiles $(BUILDDIR)/build.o -o $(TARGETDIR)/build.elf
	$(OBJCOPY) -O ihex $(TARGETDIR)/build.elf $(TARGETDIR)/build.hex

clean:
	rm $(BUILDDIR)/build.o
	rm $(TARGETDIR)/build.elf
	rm $(TARGETDIR)/build.hex

	@echo "Objects and targets removed."
