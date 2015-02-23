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
 * Initializes ADC channels 6, 7, 8, 11, 12, 13
 * CH6: 5V5 Rail voltage
 * CH7: 22.4V Rail
 * CH8: Backup battery voltage
 * CH11: Battery Current
 * CH12: Motor voltage (output)
 * CH13: 5V5 Rail current
 * @return
 */
return_value_t init_adc();

/**
 * Updates some internal ADC variables 
 * Call this function at a rate of 1KHz.
 */
void adc_update_state();
/**
 * Updates the "outputs" (kill switch etc.) based on the ADC state
 * Call as fast as possible.
 */
void adc_update_output();
void Delay_us(unsigned int delay);

#endif	/* POWER_ADC_H */

