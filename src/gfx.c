// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Basic graphics functions for use with a single dimensional
 *					array buffer.
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

// Includes -------------------------------------------------------------------

#include <avr/pgmspace.h>
#include <stdint.h>
#include <stdlib.h>

#include "../include/gfx.h"
#include "../include/bitwise.h"

static uint16_t lcdX;
static uint16_t lcdY;
static uint32_t gfxBufferSize;

unsigned char* gfxBuffer;

// Function Definitions -------------------------------------------------------

/*
 * Initialises the display size and allocates the graphics buffer.
 *
 * @param unsigned char** gfx buffer
 *      Pointer to the graphics buffer.
 *
 * @param uint16_t xPixels
 *      Number of horizontal pixels.
 *
 * @param uint16_t yPixels
 *      Number of vertical pixels.
 *
 * @return void
*/
void gfx_init(unsigned char** gfxBuffer, uint16_t xPixels, uint16_t yPixels) {
	lcdX = xPixels;
	lcdY = yPixels;
	gfxBufferSize = lcdX * lcdY;

	*gfxBuffer = malloc(sizeof(char) * gfxBufferSize);
}

/*
 * Sets/clears a pixel in the buffer at the (x, y) position.
 *
 * @param unsigned char x
 *      Horizontal position of the pixel.
 *
 * @param unsigned char y
 *      Vertical position of the pixel.
 *
 * @param unsigned char* buffer
 *		Array of chars representing the screen.
 *
 * @return void
*/
void gfx_set_pixel(unsigned char x, unsigned char y, unsigned char* buffer) 
{
	uint16_t bufferPosition;

	if (x >= 0 && x < lcdX && y >= 0 && y < lcdY) {		// Check pixel location is allowed
		bufferPosition = ((y / 8) * lcdX) + x;			// y / 8 finds row. * 8 moves to start of that row.
		set_bit(buffer[bufferPosition], (y % 8));
	}
}

void gfx_clr_pixel(unsigned char x, unsigned char y, unsigned char* buffer) 
{
	uint16_t bufferPosition;

	if (x >= 0 && x < lcdX && y >= 0 && y < lcdY) {		// Check pixel location is allowed
		bufferPosition = ((y / 8) * lcdX) + x; 			// y / 8 finds row. * 8 moves to start of that row.
		clr_bit(buffer[bufferPosition], (y % 8));
	}
}

/*
 * Returns the state of a pixel in the buffer at the (x, y) position.
 *
 * @param unsigned char x
 *      Horizontal position of the pixel.
 *
 * @param unsigned char y
 *      Vertical position of the pixel.
 *
 * @param unsigned char* buffer
 *		Array of chars representing the screen.
 *
 * @return unsigned char
 *		The state of the pixel (1 or 0)
 *
*/
unsigned char gfx_get_pixel(unsigned char x, unsigned char y, unsigned char* buffer) 
{
	uint16_t bufferPosition;

	if (x >= 0 && x < lcdX && y >= 0 && y < lcdY) {		// Check pixel location is allowed
		bufferPosition = ((y / 8) * lcdX) + x; 			// y / 8 finds row. * 8 moves to start of that row.
		return get_bit(buffer[bufferPosition], (y % 8));
	}
	return -1;
}

/*
 * Draws a line in the buffer from (x1, y1) to (x2, y2).
 *
 * @param unsigned char x1
 *      Horizontal position of the start of the line.
 *
 * @param unsigned char y1
 *      Vertical position of the start of the line.
 *
 * @param unsigned char x2
 *      Horizontal position of the end of the line.
 *
 * @param unsigned char y2
 *      Vertical position of the end of the line.
 *
 * @param unsigned char* buffer
 *		Array of chars representing the screen.
 *
 * @return void
 *
*/
void gfx_draw_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char* buffer) 
{
	char dx = abs(x2 - x1);
	char dy = abs(y2 - y1);
	char error = dx - dy;
	char error2;
	char shiftX = (x1 < x2) ? 1 : -1; // Shift x and y in the correct direction based on line direction
	char shiftY = (y1 < y2) ? 1 : -1;

	while (1) 
	{
		gfx_set_pixel(x1, y1, buffer);

		if ((x1 == x2) && (y1 == y2))
		{
			break;
		}

		// Shift the x and/or y position based on accumulated error
		error2 = 2 * error;
		if (error2 > -dy) 
		{
			error -= dy;
			x1 += shiftX;
		}
		if (error2 < dx) 
		{
			error += dx;
			y1 += shiftY;
		}
	}
}

/*
 * Draws a circle in the buffer centred at the point (x, y).
 *
 * @param unsigned char x
 *      Horizontal position of the centre of the circle.
 *
 * @param unsigned char y
 *      Vertical position of the centre of the circle.
 *
 * @param unsigned char radius
 *      Radius of the circle in pixels.
 *
 * @param unsigned char* buffer
 *		Array of chars representing the screen.
 *
 * @return void
 *
*/
void gfx_draw_circle(unsigned char x, unsigned char y, unsigned char radius, unsigned char* buffer) 
{
	char xDist, yDist, error;

	xDist = radius;
	yDist = 0;
	error = 1 - xDist; // Used to determine if the 'slow direction' should increment.

	if (x < 84 && x > -1 && y > -1) 
	{
		while (xDist >= yDist) 
		{
			// Algorithm only draws a single octant. Each line draws a differnt octant.
			// Draws the left and right 'sides' of the circle.
			gfx_set_pixel(x + xDist, y + yDist, buffer);
			gfx_set_pixel(x - xDist, y + yDist, buffer);
			gfx_set_pixel(x + xDist, y - yDist, buffer);
			gfx_set_pixel(x - xDist, y - yDist, buffer);

			// Draws the top and bottom of the circle.
			gfx_set_pixel(x + yDist, y + xDist, buffer);
			gfx_set_pixel(x - yDist, y + xDist, buffer);
			gfx_set_pixel(x + yDist, y - xDist, buffer);
			gfx_set_pixel(x - yDist, y - xDist, buffer);

			// Increment y ('fast direction') and determine if x should be incremented.
			yDist++;
			if (error > 0) 
			{
				xDist--;
				error += 2 * (yDist - xDist + 1);
			} else {
				error += 2 * yDist + 1;
			}
		}
	}
}

/*
 * Draws a sprite in the buffer.
 *
 * @param unsigned char x
 *      Horizontal position of the centre of the circle.
 *
 * @param unsigned char y
 *      Vertical position of the centre of the circle.
 *
 * @param unsigned char* buffer
 *		Array of chars representing the screen.
 *
 * @return void
 *
*/
void gfx_draw_sprite(unsigned char* sprite, unsigned char x, unsigned char y, unsigned char* buffer) 
{
	// TODO
	// for (int i = 0; i < spriteWidth; i++)
	// {
	// 	for (int j = 0; j < spriteHeight; j++)
	// 	{
	// 		if (pgm_read_byte(&sprite))
	// 		{

	// 		}
	// 		gfx_set_pixel(x + i, y + j, buffer);
	// 	}
	// }
}