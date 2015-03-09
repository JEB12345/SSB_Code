/* 
 * File:   power_killswitch.h
 * Author: ken
 *
 * Created on March 3, 2015, 5:43 PM
 */

#ifndef POWER_KILLSWITCH_H
#define	POWER_KILLSWITCH_H

#include "power_state.h"

#ifdef	__cplusplus
extern "C" {
#endif

return_value_t killswitch_init();
void killswitch_update();

#ifdef	__cplusplus
}
#endif

#endif	/* POWER_KILLSWITCH_H */

