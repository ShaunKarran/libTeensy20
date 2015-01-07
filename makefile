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
OBJCOPY = avr-objcpy

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

all: test
	@echo "$(CFILES)"
	@echo "$(OBJS)"

test: $(OBJS)
	@echo "This is where .hex is created."
	@#@ld -r $(OBJS) -o test.o
	@#@avr-objcopy $(OBJS) -O ihex $(TARGETDIR)/test.hex

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	@echo "Building $< into $@"
	$(CC) $(AVRFLAGS) $(CXXFLAGS) $(CFLAGS) -c $< -o $@ 

# $(TARGETDIR).hex: %.hex

# 	@echo "\nCreating .hex file...\n"

# 	@avr-objcopy -O ihex $(OBJS) $(TARGETDIR).hex

clean:

	@rm $(OBJS)
	#@rm $(TARGETDIR).hex

	@echo "\nObjects and targets removed.\n"
