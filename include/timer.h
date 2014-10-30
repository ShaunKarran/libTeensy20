/*	Library:		libTeensy20
 *	Purpose:		Setup timers
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#ifndef _timer_h
#define _timer_h

// Defines --------------------------------------------------------------------
#define TIMER_PRESCALE_1	1
#define TIMER_PRESCALE_8	2
#define TIMER_PRESCALE_64	3
#define TIMER_PRESCALE_256	4
#define TIMER_PRESCALE_1024	5

// Output compare registers
#define TIMER_OCR_A 0
#define TIMER_OCR_B 1
#define TIMER_OCR_C 2

// Function Prototypes --------------------------------------------------------
void timer0_ovf_init(unsigned char prescaler);

void timer0_freq_Hz(uint32_t hz, unsigned char ocr);

void timer0_freq_ms(uint16_t ms, unsigned char ocr);

void timer1_ovf_init(unsigned char prescaler);

void timer3_ovf_init(unsigned char prescaler);

void timer1_freq_Hz(uint32_t hz, unsigned char ocr);

void timer3_freq_Hz(uint32_t hz, unsigned char ocr);

void timer1_freq_ms(uint16_t ms, unsigned char ocr);

void timer3_freq_ms(uint16_t ms, unsigned char ocr);

#endif // _timer_h