#include "sensor_imu.h"
#include "sensor_state.h"
#include "sensor_pindefs.h"
#include "sensor_led.h"
#include <p33Exxxx.h>

imu_data imu_state;

volatile enum I2C_STATES i2c_state;
volatile enum I2C_STATES i2c_err;
volatile uint8_t acc_read_register;
volatile uint8_t acc_read_num;
volatile uint8_t acc_read_data[25];
//volatile uint8 acc_read_done;
volatile uint8_t i2c_address, i2c_address_2;
volatile uint16_t acc_cnt, i2c_err_5, i2c_err_2, i2c_err_sum;
volatile uint8_t acc_write_num;
volatile uint8_t acc_write_data[20];
volatile uint8_t acc_write_register;
volatile uint8_t acc_write_done;
volatile uint8_t i2c_dev[128];
volatile uint8_t scan_address;

enum I2C_STATES {
    IDLE,
    GYRO_WAIT_START,

    WAIT_START_READ_STATE, //beginning of transaction to read the
    ADDRESS_READ_STATE,
    REGISTER_ADDRESS_READ_STATE,
    RS_READ_STATE,
    REGISTER_ADDRESS_READ_READ_STATE,
    BYTE_READ_READ_STATE,
    STOP_READ_STATE,
    NEXT_BYTE_READ_STATE,

    WAIT_START_WRITE_STATE,
    ADDRESS_WRITE_STATE,
    BYTE_WRITE_STATE,
    STOP_WRITE_STATE,
    WAIT_START_SCAN_STATE,
    ADDRESS_SCAN_STATE

};

void i2c_scan();

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

    i2c_state = IDLE;
    if (I2C1STATbits.RBF)
        temp = I2C1RCV;

    for(i=0;i<10000;i++){
        Nop();
    }
    i2c_scan();

    return imu_state.init_return;
}

void i2c_scan() {
    uint8_t address = 0;
    uint8_t temp;
    uint16_t i;

    for (address = 0; address < 128; ++address) {
        i2c_dev[address] = 0;
        while (i2c_state != IDLE);
        I2C1STATbits.IWCOL = 0;
        if (I2C1STATbits.RBF)
            temp = I2C1RCV; //clears the RBF flag
        i2c_state = WAIT_START_SCAN_STATE;

        i2c_address = address<<1;
        scan_address = address;

        I2C1STATbits.BCL = 0;
        I2C1CONbits.SEN = 1;

        while (i2c_state != IDLE);
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

    switch (i2c_state) {
        case GYRO_WAIT_START:
            if (I2C1CONbits.SEN) {
                //something went wrong (this should be low)
                //reset to idle
                I2C1CONbits.PEN = 1; //stop bit
                i2c_state = IDLE;
            }
            break;
        case WAIT_START_WRITE_STATE:
            if (!I2C1STATbits.S) {
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = WAIT_START_WRITE_STATE;
                i2c_state = IDLE;
            } else {
                //send address
                i2c_state = ADDRESS_WRITE_STATE;
                I2C1TRN = i2c_address;
            }
            break;
        case ADDRESS_WRITE_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = ADDRESS_WRITE_STATE;
                i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //send register address
                i2c_state = BYTE_WRITE_STATE;
                byte_cnt = 0;
                I2C1TRN = acc_write_register;
            }
            break;
        case BYTE_WRITE_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = BYTE_WRITE_STATE;
                i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //send data byte
                if (++byte_cnt >= acc_write_num) {
                    i2c_state = STOP_WRITE_STATE;
                } else {
                    i2c_state = BYTE_WRITE_STATE;
                }
                I2C1TRN = acc_write_data[byte_cnt - 1];
            }
            break;
        case STOP_WRITE_STATE:
            if (I2C1CONbits.ACKEN) {
                //NACK was not sent: error
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = STOP_WRITE_STATE;
                i2c_state = IDLE;
            } else {
                I2C1CONbits.PEN = 1; //stop bit
                i2c_state = IDLE;
                acc_write_done = 1; //success
            }
            break;

        case WAIT_START_READ_STATE:
            if (!I2C1STATbits.S) {
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = WAIT_START_READ_STATE;
                i2c_state = IDLE;

            } else {
                //send address
                i2c_state = ADDRESS_READ_STATE;
                I2C1TRN = i2c_address; //0xD2; //0x38; //WRITE
            }
            break;
        case ADDRESS_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = ADDRESS_READ_STATE;
                i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //send register address
                i2c_state = REGISTER_ADDRESS_READ_STATE;
                I2C1TRN = acc_read_register;
            }
            break;
        case REGISTER_ADDRESS_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = REGISTER_ADDRESS_READ_STATE;
                i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //send a repeated start bit
                i2c_state = RS_READ_STATE;
                I2C1CONbits.RSEN = 1; //repeated start bit
            }
            break;
        case RS_READ_STATE:
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
            /*if(I2C1CONbits.RSEN = 1){
                //didn't send the repeated start, weird
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = ACC_RS_READ_STATE;
                i2c_state = IDLE;
            } else */
        {
            //send device address with read
            i2c_state = REGISTER_ADDRESS_READ_READ_STATE;
            I2C1TRN = i2c_address_2; //0xD3;//0x39;
        }
            break;
        case REGISTER_ADDRESS_READ_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = REGISTER_ADDRESS_READ_READ_STATE;
                i2c_state = IDLE;
            } else {
                //ACK RECEIVED
                //we can now start reading registers
                byte_cnt = 0;
                i2c_state = BYTE_READ_READ_STATE;
                I2C1CONbits.RCEN = 1;
            }
            break;
        case BYTE_READ_READ_STATE:
            if (!I2C1STATbits.RBF) {
                //nothing received, error
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = BYTE_READ_READ_STATE;
                i2c_state = IDLE;
            } else {
                //data received
                //copy data to output buffer
                acc_read_data[byte_cnt++] = I2C1RCV;
                //check if we need to send a nack or ack
                if (byte_cnt >= acc_read_num) {
                    //send NACK
                    I2C1CONbits.ACKDT = 1;
                    i2c_state = STOP_READ_STATE;
                    I2C1CONbits.ACKEN = 1;
                } else {
                    //send ACK
                    I2C1CONbits.ACKDT = 0;
                    i2c_state = NEXT_BYTE_READ_STATE;
                    I2C1CONbits.ACKEN = 1;
                }
            }
            break;
        case NEXT_BYTE_READ_STATE:
            if (I2C1CONbits.ACKEN) {
                //ACK was not sent: error
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = NEXT_BYTE_READ_STATE;
                i2c_state = IDLE;
            } else {
                i2c_state = BYTE_READ_READ_STATE;
                I2C1CONbits.RCEN = 1; //get next byte
            }
            break;
        case STOP_READ_STATE:
            if (I2C1CONbits.ACKEN) {
                //NACK was not sent: error
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = STOP_READ_STATE;
                i2c_state = IDLE;
            } else {
                I2C1CONbits.PEN = 1; //stop bit
                i2c_state = IDLE;
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
                i2c_err = WAIT_START_SCAN_STATE;
                i2c_state = IDLE;

            } else {
                //send address
                i2c_state = ADDRESS_SCAN_STATE;
                I2C1TRN = i2c_address;
            }
            break;
        case ADDRESS_SCAN_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //NACK RECEIVED
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = ADDRESS_SCAN_STATE;
                i2c_state = IDLE;

            } else {
                //ACK RECEIVED
                //send register address
                I2C1CONbits.PEN = 1; //stop bit
                i2c_err = IDLE;
                i2c_state = IDLE;
                i2c_dev[scan_address] = 1;
                
            }
            break;
        default:
            i2c_state = IDLE;
    };

    IFS1bits.MI2C1IF = 0;
}