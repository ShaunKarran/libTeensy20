// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Using Analogue to Digital Converter
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

// Includes -------------------------------------------------------------------

#include <stdint.h>

#ifndef _adc_h
#define _adc_h

// Defines --------------------------------------------------------------------

// Prescaler values (based on 16Mhz clkSpd)
#define ADC_8MHZ 1
#define ADC_4MHZ 2
#define ADC_2MHZ 3
#define ADC_1MHZ 4
#define ADC_500KHZ 5
#define ADC_250KHZ 6
#define ADC_125KHZ 7

// ADC modes of operation.
#define ADC_MODE_8_BIT 0
#define ADC_MODE_10_BIT 1

// Function Prototypes --------------------------------------------------------

void adc_init(unsigned char prescaler);

uint16_t adc_read(unsigned char channel, unsigned char mode);

uint32_t adc_read_scaled(unsigned char channel, unsigned char mode, uint32_t scale);

void adc_freerun(unsigned char channel, unsigned char enable);

#endif // _adc_h