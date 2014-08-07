/* 
 * File:   power_adc.h
 * Author: jonathan
 *
 * Created on March 25, 2014, 8:52 AM
 */

#ifndef POWER_ADC_H
#define	POWER_ADC_H

#include <p33Exxxx.h>

#include "power_state.h"

/**
 * Initializes ADC channels 6, 7, 8, 11
 * CH6: 5V5 Rail
 * CH7: 22.4V Rail
 * CH8: Switch
 * CH11: Battery Current
 * @return
 */
return_value_t init_adc();
void Delay_us(unsigned int delay);

#endif	/* POWER_ADC_H */

