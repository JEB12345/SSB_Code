
#include "sensor_imu.h"
#include "sensor_state.h"
#include "sensor_pindefs.h"
#include "sensor_led.h"
#include <p33Exxxx.h>

imu_data imu_state;

void i2c_scan(); //internal helper function
return_value_t imu_init()
{
    uint8_t temp;
    uint16_t i;
    imu_state.init_return = RET_OK;

    I2C1BRG =165; //400kHz= 1/((1/70000000.)*(165+1)+130ns) = 399771.559
    IFS1bits.MI2C1IF = 0;
    IFS1bits.SI2C1IF = 0;
    IEC1bits.MI2C1IE = 1; //clear interrupts
    IEC1bits.SI2C1IE = 1;
    I2C1CONbits.A10M = 0; //7 bit slave address
    I2C1CONbits.I2CEN = 1; //enable the i2c module
    temp = I2C1RCV; //clear receive buffer

    //clear some bits, just to be sure...
    //I2C1CONbits.RCEN = 0; //receive sequence not in progress
    I2C1STATbits.BCL = 0;
    I2C1STATbits.IWCOL = 0;

    //stop bit to make sure that the module is idle
    I2C1CONbits.PEN = 1;
    while (!I2C1STATbits.P); //wait for hardware clear

    I2C1STATbits.BCL = 0;

    imu_state.i2c_state = IDLE;
    if (I2C1STATbits.RBF)
        temp = I2C1RCV;

    for(i=0;i<10000;i++){
        Nop();
    }
    i2c_scan();

    //check if the gyro/acc chip was found
    if(!imu_state.i2c_dev[IMU_ADDR]){
        imu_state.init_return = RET_ERROR; //not found
    } else {
        //put the module in active mode
        imu_state.i2c_err = IDLE;
        I2C1STATbits.IWCOL = 0;
        imu_state.i2c_state = WAIT_START_WRITE_STATE;
        imu_state.i2c_address = IMU_ADDR<<1;
        I2C1STATbits.BCL = 0;
        imu_state.acc_write_register = 107;
        imu_state.acc_write_num = 1;
        imu_state.acc_write_data[0] = 0b00000000;
        imu_state.acc_write_done = 0;
        I2C1CONbits.SEN = 1; //start i2c transaction
        while (imu_state.i2c_state != IDLE);
        for(i=0;i<1000;++i){
            Nop();
        }
        //put the gyro/acc in pass-through mode so we can check for the magnetometer
        imu_state.i2c_err = IDLE;
        I2C1STATbits.IWCOL = 0;
        imu_state.i2c_state = WAIT_START_WRITE_STATE;
        imu_state.i2c_address = IMU_ADDR<<1;
        I2C1STATbits.BCL = 0;
        imu_state.acc_write_register = 0x6A;
        imu_state.acc_write_num = 1;
        imu_state.acc_write_data[0] = 0b00000000;
        imu_state.acc_write_done = 0;
        I2C1CONbits.SEN = 1; //start i2c transaction
        for(i=0;i<1000;++i){
            Nop();
        }
        while (imu_state.i2c_state != IDLE);
        imu_state.i2c_err = IDLE;
        I2C1STATbits.IWCOL = 0;
        imu_state.i2c_state = WAIT_START_WRITE_STATE;
        imu_state.i2c_address = IMU_ADDR<<1;
        I2C1STATbits.BCL = 0;
        imu_state.acc_write_register = 55;
        imu_state.acc_write_num = 1;
        imu_state.acc_write_data[0] = 0b00000010;
        imu_state.acc_write_done = 0;
        I2C1CONbits.SEN = 1; //start i2c transaction
        while (imu_state.i2c_state != IDLE);

        //if you want to test the address
//        for(i=0;i<1000;++i){
//            Nop();
//        }
//
//        I2C1STATbits.BCL = 0;
//        I2C1CONbits.SEN = 1;
//        imu_state.i2c_err = IDLE;
//        I2C1STATbits.IWCOL = 0;
//        imu_state.i2c_state = WAIT_START_READ_STATE;
//        imu_state.i2c_address = IMU_ADDR<<1;
//        imu_state.i2c_address_2 = (IMU_ADDR<<1)|1;
//        I2C1STATbits.BCL = 0;
//        imu_state.acc_read_register = 117;
//        imu_state.acc_read_num = 1;
//
//        I2C1CONbits.SEN = 1; //start i2c transaction
//        while (imu_state.i2c_state != IDLE);
//
//        if(imu_state.acc_read_data[0]==0x68){
//            LED_1 = 1;
//        } else {
//            LED_1 = 0;
//        }

        i2c_scan();
        //check if we can now find the 6 DOF IMU and the magnetometer
//        LED_3 = imu_state.i2c_dev[IMU_ADDR];
//        LED_4 = imu_state.i2c_dev[MAGNETOMETER_ADDR];
        if(imu_state.i2c_dev[IMU_ADDR] || imu_state.i2c_dev[MAGNETOMETER_ADDR]){
            imu_state.init_return = RET_OK;
        } else {
            imu_state.init_return = RET_ERROR;
        }
    }

    return imu_state.init_return;
}

void imu_read_state(){
    if (imu_state.i2c_state != IDLE)
        return;
    I2C1STATbits.BCL = 0;
    I2C1CONbits.SEN = 1;
    imu_state.i2c_err = IDLE;
    I2C1STATbits.IWCOL = 0;
    imu_state.i2c_state = WAIT_START_READ_STATE;
    imu_state.i2c_address = IMU_ADDR << 1;
    imu_state.i2c_address_2 = (IMU_ADDR << 1) | 1;
    I2C1STATbits.BCL = 0;
    imu_state.acc_read_register = 59;
    imu_state.acc_read_num = 20;

    I2C1CONbits.SEN = 1; //start i2c transaction           
}

void i2c_scan() {
    uint8_t address = 0;
    uint8_t temp;
    uint16_t i;

    for (address = 0; address < 128; ++address) {
        imu_state.i2c_dev[address] = 0;
        while (imu_state.i2c_state != IDLE);
        I2C1STATbits.IWCOL = 0;
        if (I2C1STATbits.RBF)
            temp = I2C1RCV; //clears the RBF flag
        imu_state.i2c_state = WAIT_START_SCAN_STATE;

        imu_state.i2c_address = address<<1;
        imu_state.scan_address = address;

        I2C1STATbits.BCL = 0;
        I2C1CONbits.SEN = 1;

        while (imu_state.i2c_state != IDLE);
        for(i=0;i<1000;++i){
            Nop();
        }
    }
    if(address > 0)
        address = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _MI2C1Interrupt(void) {
    static uint8_t byte_cnt;
    //master interrupt

    switch (imu_state.i2c_state) {
        case GYRO_WAIT_START:
            if (I2C1CONbits.SEN) {
                //something went wrong (this should be low)
                //reset to idle
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_state = IDLE;
            }
            break;
        case WAIT_START_WRITE_STATE:
            if (!I2C1STATbits.S) {
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = WAIT_START_WRITE_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                //send address
                imu_state.i2c_state = ADDRESS_WRITE_STATE;
                I2C1TRN = imu_state.i2c_address;
            }
            break;
        case ADDRESS_WRITE_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = ADDRESS_WRITE_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //send register address
                imu_state.i2c_state = BYTE_WRITE_STATE;
                byte_cnt = 0;
                I2C1TRN = imu_state.acc_write_register;
            }
            break;
        case BYTE_WRITE_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = BYTE_WRITE_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //send data byte
                if (++byte_cnt >= imu_state.acc_write_num) {
                    imu_state.i2c_state = STOP_WRITE_STATE;
                } else {
                    imu_state.i2c_state = BYTE_WRITE_STATE;
                }
                I2C1TRN = imu_state.acc_write_data[byte_cnt - 1];
            }
            break;
        case STOP_WRITE_STATE:
            if (I2C1CONbits.ACKEN) {
                //NACK was not sent: error
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = STOP_WRITE_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_state = IDLE;
                imu_state.acc_write_done = 1; //success
            }
            break;

        case WAIT_START_READ_STATE:
            if (!I2C1STATbits.S) {
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = WAIT_START_READ_STATE;
                imu_state.i2c_state = IDLE;

            } else {
                //send address
                imu_state.i2c_state = ADDRESS_READ_STATE;
                I2C1TRN = imu_state.i2c_address; //0xD2; //0x38; //WRITE
            }
            break;
        case ADDRESS_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = ADDRESS_READ_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //send register address
                imu_state.i2c_state = REGISTER_ADDRESS_READ_STATE;
                I2C1TRN = imu_state.acc_read_register;
            }
            break;
        case REGISTER_ADDRESS_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = REGISTER_ADDRESS_READ_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //send a repeated start bit
                imu_state.i2c_state = RS_READ_STATE;
                I2C1CONbits.RSEN = 1; //repeated start bit
            }
            break;
        case RS_READ_STATE:
        {
            //send device address with read
            imu_state.i2c_state = REGISTER_ADDRESS_READ_READ_STATE;
            I2C1TRN = imu_state.i2c_address_2; //0xD3;//0x39;
        }
            break;
        case REGISTER_ADDRESS_READ_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = REGISTER_ADDRESS_READ_READ_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //we can now start reading registers
                byte_cnt = 0;
                imu_state.i2c_state = BYTE_READ_READ_STATE;
                I2C1CONbits.RCEN = 1;
            }
            break;
        case BYTE_READ_READ_STATE:
            if (!I2C1STATbits.RBF) {
                //nothing received, error
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = BYTE_READ_READ_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                //data received
                //copy data to output buffer
                imu_state.acc_read_data[byte_cnt++] = I2C1RCV;
                //check if we need to send a nack or ack
                if (byte_cnt >= imu_state.acc_read_num) {
                    //send NACK
                    I2C1CONbits.ACKDT = 1;
                    imu_state.i2c_state = STOP_READ_STATE;
                    I2C1CONbits.ACKEN = 1;
                } else {
                    //send ACK
                    I2C1CONbits.ACKDT = 0;
                    imu_state.i2c_state = NEXT_BYTE_READ_STATE;
                    I2C1CONbits.ACKEN = 1;
                }
            }
            break;
        case NEXT_BYTE_READ_STATE:
            if (I2C1CONbits.ACKEN) {
                //ACK was not sent: error
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = NEXT_BYTE_READ_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                imu_state.i2c_state = BYTE_READ_READ_STATE;
                I2C1CONbits.RCEN = 1; //get next byte
            }
            break;
        case STOP_READ_STATE:
            if (I2C1CONbits.ACKEN) {
                //NACK was not sent: error
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = STOP_READ_STATE;
                imu_state.i2c_state = IDLE;
            } else {
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_state = IDLE;
                //acc_read_done = 1; //success
                //update gyro or accelerometer
//                if(update_acc){
//                    //update accelerometer
//                    update_acc = 0;
//                    //TODO: add support for bit shifting?
//                    imu_state.acceleration_state = acc_read_data[0];
//                    imu_state.acceleration[0] = (((acc_read_data[1]<<8)|acc_read_data[2])>>eeprom_state.acc_shift[0])&0xFF;
//                    imu_state.acceleration[1] = (((acc_read_data[3]<<8)|acc_read_data[4])>>eeprom_state.acc_shift[1])&0xFF;
//                    imu_state.acceleration[2] = (((acc_read_data[5]<<8)|acc_read_data[6])>>eeprom_state.acc_shift[2])&0xFF;
//                } else if(update_gyro) {
//                    //update gyroscope
//                    update_gyro = 0;
//                    imu_state.gyroscope_state = acc_read_data[0];
//                    imu_state.gyroscope[0] = (((acc_read_data[2]<<8)|acc_read_data[1])>>eeprom_state.gyro_shift[0])&0xFF; //which part do we want?
//                    imu_state.gyroscope[1] = (((acc_read_data[4]<<8)|acc_read_data[4])>>eeprom_state.gyro_shift[0])&0xFF;
//                    imu_state.gyroscope[2] = (((acc_read_data[6]<<8)|acc_read_data[5])>>eeprom_state.gyro_shift[0])&0xFF;
//                }
            }
            break;
        case WAIT_START_SCAN_STATE:
            if (!I2C1STATbits.S) {
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = WAIT_START_SCAN_STATE;
                imu_state.i2c_state = IDLE;

            } else {
                //send address
                imu_state.i2c_state = ADDRESS_SCAN_STATE;
                I2C1TRN = imu_state.i2c_address;
            }
            break;
        case ADDRESS_SCAN_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = ADDRESS_SCAN_STATE;
                imu_state.i2c_state = IDLE;

            } else {
                //ACK RECEIVED
                //send register address
                I2C1CONbits.PEN = 1; //stop bit
                imu_state.i2c_err = IDLE;
                imu_state.i2c_state = IDLE;
                imu_state.i2c_dev[imu_state.scan_address] = 1;
                
            }
            break;
        default:
            imu_state.i2c_state = IDLE;
    };

    IFS1bits.MI2C1IF = 0;
}