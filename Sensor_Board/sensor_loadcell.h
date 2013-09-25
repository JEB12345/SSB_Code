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
    //void loadcell_reset();
    //void loadcell_process();
    void loadcell_start();

#define SG_SELECT       SS=0
#define SG_DESELECT     SS=1

#define SG_REG_COMM 0b0
#define SG_REG_STATUS 0b0
#define SG_REG_MODE 0b001000
#define SG_REG_CONFIG 0b010000
#define SG_REG_DATA 0b011000
#define SG_REG_ID 0b100000
#define SG_REG_GPOCON 0b101000
#define SG_REG_OFFSET 0b110000
#define SG_REG_FULLSCALE 0b111000


//void init_load_cells();
//void load_cell_reset();
//void load_cell_process();
//void load_cell_start_reading();

//void lc_load_persistent_sbcp_settings();

//typedef enum lc_error_flags {
//	LC_F_OK                            = 0 ,
//	LC_F_ONBOARD_PROCESSING_UNFINISHED = 1
//} lc_error_flags;

//int lc_get_torque(load_cell * e);

//lc_error_flags lc_get_error(load_cell * e);

//extern load_cell * lc1,* lc2,* lc3;

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_LOADCELL_H */

