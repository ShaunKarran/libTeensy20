// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Using the HC-SR04 Ultrasonic Distance Module.
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

// Includes -------------------------------------------------------------------

#include <avr/io.h>
#include <util/delay.h>

#include "../include/bitwise.h"
#include "../include/timer.h"

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
void sonic_init(void)
{
    uint32_t TIME = 0;

    set_output(DDRB, SONIC_TRIGGER);
    set_input(DDRB, SONIC_ECHO);

    timer0_freq_ms(0.001, TIMER_OCR_A);
}

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
uint16_t sonic_dist_mm(void) 
{
    uint16_t echoStart;
    uint16_t echoFinish;
    uint16_t deltaTime;

    TIME = 0;

    // Send trigger signal.
    set_bit(PORTB, SONIC_TRIGGER);
    _delay_us(10);
    clr_bit(PORTB, SONIC_TRIGGER);

    // Wait for echo signal to start.
    while (!get_bit(PINB, SONIC_ECHO)) { ; }

    // Measure echo length.
    echoStart = TIME;
    while(get_bit(PINB, SONIC_ECHO)) { ; }
    echoFinish = TIME;
    deltaTime = echoFinish - echoStart;

    return (deltaTime * SPD_OF_SND * 1000) / 2; // Divide by 2 because time is there and back again.
}

ISR(TIMER0_COMPA_vect)
{
    TIME++;
}
