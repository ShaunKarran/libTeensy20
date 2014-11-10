/*	Library:		libTeensy20
 *	Purpose:		Test for lcd_5110
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#include "../include/lcd_5110.h"
#include "../include/lcd_gfx.h"

int main(void) {

	lcd_init(LCD_DEFAULT_CONTRAST);

	gfx_draw_line(3, 6, 65, 40, lcdBuffer);

	lcd_display_buffer(lcdBuffer);

	while(1) { ; }

	return 0;
}