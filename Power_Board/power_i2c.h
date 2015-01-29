/* 
 * File:   power_i2c.h
 * Author: ken
 *
 * Created on January 28, 2015, 7:44 PM
 *
 * Generic interrupt based i2c routines.
 *
 */

#ifndef POWER_I2C_H
#define	POWER_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Initializes the I2C module
     * @return
     */
return_value_t i2c_1_init();

/**
 * Schedules an I2C write operation
 * @param address 7 bit address of the slave device
 * @param command 8 bit command (register)
 * @param num_bytes the number of bytes to write
 * @param output pointer to data to write
 * @param status_out stores the result of the operation (RET_OK or RET_ERROR),
 * this can be used by the user to check the state of the operation
 * @return RET_OK if the write operation been successfully scheduled,
 * else RET_ERROR
 */
return_value_t i2c_1_write(uint8_t address, uint8_t command, uint16_t num_bytes,
        uint8_t* output, return_value_t* status_out);

/**
 * Schedules an I2C read operation
 * @param address 7 bit address of the slave device
 * @param command 8 bit command (register)
 * @param num_bytes the number of bytes to read
 * @param output pointer to store the read data
 * @param status_out stores the result of the operation (RET_OK or RET_ERROR),
 * this can be used by the user to check the state of the operation
 * @return RET_OK if the read has been successfully scheduled, else RET_ERROR
 */
return_value_t i2c_1_read(uint8_t address, uint8_t command, uint16_t num_bytes,
        uint8_t* output, return_value_t* status_out);


#ifdef	__cplusplus
}
#endif

#endif	/* POWER_I2C_H */

