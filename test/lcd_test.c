/*	Library:		libTeensy20
 *	Purpose:		Test for lcd_5110
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#include "../include/lcd_5110.h"

int main(void) {

	lcd_init(LCD_DEFAULT_CONTRAST);

	lcd_goto(0, 0);
	lcd_print_str("Test String123");

	lcd_goto(0, 5);
	lcd_print_int(2123456789L);

	while(1) { ; }

	return 0;
}