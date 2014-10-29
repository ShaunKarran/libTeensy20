/*	Library:		libTeensy20
 *	Purpose:		Setup timers
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#ifndef _timer_h
#define _timer_h

#define TIMER_PRESCALE_1	1
#define TIMER_PRESCALE_8	2
#define TIMER_PRESCALE_64	3
#define TIMER_PRESCALE_256	4
#define TIMER_PRESCALE_1024	5

#define TIMER_OCR_A 0
#define TIMER_OCR_B 1
#define TIMER_OCR_C 2

void timer1_ovf_init(unsigned char prescaler);

void timer1_freq_Hz(unsigned char hz);

void timer1_freq_ms(unsigned char ms);

#endif // _timer_h