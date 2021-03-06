// Information ----------------------------------------------------------------

/*  Library:        libTeensy20
 *  Purpose:        Sprites
 *  Author(s):      Shaun Karran
 *  Created:        October 2014
*/

/* Sprite Format
 *
 * Sprites are stored as one dimensional arrays of chars. Each char represents
 * a vertical line of 8 pixels with the LSB at the top. Each char is positioned
 * on the screen to the right of the previous.
 *
 * The first byte is the size of the x dimension (in pixels) of the sprite.
 * The second byte is the vertical size (in chars) of the sprite.
 * The bytes following the width and height are the sprite itself.
*/

// Includes -------------------------------------------------------------------

#include <avr/pgmspace.h>

#ifndef _SPRITES_H
#define _SPRITES_H

// Sprites --------------------------------------------------------------------

static const unsigned char sprite_tank[] PROGMEM = 
{
    0x05, 0x01,
    0x06, 0x06, 0x07, 0x06, 0x06
};

static const unsigned char sprite_smile[] PROGMEM = 
{
	0x14, 0x02,
	0x06, 0x06, 0x30, 0x20, 0x40, 0xCC, 0x8C, 0x80, 0x00, 0xE0, 0x20, 0xE0, 0x20, 0xEC, 0x8C, 0x60, 0x20, 0x30, 0x00, 0x06, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

#endif //_SPRITES_H
