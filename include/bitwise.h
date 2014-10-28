/*	Library:		libTeensy20
 *	Purpose:		Bitwise macros
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#ifndef _bitwise_h
#define _bitwise_h

#define set_bit(reg, pin) 		(reg |= (1 << pin))
#define clr_bit(reg, pin) 		(reg &= ~(1 << pin))
#define tog_bit(reg, pin)		(reg ^= (1 << pin))
#define get_bit(reg, pin) 		(reg & (1 << pin))

// For data direction registers.
#define set_output(reg, pin)	(reg |= (1 << pin))
#define set_input(reg, pin)		(reg &= ~(1 << pin))

#endif // _bitwise_h