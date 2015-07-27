// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Drivers to interface with the DS18B20 tempurature sensor
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

// Includes -------------------------------------------------------------------

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "../include/bitwise.h"
#include "../include/ds18b20.h"

// Function Definitions -------------------------------------------------------

uint8_t ds18_reset()
{
	uint8_t tick = 0;

	// Pull gpio pin low for > 480us.
	set_output(REG, PIN);
	clr_bit(REG, PIN);
	_delay_us(500);

	// Release the pin (set as input)
	set_input(REG, PIN);

	// Wait for the sensor to respond (15-60us)
	while (get_bit(REG, PIN) && tick < 60)
	{
		tick++;
		_delay_us(1);
	}

	// The sensor pulls pin low for 60-240us
	if (tick < 60)
	{
		return 1;
	} else 
	{
		return 0;
	}
}

void ds18_write_byte(uint8_t byte)
{
	for (int i = 0; i < 7; i++)
	{
		// Pull gpio pin low for > 1us & < 15us
		set_output(REG, PIN);
		clr_bit(REG, PIN);
		_delay_us(2);

		// Set or clr pin for remaining time to make 60us total
		if (get_bit(byte, i))
		{
			set_bit(REG, PIN);
		}
		_delay_us(58);

		// Release the pin. Must wait >=1us between write slots
		set_input(REG, PIN);
		_delay_us(1);
	}
}

uint8_t ds18_read_byte()
{
	uint8_t byte = 0x00;

	for (int i = 0; i < 7; i++)
	{
		// Pull gpio pin low for > 1us
		set_output(REG, PIN);
		clr_bit(REG, PIN);
		_delay_us(2);

		// Release the pin (set as input) and wait < 15us
		set_input(REG, PIN);
		_delay_us(10);

		// Read gpio pin
		if (get_bit(REG, PIN))
		{
			set_bit(byte, i);
		}

		// Must wait >= 1us between read time slots
		_delay_us(1);
	}
}