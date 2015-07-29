// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Drive Nokia 5110 LCD
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

// Includes -------------------------------------------------------------------

#include <stdint.h>

#ifndef _lcd_5110_h
#define _lcd_5110_h

// Defines --------------------------------------------------------------------

// Display Dimensions
#define LCD_X 84
#define LCD_Y 48
#define LCD_PIXELS (LCD_X * LCD_Y)

// Pins. Change to suit physical implementation.
#define LCD_SCLK PF7	// Serial clock input
#define LCD_SDIN PB6	// Serial Data Input, sampled on rising edge of SCLK
#define LCD_DC PB5		// Tells the LCD if sending DATA or COMMAND
#define LCD_RST PB4		// Reset device (active LOW)
#define LCD_SCE PD7		// Chip Enable - Allows data to be clocked in (active LOW)

// Commands
#define CMD_B_SET 0x20		// Basic instruction set
#define CMD_EXT_SET 0x21	// Extented instruction set
#define CMD_TMP_CTRL 0x04	// Tempratire coefficient
#define CMD_BIAS 0x14		// Bias value n = 4
#define CMD_DISP_NORM 0x0C	// Normal display mode
#define CMD_DISP_INV 0x0D	// Inverse display mode

// LCD Contrast levels
#define LCD_LOW_CONTRAST		0x2F
#define LCD_DEFAULT_CONTRAST	0x3F
#define LCD_HIGH_CONTRAST		0x4F

#define LCD_DATA 1
#define LCD_CMD 0

// LCD Buffer
#define LCD_BUFFER_SIZE (LCD_PIXELS / 8)

// Function Prototypes --------------------------------------------------------

void lcd_init(unsigned char contrast);

void lcd_clear(void);

void lcd_goto(unsigned char x, unsigned char y);

void lcd_write_byte(unsigned char dc, unsigned char data);

void lcd_print_char(char character);

void lcd_print_str(char* str);

void lcd_print_int(int32_t value);

void lcd_print_float(float value);

void lcd_display_buffer(unsigned char* buffer);

#endif // _lcd_5110_h