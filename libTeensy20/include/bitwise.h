// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Bitwise macros
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#ifndef _bitwise_h
#define _bitwise_h

// Macros ----------------------------------------------------------------

#define set_bit(reg, bit) 		(reg |= (1 << bit))
#define clr_bit(reg, bit) 		(reg &= ~(1 << bit))
#define tog_bit(reg, bit)		(reg ^= (1 << bit))
#define get_bit(reg, bit) 		(reg & (1 << bit))

// For data direction registers.
#define set_output(reg, bit)	(reg |= (1 << bit))
#define set_input(reg, bit)		(reg &= ~(1 << bit))	

#endif // _bitwise_h