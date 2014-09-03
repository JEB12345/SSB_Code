/* 
 * File:   load_cell.h
 * Author: jonas
 *
 * Created on March 26, 2013, 11:07 AM
 */

#ifndef LOAD_CELL_H
#define	LOAD_CELL_H

#include <gpio.h>
#include <libpic30.h>


struct load_cell;

typedef struct load_cell load_cell;




void init_load_cells();
void load_cell_reset();
void load_cell_process();
void load_cell_start_reading();

void lc_load_persistent_sbcp_settings();

typedef enum lc_error_flags {
	LC_F_OK                            = 0 ,
	LC_F_ONBOARD_PROCESSING_UNFINISHED = 1
} lc_error_flags;

int lc_get_torque(load_cell * e);

lc_error_flags lc_get_error(load_cell * e);

extern load_cell * lc1,* lc2,* lc3;

#endif	/* LOAD_CELL_H */

