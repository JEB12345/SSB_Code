/* 
 * File:   power_spi.h
 * Author: jonathan
 *
 * Created on October 10, 2014, 11:42 AM
 */

#ifndef POWER_SPI_H
#define	POWER_SPI_H

#include "power_pindef.h"


#define SG_SELECT       RF_CSN=0
#define SG_DESELECT     RF_CSN=1

#ifdef	__cplusplus
extern "C" {
#endif

return_value_t init_RF_spi();

void init_RF_device_RX();

void init_RF_device_TX();

unsigned char spi1_send_read_byte(unsigned char byte);


#ifdef	__cplusplus
}
#endif

#endif	/* POWER_SPI_H */

