/*	Library:		libTeensy20
 *	Purpose:		Setup timers
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#include <stdint.h>

#include "../include/timer.h"

void timer1_ovf(unsigned char prescaler) {
	TCCR1B |= prescaler;
    TCNT1 = 0; // Start timer at 0.
    SET_BIT(TIMSK1, TOIE1); // Enable overflow interrupt.
}

void timer1_freq_Hz(unsigned char hz, unsigned char ocr) {
	uint32_t ocrValue;
    int prescale[] = { 1, 8, 64, 256, 1024};
    int i = 0;

    do {
        // ocr = (clk / (prescale * desiredFreq)) - 1
        ocrValue = (16000000 / (prescale[i] * interruptFreq)) - 1;
        i++;
    } while (ocrValue > 65535); // While ocrValue is too large, try larger prescaler.

    TCNT1 = 0; // Set counter to 0.
    TCCR1B |= i; // Set prescaler.
    set_bit(TCCR1B, WGM12); // Set CTC mode.

    if (ocr == TIMER_OCR_A) {
    	OCR1A = ocrValue; // Set compare A value.
    	set_bit(TIMSK1, OCIE1A); // Enable compare A interrupt.

    } else if (ocr == TIMER_OCR_B) {
    	OCR1B = ocrValue; // Set compare A value.
    	set_bit(TIMSK1, OCIE1B); // Enable compare A interrupt.

    } else if (ocr == TIMER_OCR_C) {
    	OCR1C = ocrValue; // Set compare A value.
    	set_bit(TIMSK1, OCIE1C); // Enable compare A interrupt.
    }
}

void timer1_freq_ms(unsigned char ms) {
	// TODO
}