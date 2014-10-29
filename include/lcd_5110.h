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

// LCD Buffer
#define LCD_BUFFER_SIZE (LCD_PIXELS / 8)

extern unsigned char lcdBuffer[LCD_BUFFER_SIZE];

/*
 * Initialises the LCD display. Sets up the pins connected to the display and sets
 * initial settings for the display.
 *
 * @param unsigned char contrast
 *      Contrast setting of display.
 *      Can be LCD_LOW_CONTRAST or LCD_Default_CONTRAST or LCD_HIGH_CONTRAST
 *
 * @return void
*/
void lcd_init(unsigned char contrast);

/*
 * Clears the display by writing 0's to all pixels.
 *
 * @return void
*/
void lcd_clear(void);

/*
 * Moves the LCDs built in cursor to the defined position.
 *
 * @param unsigned char x
 *      Horizontal position of the cursor. Range: 0 to 83
 *
 * @param unsigned char y
 *      Vertial position of the cursor. Range: 0 to 5
 *
 * @return void
*/
void lcd_goto(unsigned char x, unsigned char y);

/*
 * Writes a byte of data to the screen.
 *
 * @param unsigned char dc
 *      Define if sending data or command.
 *		Can be LCD_DATA or LCD_CMD
 *
 * @param unsigned char data
 *      Data to be sent.
 *		If dc == LCD_DATA then pixels will be written in a vertial line at the current position
 *		of the LCDs cursor. The cursor will automatically move to the next position on completion.
 *
 * @return void
*/
void lcd_write_byte(unsigned char dc, unsigned char data);

/*
 * Prints an ASCII character to the display at the cursors current location.
 *
 * @param unsigned char character
 *      Character to be printed on the display. Must be a printable ASCII character.
 *
 * @return void
*/
void lcd_print_char(char character);

/*
 * Prints a string to the display at the cursors current location.
 *
 * @param unsigned char* string
 *      Char array to be printed to the display. Must contain printble ASCII characters.
 *
 * @return void
*/
void lcd_print_str(char* string);

/*
 * Prints a long int to the display at the cursors current location.
 *
 * @param int32_t value
 *      Int to be printed on the display. Range: –2,147,483,648 to 2,147,483,647
 *
 * @return void
*/
void lcd_print_int(int32_t value);

/*
 * Prints a float to the display at the cursors current location.
 *
 * @param float value
 *      float to be printed on the display. Range: 3.4E +/- 38 (7 digits)
 *
 * @return void
*/
void lcd_print_float(float value);

/*
 * Sends the contents of the buffer to the display and clears the buffer.
 *
 * @param unsigned char* buffer
 *      Buffer to be displayed and then cleared.
 *
 * @return void
*/
void lcd_display_buffer(unsigned char* buffer);

/*
 * Clears the buffer by writing all 0's.
 *
 * @param unsigned char* buffer
 *      Buffer to be cleared.
 *
 * @return void
*/
void lcd_clear_buffer(unsigned char* buffer);

#endif // _lcd_5110_h