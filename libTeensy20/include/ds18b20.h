// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Drivers to interface with the DS18B20 tempurature sensor
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#ifndef _ds18b20_h
#define _ds18b20_h

// Defines --------------------------------------------------------------------

// Change to which ever pin the sensor is connected to.
#define PIN	PB1
// Change to DDR register for the given pin.
#define REG DDRB

// Command set - Can be sent using write_byte
#define SKIP_ROM 	0xCC

// Function Prototypes --------------------------------------------------------

uint8_t ds18_reset();

void ds18_write_byte(uint8_t byte);

uint8_t ds18_read_byte();

#endif // _ds18b20_h