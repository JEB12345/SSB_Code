/* 
 * File:   sensor_loadcell.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:57 PM
 */

#ifndef SENSOR_LOADCELL_H
#define	SENSOR_LOADCELL_H
#include "sensor_state.h"
#include "sensor_pindefs.h"
#ifdef	__cplusplus
extern "C" {
#endif


    return_value_t loadcell_init();
    void loadcell_start();

#define SG_SELECT       SS=0
#define SG_DESELECT     SS=1

#define SG_REG_COMM 0b0
#define SG_REG_STATUS 0b0
#define SG_REG_MODE 0b001000
#define SG_REG_CONFIG 0b010000
#define SG_REG_DATA 0b011000
#define SG_REG_ID 0b100000
#define SG_REG_GPOCON 0b00101000
#define SG_REG_OFFSET 0b110000
#define SG_REG_FULLSCALE 0b111000


#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_LOADCELL_H */

