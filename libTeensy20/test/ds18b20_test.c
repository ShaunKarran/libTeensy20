/*	Library:		libTeensy20
 *	Purpose:		Test for DS18B20
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#include <avr/io.h>
#include <stdint.h>

#include "../include/bitwise.h"
#include "../include/ds18b20.h"
#include "../include/global_defines.h"
#include "../include/lcd_5110.h"

int main(void) {
	uint16_t tempurature = 0;

	cpu_speed(CPU_8Mhz);
	lcd_init(LCD_DEFAULT_CONTRAST);

	set_output(DDRD, PD6);
	set_bit(PORT, PD6);

	while(1)
	{
		if(ds18_reset())
		{
			ds18_write_byte(0xCC);
			ds18_write_byte(0x44);
			while (ds18_read_byte() == 0) { ; }
			if (ds18_reset())
			{
				ds18_write_byte(0xCC);
				ds18_write_byte(0xBE);
				tempurature = ds18_read_byte();
				tempurature = ds18_read_byte() << 8;
				lcd_print_int(tempurature);
				if (tempurature < 21)
				{
					set_bit(PORTB, PB6);
				} else
				{
					clr_bit(PORTB, PB6);
				}
			} else
			{
				lcd_print_str("Reset 2 Failed");
			}
		} else
		{
			lcd_print_str("Reset Failed");
		}
	}

	return 0;
}