/*	Library:		libTeensy20
 *	Purpose:		Test for HC_SR04
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "../include/global_defines.h"
#include "../include/lcd_5110.h"
#include "../include/sonic_sr04.h"

int main(void) {
	uint16_t dist;
	uint16_t testCount = 0;

	cpu_speed(CPU_8Mhz);
	lcd_init(LCD_DEFAULT_CONTRAST);
	sonic_init();

	while(1)
	{
		lcd_clear();

		dist = sonic_dist_mm();
		
		lcd_goto(25, 2); lcd_print_int(dist);

		_delay_ms(100);
	}

	return 0;
}
