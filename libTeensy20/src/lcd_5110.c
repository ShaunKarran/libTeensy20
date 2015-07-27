// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Drive Nokia 5110 LCD
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

// Includes -------------------------------------------------------------------

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "../include/lcd_5110.h"
#include "../include/bitwise.h"
//#include "../assets/ASCII_lib.h"

// Function Definitions -------------------------------------------------------

/*
 * Configures the pins connected to the display.
 *
 * @param unsigned char contrast
 *      Contrast setting of display.
 *      Can be LCD_LOW_CONTRAST or LCD_Default_CONTRAST or LCD_HIGH_CONTRAST
 *
 * @return void
*/
static void lcd_config(void) 
{
    // Setup LCD pins for output
    set_output(DDRF, LCD_SCLK);
    set_output(DDRB, LCD_SDIN);
    set_output(DDRB, LCD_DC);
    set_output(DDRB, LCD_RST);
    set_output(DDRD, LCD_SCE);

    // Reset pulse and set SCE HIGH. MUST BE DONE following power on
    clr_bit(PORTB, LCD_RST);
    set_bit(PORTB, LCD_RST);
    set_bit(PORTD, LCD_SCE);
}

/*
 * Initialises the LCD display.
 *
 * @param unsigned char contrast
 *      Contrast setting of display.
 *      Can be LCD_LOW_CONTRAST or LCD_Default_CONTRAST or LCD_HIGH_CONTRAST
 *
 * @return void
*/
void lcd_init(unsigned char contrast) 
{
    lcd_config();

    lcd_write_byte(LCD_CMD, CMD_EXT_SET); // H to 1 to use extended intruction set
    lcd_write_byte(LCD_CMD, 0x80 | contrast); // Set Vop
    lcd_write_byte(LCD_CMD, CMD_TMP_CTRL); // Set Temp Coefficient
    lcd_write_byte(LCD_CMD, CMD_BIAS); // LCD Bias

    lcd_write_byte(LCD_CMD, CMD_B_SET); // H to 0 to use normal intructions
    lcd_write_byte(LCD_CMD, CMD_DISP_NORM); // Set Display control

    lcd_goto(0, 0);
    lcd_clear();
}

/*
 * Clears the display by writing 0's to all pixels.
 *
 * @return void
*/
void lcd_clear(void) 
{
	for (int i = 0; i < (LCD_X * LCD_Y / 8); i++) 
    {
        lcd_write_byte(LCD_DATA, 0x00);
    }
}

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
void lcd_goto(unsigned char x, unsigned char y) 
{
	lcd_write_byte(LCD_CMD, 0x40 | y);
    lcd_write_byte(LCD_CMD, 0x80 | x);
}

/*
 * Writes a byte of data to the screen.
 *
 * @param unsigned char dc
 *      Define if sending data or command.
 *      Can be LCD_DATA or LCD_CMD
 *
 * @param unsigned char data
 *      Data to be sent.
 *      If dc == LCD_DATA then pixels will be written in a vertial line at the current position
 *      of the LCDs cursor. The cursor will automatically move to the next position on completion.
 *
 * @return void
*/
void lcd_write_byte(unsigned char dc, unsigned char data) 
{
    // Tell the LCD that we are writing either to data or a command
    if (dc) 
    {
        set_bit(PORTB, LCD_DC);
    } else 
    {
        clr_bit(PORTB, LCD_DC);
    }

    // Set SCE LOW for sending of data
    clr_bit(PORTD, LCD_SCE);

    // Send data to SDIN starting from MSB
    for (int i = 7; i >= 0; i--) 
    {

        clr_bit(PORTF, LCD_SCLK);

        if (get_bit(data, i)) 
        {
            set_bit(PORTB, LCD_SDIN);
        } else 
        {
            clr_bit(PORTB, LCD_SDIN);
        }

        set_bit(PORTF, LCD_SCLK);
    }

    // Reset SCE to HIGH.
    set_bit(PORTD, LCD_SCE);
}

/*
 * Prints an ASCII character to the display at the cursors current location.
 *
 * @param unsigned char character
 *      Character to be printed on the display. Must be a printable ASCII character.
 *
 * @return void
*/
// void lcd_print_char(char character) 
// {
// 	for (int i = 0; i < 5; i++) 
//     {
//         lcd_write_byte(LCD_DATA, pgm_read_byte(&ASCII[character - 0x20][i]));
//     }
//     lcd_write_byte(LCD_DATA, 0x00); // Empty line between characters.
// }

/*
 * Prints a string to the display at the cursors current location.
 *
 * @param unsigned char* string
 *      Char array to be printed to the display. Must contain printble ASCII characters.
 *
 * @return void
*/
void lcd_print_str(char* str) 
{
	int i = 0;
    
    while (str[i] != '\0') 
    {
        lcd_print_char(str[i]);
        i++;
    }
}

/*
 * Prints a long int to the display at the cursors current location.
 *
 * @param int32_t value
 *      Int to be printed on the display. Range: –2,147,483,648 to 2,147,483,647
 *
 * @return void
*/
void lcd_print_int(int32_t value) 
{
	char str[11];
    sprintf(str, "%ld", value);
    lcd_print_str(str);
}

/*
 * Prints a float to the display at the cursors current location.
 *
 * @param float value
 *      float to be printed on the display. Range: 3.4E +/- 38 (7 digits)
 *
 * @return void
*/
// void lcd_print_float(float value) 
// {
// 	// TODO
// }

/*
 * Sends the contents of the buffer to the display and clears the buffer.
 *
 * @param unsigned char* buffer
 *      Buffer to be displayed and then cleared.
 *
 * @return void
*/
void lcd_display_buffer(unsigned char* buffer) 
{
    lcd_goto(0, 0);

    for (int i = 0; i < LCD_BUFFER_SIZE; i++) 
    {
        lcd_write_byte(LCD_DATA, buffer[i]);
    }
}
