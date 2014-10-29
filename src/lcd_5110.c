/*	Library:		libTeensy20
 *	Purpose:		Drive Nokia 5110 LCD
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "../include/lcd_5110.h"
#include "../include/bitwise.h"
#include "../include/ASCII_font.h"

void lcd_init(unsigned char contrast) {

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

    lcd_write_byte(LCD_CMD, CMD_EXT_INST); // H to 1 to use extended intruction set
    lcd_write_byte(LCD_CMD, 0x80 | contrast); // Set Vop
    lcd_write_byte(LCD_CMD, CMD_TMP_CTRL); // Set Temp Coefficient
    lcd_write_byte(LCD_CMD, CMD_BIAS); // LCD Bias

    lcd_write_byte(LCD_CMD, CMD_BASIC_INST); // H to 0 to use normal intructions
    lcd_write_byte(LCD_CMD, CMD_DISP_NORM); // Set Display control

    lcd_goto(0, 0);
    lcd_clear();
}

void lcd_clear(void) {

	for (int i = 0; i < (LCD_X * LCD_Y / 8); i++) {
        lcd_write_byte(LCD_DATA, 0x00);
    }
}

void lcd_goto(uint8_t x, uint8_t y) {

	lcd_write_byte(LCD_CMD, 0x40 | y);
    lcd_write_byte(LCD_CMD, 0x80 | x);
}

void lcd_write_byte(unsigned char dc, unsigned char data) {

    // Tell the LCD that we are writing either to data or a command
    if (dc) {
        set_bit(PORTB, LCD_DC);
    } else {
        clr_bit(PORTB, LCD_DC);
    }

    // Set SCE LOW for sending of data
    clr_bit(PORTD, LCD_SCE);

    // Send data to SDIN starting from MSB
    for (int i = 7; i >= 0; i--) {

        clr_bit(PORTF, LCD_SCLK);

        if (get_bit(data, i)) {
            set_bit(PORTB, LCD_SDIN);
        } else {
            clr_bit(PORTB, LCD_SDIN);
        }

        set_bit(PORTF, LCD_SCLK);
    }

    // Reset SCE to HIGH.
    set_bit(PORTD, LCD_SCE);
}

void lcd_print_char(unsigned char character) {

	for (int i = 0; i < 5; i++) {
        lcd_write_byte(LCD_DATA, pgm_read_byte(&ASCII[character - 0x20][i])); // Might need extra set of brackets.
    }
    lcd_write_byte(LCD_DATA, 0x00); // Empty line between characters.
}

void lcd_print_str(unsigned char* str) {

	int i = 0;
    
    while (str[i] != '\0') {
        lcd_print_char(str[i]);
        i++;
    }
}

void lcd_print_int(int32_t value) {
	char string[11];
    sprintf(string, "%ld", value);
    lcd_print_str(string);
}

void lcd_print_double(double value) {
	// TODO
}
