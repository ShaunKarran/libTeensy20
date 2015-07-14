// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Global definitions and macros
 *	Author(s):		Shaun Karran
 *	Created:		November 2014
*/

#include <avr/io.h>

#ifndef _global_defines_h
#define _global_defines_h

// Definitions ----------------------------------------------------------------

#define CPU_16Mhz 0x00
#define CPU_8Mhz 0x01
#define CPU_4Mhz 0x02
#define CPU_2Mhz 0x03
#define CPU_1Mhz 0x04

// Macros ---------------------------------------------------------------------

#define cpu_speed(clkspd) (CLKPR = 0x80, CLKPR = clkspd)

#endif // _global_defines_h