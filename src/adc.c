// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Using Analogue to Digital Converter
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

// Includes -------------------------------------------------------------------

#include <avr/io.h>

#include "../include/adc.h"
#include "../include/bitwise.h"

// Function Definitions -------------------------------------------------------

/*
 * Initialise the adc using external voltage reference.
 *
 * @param unsigned char prescaler
 *      ADC prescaler. Optimal operation between 50kHz and 200kHz for 10-bit mode.
 *      Prescaler options defined in adc.h
 *
 * @return void
 *
*/
void adc_init(unsigned char prescaler) 
{
    set_bit(ADMUX, REFS0); // External Vref
    ADCSRA |= prescaler;
    set_bit(ADCSRA, ADEN); // ADC enable
}

/*
 * Performs a single conversion and returns the result.
 *
 * @param unsigned char mode
 *     The mode can be MODE_8_BIT or MODE_10_BIT
 *     if mode == MODE_8_BIT, the resolution will be 256
 *     if mode == MODE_10_BIT, the resolution will be 1024
 * 
 * @return uint16_t
 *     Digital representation of analog signal
*/
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

/*
 * Reads an analog signal and scales the returned value to a value from 0 to multiplier.
 * 
 * @param unsigned char channel
 *     The pin that should be read (0 - 7)
 * 
 * @param unsigned char mode
 *     The mode can be MODE_8_BIT or MODE_10_BIT
 *     if mode == MODE_8_BIT, the resolution will be 256
 *     if mode == MODE_10_BIT, the resolution will be 1024
 *
 * @param uint16_t multiplier
 *     The maximum value you want to scale the read value to
 *     Eg. multiplier of 100 will return a value from 0 to 100
 * 
 * @return uint16_t
 *     Scaled representation of analog signal
*/
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

/*
 * Enables/Disables auto trigger source in free running mode. In this mode
 * the ADC will constantly sample and update the ADC register.
 * 
 * @param unsigned char channel
 *     The pin that should be read (0 - 7)
 * 
 * @param unsigned char enable
 *     Can be either ON or OFF
 *     if enable == ON, the ADC will be enabled in free running mode
 *     if enable == OFF, auto trigger will be disabled and the ADC will stop
 *
 * @return void
*/
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
