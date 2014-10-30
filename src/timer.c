/*	Library:		libTeensy20
 *	Purpose:		Setup timers
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

// Includes -------------------------------------------------------------------
#include <stdint.h>

#include "../include/timer.h"

/*
 * Enable timer0 with overflow interrupt
 *
 * @param unsigned char prescaler
 *      Using prescaler defines in timer.h
 *
 * @return void
*/
void timer0_ovf(unsigned char prescaler) {
    TCCR0B |= prescaler;
    TCNT0 = 0; // Start timer at 0.
    SET_BIT(TIMSK0, TOIE0); // Enable overflow interrupt.
}

/*
 * Enable timer0 at desired frequency.
 *
 * @param unsigned char hz
 *      Frequency of interrupt in Hz
 *
 * @param unsigned char ocr
 *      Output compare register to use (only A or B)
 *
 * @return void
*/
void timer0_freq_Hz(uint32_t hz, unsigned char ocr) {
    uint32_t ocrValue;
    int prescale[] = { 1, 8, 64, 256, 1024};
    int i = 0;

    do {
        // ocr = (clk / (prescale * desiredFreq)) - 1
        ocrValue = (16000000 / (prescale[i] * hz)) - 1;
        i++;
    } while (ocrValue > 255); // While ocrValue is too large, try larger prescaler.

    TCCR0B |= i; // Set prescaler.
    set_bit(TCCR0A, WGM01); // Set CTC mode.

    if (ocr == TIMER_OCR_A) {
        OCR0A = ocrValue; // Set compare A value.
        set_bit(TIMSK0, OCIE0A); // Enable compare A interrupt.

    } else if (ocr == TIMER_OCR_B) {
        OCR0B = ocrValue; // Set compare A value.
        set_bit(TIMSK0, OCIE0B); // Enable compare B interrupt.
    }
}

/*
 * Enable timer0 at desired time interval.
 *
 * @param unsigned char ms
 *      Time interval of interrupt in ms
 *
 * @param unsigned char ocr
 *      Output compare register to use (only A or B)
 *
 * @return void
*/
void timer0_freq_ms(uint16_t ms, unsigned char ocr) {
    uint16_t s = ms / 1000; // Interval in seconds
    uint32_t hz = 1 / s; // freq = 1 / period

    timer0_freq_Hz(hz, ocr);
}

/*
 * Enable timer1/timer3 with overflow interrupt
 *
 * @param unsigned char prescaler
 *      Using prescaler defines in timer.h
 *
 * @return void
*/
void timer1_ovf(unsigned char prescaler) {
	TCCR1B |= prescaler;
    TCNT1 = 0; // Start timer at 0.
    SET_BIT(TIMSK1, TOIE1); // Enable overflow interrupt.
}

void timer3_ovf(unsigned char prescaler) {
    TCCR3B |= prescaler;
    TCNT3 = 0; // Start timer at 0.
    SET_BIT(TIMSK3, TOIE3); // Enable overflow interrupt.
}

/*
 * Enable timer1/timer3 at desired frequency.
 *
 * @param unsigned char hz
 *      Frequency of interrupt in Hz
 *
 * @param unsigned char ocr
 *      Output compare register to use
 *
 * @return void
*/
void timer1_freq_Hz(uint32_t hz, unsigned char ocr) {
	uint32_t ocrValue;
    int prescale[] = { 1, 8, 64, 256, 1024};
    int i = 0;

    do {
        // ocr = (clk / (prescale * desiredFreq)) - 1
        ocrValue = (16000000 / (prescale[i] * hz)) - 1;
        i++;
    } while (ocrValue > 65535); // While ocrValue is too large, try larger prescaler.

    TCCR1B |= i; // Set prescaler.
    set_bit(TCCR1B, WGM12); // Set CTC mode.

    if (ocr == TIMER_OCR_A) {
    	OCR1A = ocrValue; // Set compare A value.
    	set_bit(TIMSK1, OCIE1A); // Enable compare A interrupt.

    } else if (ocr == TIMER_OCR_B) {
    	OCR1B = ocrValue; // Set compare A value.
    	set_bit(TIMSK1, OCIE1B); // Enable compare B interrupt.

    } else if (ocr == TIMER_OCR_C) {
    	OCR1C = ocrValue; // Set compare A value.
    	set_bit(TIMSK1, OCIE1C); // Enable compare C interrupt.
    }
}

void timer3_freq_Hz(uint32_t hz, unsigned char ocr) {
    uint32_t ocrValue;
    int prescale[] = { 1, 8, 64, 256, 1024};
    int i = 0;

    do {
        // ocr = (clk / (prescale * desiredFreq)) - 1
        ocrValue = (16000000 / (prescale[i] * hz)) - 1;
        i++;
    } while (ocrValue > 65535); // While ocrValue is too large, try larger prescaler.

    TCCR3B |= i; // Set prescaler.
    set_bit(TCCR3B, WGM32); // Set CTC mode.

    if (ocr == TIMER_OCR_A) {
        OCR3A = ocrValue; // Set compare A value.
        set_bit(TIMSK3, OCIE3A); // Enable compare A interrupt.

    } else if (ocr == TIMER_OCR_B) {
        OCR3B = ocrValue; // Set compare A value.
        set_bit(TIMSK3, OCIE3B); // Enable compare B interrupt.

    } else if (ocr == TIMER_OCR_C) {
        OCR3C = ocrValue; // Set compare A value.
        set_bit(TIMSK3, OCIE3C); // Enable compare C interrupt.
    }
}

/*
 * Enable timer1/timer3 at desired time interval.
 *
 * @param unsigned char ms
 *      Time interval of interrupt in ms
 *
 * @param unsigned char ocr
 *      Output compare register to use
 *
 * @return void
*/
void timer1_freq_ms(uint16_t ms, unsigned char ocr) {
    uint16_t s = ms / 1000; // Interval in seconds
    uint32_t hz = 1 / s; // freq = 1 / period

    timer1_freq_Hz(hz, ocr);
}

void timer3_freq_ms(uint16_t ms, unsigned char ocr) {
    uint16_t s = ms / 1000; // Interval in seconds
    uint32_t hz = 1 / s; // freq = 1 / period

    timer3_freq_Hz(hz, ocr);
}
