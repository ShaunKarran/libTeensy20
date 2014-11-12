/*	Library:		libTeensy20
 *	Purpose:		Test for lcd_5110
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#include <avr/interrupt.h>

#include "../include/adc.h"
#include "../assets/ASCII_lib.h"
#include "../include/bitwise.h"
#include "../include/lcd_5110.h"
#include "../include/global_defines.h"
#include "../include/gfx.h"
#include "../assets/sprites.h"
#include "../include/timer.h"

volatile char TICK = 0;

int main(void) {

	cpu_speed(CPU_8Mhz);

	//timer Test --------------------------------------------------------------
	timer1_freq_ms(250, TIMER_OCR_A);

	//lcd_5110 Test -----------------------------------------------------------
	lcd_init(LCD_DEFAULT_CONTRAST);

	// lcd_goto(0, 0);
	// lcd_print_str("Test String123");

	// lcd_goto(0, 5);
	// lcd_print_int(2123456789L);

	// lcd_gfx Test -----------------------------------------------------------
	gfx_init(LCD_X, LCD_Y);

	while(1)
	{
		gfx_clear_buffer();

		gfx_draw_sprite(sprite_smile, 30, 20);

		gfx_draw_sprite(sprite_tank, TICK, 10);

		lcd_display_buffer(gfxBuffer);
	}

	return 0;
}

ISR(TIMER1_COMPA_vect)
{
	TICK++;
}