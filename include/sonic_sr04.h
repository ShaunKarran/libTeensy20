// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Using the HC-SR04 Ultrasonic Distance Module.
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

// Includes -------------------------------------------------------------------

#include <stdint.h>

#ifndef _SONIC_SR04_H
#define _SONIC_SR04_H

// Defines --------------------------------------------------------------------

#define SONIC_TRIGGER 	PB6
#define SONIC_ECHO 		PB7
#define SPD_OF_SND 		340 // m/s

// Function Prototypes --------------------------------------------------------

void sonic_init(void);

uint16_t sonic_dist_mm(void);

#endif // _SONIC_SR04_H