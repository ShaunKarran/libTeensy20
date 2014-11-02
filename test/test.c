/*	Library:		libTeensy20
 *	Purpose:		Test for lcd_5110
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#include "../include/adc.h"
#include "../include/ASCII_lib.h"
#include "../include/bitwise.h"
#include "../include/lcd_5110.h"
#include "../include/gfx.h"
#include "../include/timer.h"

int main(void) {

	// lcd_5110 Test ----------------------------------------------------------
	lcd_init(LCD_DEFAULT_CONTRAST);

	lcd_goto(0, 0);
	lcd_print_str("Test String123");

	lcd_goto(0, 5);
	lcd_print_int(2123456789L);


	// lcd_gfx Test -----------------------------------------------------------
	gfx_init(LCD_X, LCD_Y);

	gfx_draw_line(3, 6, 65, 40, lcdBuffer);

	lcd_display_buffer(lcdBuffer);

	while(1) { ; }

	return 0;
}