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
 * The bytes following the width and height, and before the null character
 * are the sprite itself.
*/

// Includes -------------------------------------------------------------------

#include <avr/pgmspace.h>

#ifndef _SPRITES_H
#define _SPRITES_H

#include "../include/sprite.h"

// Sprites --------------------------------------------------------------------

const unsigned char sprite_tank[] PROGMEM = 
{
    0x05, 0x01,
    0x06, 0x06, 0x0E, 0x06, 0x06,
    '\0'
};

#endif //_SPRITES_H
