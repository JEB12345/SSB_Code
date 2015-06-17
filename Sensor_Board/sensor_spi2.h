/* 
 * File:   sensor_spi2.h
 * Author: jonathan
 *
 * Created on June 9, 2015, 11:18 AM
 */

#ifndef SENSOR_SPI2_H
#define	SENSOR_SPI2_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Configures the SPI2 module to operate at 2.5Mhz
 */
void config_spi2_slow();

/**
 * Configures the SPI2 module to operate at 14Mhz
 */
void config_spi2_fast();


#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_SPI2_H */

