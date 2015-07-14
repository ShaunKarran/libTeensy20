// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Graphics for Nokia 5110 LCD
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#ifndef _lcd_gfx_h
#define _lcd_gfx_h

extern unsigned char* gfxBuffer;

// Function Prototypes --------------------------------------------------------

void gfx_init(uint16_t xPixels, uint16_t yPixels);

void gfx_clear_buffer(void);

void gfx_set_pixel(uint16_t x, uint16_t y);

void gfx_clr_pixel(uint16_t x, uint16_t y);

unsigned char gfx_get_pixel(uint16_t x, uint16_t y);

void gfx_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void gfx_draw_circle(uint16_t x, uint16_t y, unsigned char radius);

void gfx_draw_char(char character, const unsigned char font[][5], uint16_t x, uint16_t y);

void gfx_draw_string(char* str, const unsigned char font[][5], uint16_t x, uint16_t y);

void gfx_draw_int(int32_t value, const unsigned char font[][5], uint16_t x, uint16_t y);

void gfx_draw_sprite(const unsigned char* sprite, uint16_t x, uint16_t y);

#endif // _lcd_gfx_h