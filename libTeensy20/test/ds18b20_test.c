/*	Library:		libTeensy20
 *	Purpose:		Test for DS18B20
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "../include/bitwise.h"
#include "../include/ds18b20.h"
#include "../include/global_defines.h"
#include "../include/lcd_5110.h"

int main(void) {
	uint16_t tempurature = 0;

	cpu_speed(CPU_8Mhz);
	lcd_init(LCD_DEFAULT_CONTRAST);

	while(1)
	{
		lcd_goto(0, 0);

		if(ds18_reset())
		{
			ds18_write_byte(0xCC);
			ds18_write_byte(0x44);
			while (ds18_read_byte() == 0)
			{
				lcd_goto(0, 0);
				lcd_print_str("Converting...");
				lcd_clear();
			}
			if (ds18_reset())
			{
				ds18_write_byte(0xCC);
				ds18_write_byte(0xBE);
				// tempurature = ds18_read_byte();
				// tempurature |= ds18_read_byte() << 8;
				// lcd_print_int(tempurature);
				lcd_print_int(ds18_read_byte());
				lcd_goto(0, 1);
				lcd_print_int(ds18_read_byte());
			} else
			{
				lcd_print_str("Reset 2 Failed");
			}
		} else
		{
			lcd_print_str("Reset Failed");
		}

		lcd_clear();
	}

	return 0;
}