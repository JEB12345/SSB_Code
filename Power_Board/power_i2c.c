#include "p33Exxxx.h"
#include "power_state.h"
#include "power_pindef.h"
#include <i2c.h>
#include "power_i2c.h"

//this struct is for internal use only
typedef struct {
    uint8_t op_type; //0 = read, 1 = write
    uint8_t address;
    uint8_t command;
    uint16_t num_bytes;
    uint8_t* output;
    return_value_t* status_out;
} i2c_operation;

typedef enum {
    I2C_IDLE,
            I2C_WAIT_START_READ_STATE,
            I2C_NEXT_PACKET,
            I2C_ADDRESS_READ_STATE,
            I2C_REGISTER_ADDRESS_READ_STATE,
            I2C_RS_READ_STATE,
            I2C_REGISTER_ADDRESS_READ_READ_STATE,
            I2C_BYTE_READ_READ_STATE,
            I2C_STOP_READ_STATE,
            I2C_NEXT_BYTE_READ_STATE
} i2c_internal_state;

#define I2C_OPS_MAX 5
typedef struct {
    volatile i2c_operation operations[I2C_OPS_MAX];
    volatile uint16_t ops_start;
    volatile uint16_t ops_end;
    volatile i2c_internal_state  state;
    volatile uint16_t byte_cnt;
} i2c_data;

i2c_data i2c_state;

void __attribute__((__interrupt__, no_auto_psv)) _MI2C1Interrupt(void) {

    IFS1bits.MI2C1IF = 0;
i2c_interrupt_start:
    switch(i2c_state.state){
        case I2C_NEXT_PACKET:
        case I2C_IDLE:
            if(i2c_state.ops_end!=i2c_state.ops_start){
                //new operation!
                if(i2c_state.operations[i2c_state.ops_start].op_type==0){
                    //read
                    I2C1CONbits.SEN = 1; //start i2c transaction
                    i2c_state.state = I2C_WAIT_START_READ_STATE;
                } else {
                    //write: TODO implement this
                }
            } else {
                i2c_state.state = I2C_IDLE;
            }
            break;
        case I2C_WAIT_START_READ_STATE:
            if (!I2C1STATbits.S) {
                //error
                I2C1CONbits.PEN = 1; //stop bit
                *(i2c_state.operations[i2c_state.ops_start].status_out) = RET_ERROR;
                i2c_state.ops_start++;
                if(i2c_state.ops_start>=I2C_OPS_MAX){
                    i2c_state.ops_start = 0;
                }
                i2c_state.state = I2C_NEXT_PACKET;
                goto i2c_interrupt_start;
            } else {
                //send address
                I2C1TRN = i2c_state.operations[i2c_state.ops_start].address<<1;
                i2c_state.state = I2C_ADDRESS_READ_STATE;
            }
            break;
        case I2C_ADDRESS_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //error
                I2C1CONbits.PEN = 1; //stop bit
                *(i2c_state.operations[i2c_state.ops_start].status_out) = RET_ERROR;
                i2c_state.ops_start++;
                if(i2c_state.ops_start>=I2C_OPS_MAX){
                    i2c_state.ops_start = 0;
                }
                i2c_state.state = I2C_NEXT_PACKET;
                goto i2c_interrupt_start;
            } else {
                //ACK RECEIVED
                //send command
                I2C1TRN = i2c_state.operations[i2c_state.ops_start].command;
                i2c_state.state = I2C_REGISTER_ADDRESS_READ_STATE;
            }
            break;
        case I2C_REGISTER_ADDRESS_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //error
                I2C1CONbits.PEN = 1; //stop bit
                *(i2c_state.operations[i2c_state.ops_start].status_out) = RET_ERROR;
                i2c_state.ops_start++;
                if(i2c_state.ops_start>=I2C_OPS_MAX){
                    i2c_state.ops_start = 0;
                }
                i2c_state.state = I2C_NEXT_PACKET;
                goto i2c_interrupt_start;
            } else {
                //ACK RECEIVED
                //send a repeated start bit
                I2C1CONbits.RSEN = 1; //repeated start bit
                i2c_state.state = I2C_RS_READ_STATE;
            }
            break;
        case I2C_RS_READ_STATE:
            //send device address with read
            I2C1TRN = (i2c_state.operations[i2c_state.ops_start].address<<1)|0b1;
            i2c_state.state = I2C_REGISTER_ADDRESS_READ_READ_STATE;
            break;
        case I2C_REGISTER_ADDRESS_READ_READ_STATE:
            if (I2C1STATbits.ACKSTAT) {
                //error
                I2C1CONbits.PEN = 1; //stop bit
                *(i2c_state.operations[i2c_state.ops_start].status_out) = RET_ERROR;
                i2c_state.ops_start++;
                if(i2c_state.ops_start>=I2C_OPS_MAX){
                    i2c_state.ops_start = 0;
                }
                i2c_state.state = I2C_NEXT_PACKET;
                goto i2c_interrupt_start;
            } else {
                //ACK RECEIVED
                //we can now start reading registers
                i2c_state.byte_cnt = 0;
                I2C1CONbits.RCEN = 1;
                i2c_state.state = I2C_BYTE_READ_READ_STATE;
            }
            break;
        case I2C_BYTE_READ_READ_STATE:
            if (!I2C1STATbits.RBF) {
                //error
                I2C1CONbits.PEN = 1; //stop bit
                *(i2c_state.operations[i2c_state.ops_start].status_out) = RET_ERROR;
                i2c_state.ops_start++;
                if(i2c_state.ops_start>=I2C_OPS_MAX){
                    i2c_state.ops_start = 0;
                }
                i2c_state.state = I2C_NEXT_PACKET;
                goto i2c_interrupt_start;
            } else {
                //data received
                //copy data to output buffer
                i2c_state.operations[i2c_state.ops_start].output[i2c_state.byte_cnt++] = I2C1RCV;
                //check if we need to send a nack or ack
                if (i2c_state.byte_cnt >= i2c_state.operations[i2c_state.ops_start].num_bytes) {
                    //send NACK
                    I2C1CONbits.ACKDT = 1;
                    i2c_state.state = I2C_STOP_READ_STATE;
                    I2C1CONbits.ACKEN = 1;
                } else {
                    //send ACK
                    I2C1CONbits.ACKDT = 0;
                    i2c_state.state = I2C_NEXT_BYTE_READ_STATE;
                    I2C1CONbits.ACKEN = 1;
                }
            }
            break;
        case I2C_NEXT_BYTE_READ_STATE:
            if (I2C1CONbits.ACKEN) {
                //error
                I2C1CONbits.PEN = 1; //stop bit
                *(i2c_state.operations[i2c_state.ops_start].status_out) = RET_ERROR;
                i2c_state.ops_start++;
                if(i2c_state.ops_start>=I2C_OPS_MAX){
                    i2c_state.ops_start = 0;
                }
                i2c_state.state = I2C_NEXT_PACKET;
                goto i2c_interrupt_start;
            } else {
                i2c_state.state = I2C_BYTE_READ_READ_STATE;
                I2C1CONbits.RCEN = 1; //get next byte
            }
            break;
        case I2C_STOP_READ_STATE:
            if (I2C1CONbits.ACKEN) {
                //error
                I2C1CONbits.PEN = 1; //stop bit
                *(i2c_state.operations[i2c_state.ops_start].status_out) = RET_ERROR;
                i2c_state.ops_start++;
                if(i2c_state.ops_start>=I2C_OPS_MAX){
                    i2c_state.ops_start = 0;
                }
                i2c_state.state = I2C_NEXT_PACKET;
                goto i2c_interrupt_start;
            } else {
                I2C1CONbits.PEN = 1; //stop bit
                *(i2c_state.operations[i2c_state.ops_start].status_out) = RET_OK;
                i2c_state.ops_start++;
                if(i2c_state.ops_start>=I2C_OPS_MAX){
                    i2c_state.ops_start = 0;
                }
                i2c_state.state = I2C_NEXT_PACKET;
            }
            break;
        default:
            //WHAT??? we shouldn't be here :)
            break;
    };
}

/**
     * Initializes the I2C module
     * @return
     */
return_value_t i2c_1_init()
{
        I2C1CONbits.I2CEN = 0;
        I2C1BRG = 344 + 1;
        I2C1CONbits.I2CEN = 1;
        IEC1bits.MI2C1IE = 1;

        i2c_state.state = I2C_IDLE;
        i2c_state.ops_start = i2c_state.ops_end = 0;

        return RET_OK;
}

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
        uint8_t* output, return_value_t* status_out)
{
    //TODO: implement this when we need it :)
    return RET_ERROR;
}

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
        uint8_t* output, return_value_t* status_out)
{
    //check for room in the buffer
    uint16_t ops_next = i2c_state.ops_end+1;
    if(ops_next>=I2C_OPS_MAX){
        ops_next = 0;
    }
    if(ops_next!=i2c_state.ops_start){
        i2c_operation* op = &i2c_state.operations[ops_next];
        op->address = address;
        op->command = command;
        op->num_bytes = num_bytes;
        op->output = output;
        *(op->status_out) = RET_UNKNOWN;
        //update internal state last
        i2c_state.ops_end = ops_next;
        if(i2c_state.state == I2C_IDLE){
            //need to kickstart the I2C processing!
            _MI2C1Interrupt();
        }
        return RET_OK;
    } else {
        return RET_ERROR; //buffer is full
    }
}