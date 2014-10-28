/*	Library:		libTeensy20
 *	Purpose:		Drive Nokia 5110 LCD
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#include <stdint.h>

#ifndef _lcd_5110_h
#define _lcd_5110_h

// Pixel numbers
#define LCD_X 84
#define LCD_Y 48
#define LCD_PIXELS (LCD_X * LCD_Y)

// Pins
#define LCD_SCLK PF7	// Serial clock input.
#define LCD_SDIN PB6	// Serial Data Input. Sampled on rising edge of SCLK.
#define LCD_DC PB5		// Tells the LCD if sending DATA or COMMAND.
#define LCD_RST PB4		// Reset device. Active LOW.
#define LCD_SCE PD7		// Chip Enable. Allows data to be clocked in. Active LOW.

// Commands
#define CMD_BASIC_INST 0x20
#define CMD_EXT_INST 0x21
#define CMD_TMP_CTRL 0x04
#define CMD_BIAS 0x14
#define CMD_DISP_NORM 0x0C

// LCD Contrast levels
#define LCD_LOW_CONTRAST		0x2F
#define LCD_DEFAULT_CONTRAST	0x3F
#define LCD_HIGH_CONTRAST		0x4F

#define LCD_DATA 1
#define LCD_CMD 0

void lcd_init(unsigned char contrast);

void lcd_clear(void);

void lcd_goto(uint8_t x, uint8_t y);

void lcd_write_byte(unsigned char dc, unsigned char data);

void lcd_print_char(unsigned char character);

void lcd_print_str(unsigned char* str);

void lcd_print_int(int32_t value);

void lcd_print_double(double value);

#endif // _lcd_5110_h