/*	Library:		libTeensy20
 *	Purpose:		Using Analogue to Digital Converter
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
 */

#include <avr/io.h>

#include "../include/adc.h"
#include "../include/bitwise.h"

void adc_init(unsigned char prescaler) 
{
    set_bit(ADMUX, REFS0); // External Vref
    ADCSRA |= prescaler;
    set_bit(ADCSRA, ADEN); // ADC enable
}

uint16_t adc_read(unsigned char channel, unsigned char mode) 
{
    ADMUX |= channel;

    if (mode == ADC_MODE_8_BIT) 
    {
    	set_bit(ADMUX, ADLAR); // Left align for 8-bit mode
    } else 
    {
    	clr_bit(ADMUX, ADLAR); // Right align for 10-bit mode
    }

    set_bit(ADCSRA, ADSC); // ADC start conversion
    while (get_bit(ADCSRA, ADSC)) { ; } // Wait for conversion to finish
    
    if (mode == ADC_MODE_8_BIT) 
    {
    	return ADCH; // Only return the high register.
    } else 
    {
    	return ADC;
    }
}

uint32_t adc_read_scaled(unsigned char channel, unsigned char mode, uint32_t scale) 
{
	uint32_t scaledRead;

	scaledRead = adc_read(channel, mode) * scale;

	if (ADC_MODE_8_BIT) 
    {
		return scaledRead / 255;
	} else 
    {
		return scaledRead / 1023;
	}
}

void adc_freerun(unsigned char channel, unsigned char enable) 
{
    ADMUX |= channel;
    set_bit(ADCSRA, ADATE); // Auto trigger enable, ADTS bits 0 for free running mode
    if (enable) 
    {
        set_bit(ADCSRA, ADSC);
    } else 
    {
        clr_bit(ADCSRA, ADATE);
    }
}
