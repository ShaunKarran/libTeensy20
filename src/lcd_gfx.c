/*	Library:		libTeensy20
 *	Purpose:		Graphics for Nokia 5110 LCD
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#include <stdint.h>
#include <stdlib.h> // For abs()

#include "../include/lcd_gfx.h"
#include "../include/lcd_5110.h"
#include "../include/bitwise.h"

void gfx_set_pixel(unsigned char x, unsigned char y, unsigned char* buffer) {
	uint16_t bufferPosition;

	bufferPosition = ((y / 8) * LCD_X) + x; // y / 8 finds the row. * 8 moves to the start of that row.
	set_bit(buffer[bufferPosition], (y % 8));
}

void gfx_clr_pixel(unsigned char x, unsigned char y, unsigned char* buffer) {
	uint16_t bufferPosition;

	bufferPosition = ((y / 8) * LCD_X) + x; // y / 8 finds the row. * 8 moves to the start of that row.
	clr_bit(buffer[bufferPosition], (y % 8));
}

char gfx_get_pixel(unsigned char x, unsigned char y, unsigned char* buffer) {
	uint16_t bufferPosition;

	bufferPosition = ((y / 8) * LCD_X) + x; // y / 8 finds the row. * 8 moves to the start of that row.
	return get_bit(buffer[bufferPosition], (y % 8));
}

void gfx_draw_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char* buffer) {
	char dx = abs(x2 - x1);
	char dy = abs(y2 - y1);
	char error = dx - dy;
	char error2;
	char shiftX = (x1 < x2) ? 1 : -1; // Shift x and y in the correct direction based on line direction.
	char shiftY = (y1 < y2) ? 1 : -1;

	while (1) {
		gfx_set_pixel(x1, y1, buffer);

		if ((x1 == x2) && (y1 == y2))
			break;

		// Shift the x and/or y position based on accumulated error.
		error2 = 2 * error;
		if (error2 > -dy) {
			error -= dy;
			x1 += shiftX;
		}
		if (error2 < dx) {
			error += dx;
			y1 += shiftY;
		}
	}
}

void gfx_draw_circle(unsigned char x, unsigned char y, unsigned char radius, unsigned char* buffer) {
	char xDist, yDist, error;

	xDist = radius;
	yDist = 0;
	error = 1 - xDist; // Used to determine if the 'slow direction' should increment.

	if (x < 84 && x > -1 && y > -1) {
		while (xDist >= yDist) {
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
			if (error > 0) {
				xDist--;
				error += 2 * (yDist - xDist + 1);
			} else {
				error += 2 * yDist + 1;
			}
		}
	}
}

void gfx_draw_sprite(unsigned char x, unsigned char y, unsigned char* buffer) {
	// TODO
}
