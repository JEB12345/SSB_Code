/* 
 * File:   sensor_state.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:55 PM
 */

#ifndef SENSOR_STATE_H
#define	SENSOR_STATE_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum
        {
            RET_OK = 0,
            RET_ERROR = 1,
            RET_UNKNOWN = 127
        }
    return_value_t;

    typedef enum {
         SPI_IDLE            =0,
         SPI_LED_ON          =1,
         SPI_LED_OFF         =2,
         SPI_ME_READ_ANGLE   =3,
         SPI_ME_READ_ANGLE_2 =4,
         SPI_LED_END         =5,
         SPI_VARIOUS         =6,  //useful during initialization
         SPI_SG_READ_DATA_1  =7,
         SPI_SG_READ_DATA_2  =8,
         SPI_SG_READ_DATA_3  =9,
         SPI_SG_READ_DATA_4  =10,
         SPI_SG_READ_DATA_END =11
    } spi_sg_state_t;

    //#define LC_CIRCULAR_BUFFER_SIZE 3


    /*
    typedef enum  {
        DMA_SPI_LC_IDLE, ///< No reading is being performed.
        DMA_SPI_LC_WRITING_RESET,
        DMA_SPI_LC_WAITING_500us,
        DMA_SPI_LC_WAITING_TO_WRITE_SETTINGS,
        DMA_SPI_LC_WRITING_SETTINGS,
        DMA_SPI_LC_WRITING_INSTRUCTION_2,
        DMA_SPI_LC_WRITING_INSTRUCTION_3,
        DMA_SPI_LC_WAITING_FOR_READOUT,
        DMA_SPI_LC_READING_DEVICES, //We are actually reading the data from the devices
        DMA_SPI_LC_DATA_READY_TO_BE_PROCESSED // We have finished to read the data, and we need to process it to extract actual data in the spi_main function
    } DMA_SPI_LC_state_t;*/


    //maintain all state variables here
    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } imu_data;
    
    typedef struct {
        return_value_t          init_return;
        volatile struct {
          uint16_t AN6;
          uint16_t AN7;
          uint16_t AN8;
          uint16_t AN11;
        } values;
    } adc_data;

    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } can_data;

    typedef struct {
        return_value_t          init_return;
        //sets the color of the RGB led
        uint8_t                 rgb_red;
        uint8_t                 rgb_green;
        uint8_t                 rgb_blue;
    } led_data;

    /*typedef struct DMA_SPI_LC_read_value{
    unsigned char DATA[3];
    unsigned char STATUS;
} DMA_SPI_LC_read_value;*/


    typedef struct {
        return_value_t          init_return;
        uint32_t volatile       values[4];
        uint8_t volatile           data_ready; //data available was signalled by ADC
        volatile uint16_t spi_state;
        volatile uint16_t sg_data_1, sg_data_2, sg_data_3; //received data (SPI)
        volatile uint16_t sg_status;
        uint32_t volatile       num_measurements[4]; //counts the number of measurements received per channel
    } loadcell_data;

    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } rf_data;

    typedef struct {
        return_value_t          init_return;
        unsigned int volatile   systime; //updated by a timer
        unsigned int            prev_systime;  //updated in main loop
    } timer_data;

    typedef enum {STATE_UNKNOWN = 0, STATE_INITIALIZED = 1, STATE_ERROR = 127} state_t;
    typedef struct {
        return_value_t          init_return;
        state_t volatile state; //system state
    } system_data;

    typedef struct {
        return_value_t          init_return;
        uint32_t                fcy;
    } clock_data;

    /*typedef struct {
        return_value_t          init_return;
        uint8_t                 cur_state;
        uint8_t                 prev_state;
        uint16_t volatile       last_update_tmr;
        unsigned volatile       direction; //0 not moving, 1 positive, 2 negative
    } hallsensor_data;*/
    /*
    typedef struct {
        return_value_t          init_return;
        uint16_t volatile       rotor_position;
        uint16_t volatile       rotor_turns;
        float volatile          rotor_state;
        float volatile          rotor_state_interpolated;
        float volatile          rotor_speed; //in sectors/s (60deg/s)
        float                   wire_length;
    } motor_data;
    */
    return_value_t state_init();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_STATE_H */

