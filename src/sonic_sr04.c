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
#include "../include/sonic_sr04.h"
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
    set_output(DDRC, SONIC_TRIGGER);
    set_input(DDRC, SONIC_ECHO);

    clr_bit(PORTC, SONIC_TRIGGER);

    timer1_ovf(TIMER_PRESCALE_64);
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
    double deltaTime;

    // Send trigger signal.
    set_bit(PORTC, SONIC_TRIGGER);
    _delay_us(10);
    clr_bit(PORTC, SONIC_TRIGGER);

    // Wait for echo signal to start.
    while (!get_bit(PINC, SONIC_ECHO)) { ; }
    TCNT1 = 0;

    // Measure echo length.
    while (get_bit(PINC, SONIC_ECHO) && TCNT1 < 2941) { ; }
    deltaTime = TCNT1 * 0.000008; // TCNT1 counts up once every 8us.

    return (uint16_t)(deltaTime * 34000) / 2; // distance = (time(secs) * velocity(34000cm/s)) / 2
}
