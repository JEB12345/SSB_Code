/* 
 * File:   power_clock.h
 * Author: Jonathan
 *
 * Created on March 18, 2014
 */

#ifndef POWER_CLOCK_H
#define	POWER_CLOCK_H
#include "power_state.h"
#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * @brief clock_init() Initalizes the dspic33E clock to 70Mips or 70MHz
     *
     * @return The function will return RET_OK if inatlization completed
     */
    return_value_t clock_init();

#ifdef	__cplusplus
}
#endif

#endif	/* POWER_CLOCK_H */

