// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Graphics for Nokia 5110 LCD
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#ifndef _lcd_gfx_h
#define _lcd_gfx_h

// Function Prototypes --------------------------------------------------------

void gfx_set_pixel(unsigned char x, unsigned char y, unsigned char* buffer);

void gfx_clr_pixel(unsigned char x, unsigned char y, unsigned char* buffer);

unsigned char gfx_get_pixel(unsigned char x, unsigned char y, unsigned char* buffer);

void gfx_draw_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char* buffer);

void gfx_draw_circle(unsigned char x, unsigned char y, unsigned char radius, unsigned char* buffer);

void gfx_draw_sprite(unsigned char x, unsigned char y, unsigned char* buffer);

#endif // _lcd_gfx_h