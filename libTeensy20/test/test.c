/*	Library:		libTeensy20
 *	Purpose:		Test for lcd_5110
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#include <avr/io.h>

int main()
{
	DDRD |= (1 << PD6);
	PORTD |= (1 << PD6);

	while (1) { ; }
	
	return 0;
}