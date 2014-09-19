/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 Pavlo Milo Manovi
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#include <p33Exxxx.h>
#include <i2c.h>
#include "I2CdsPIC.h"
#include "sensor_state.h"
#include "sensor_pindefs.h"

static uint8_t Init = 0;

return_value_t I2C_Init() {
    uint8_t temp;

    I2C1CONbits.I2CEN = 0; //Disable I2C1
    I2C1BRG = 165;
//    IFS1bits.MI2C1IF = 0;
//    IFS1bits.SI2C1IF = 0;
//    IEC1bits.MI2C1IE = 1; //clear interrupts
//    IEC1bits.SI2C1IE = 1;
//    I2C1CONbits.A10M = 0; //7 bit slave address
    I2C1CONbits.I2CEN = 1; //enable the i2c module
//    temp = I2C1RCV; //clear receive buffer


    return (RET_OK);
}

uint8_t I2C_WriteToReg(uint8_t I2CAddress, uint8_t deviceRegister, uint8_t data) {

    StartI2C1();
    while(I2C1CONbits.SEN);
    IFS1bits.MI2C1IF = 0;

    MasterWriteI2C1(I2CAddress << 1);
    while(I2C1STATbits.TBF);   // 8 clock cycles
    while(!IFS1bits.MI2C1IF); // Wait for 9th clock cycle
    IFS1bits.MI2C1IF = 0;     // Clear interrupt flag

    MasterWriteI2C1(deviceRegister);
    while(I2C1STATbits.TBF);   // 8 clock cycles
    while(!IFS1bits.MI2C1IF); // Wait for 9th clock cycle
    IFS1bits.MI2C1IF = 0;     // Clear interrupt flag
    MasterWriteI2C1(data);

    while(I2C1STATbits.TBF);   // 8 clock cycles
    while(!IFS1bits.MI2C1IF); // Wait for 9th clock cycle
    IFS1bits.MI2C1IF = 0;     // Clear interrupt flag

    StopI2C1();               // Write stop sequence.
    while(I2C1CONbits.PEN);
    IdleI2C1();
    return(1);
}


uint8_t I2C_ReadFromReg(uint8_t I2CAddress, uint8_t deviceRegister) {
    uint8_t data = 0;
    StartI2C1();
    while(I2C1CONbits.SEN);

    MasterWriteI2C1(I2CAddress << 1);
    while(I2C1STATbits.TBF);   // 8 clock cycles
    while(!IFS1bits.MI2C1IF); // Wait for 9th clock cycle
    IFS1bits.MI2C1IF = 0;     // Clear interrupt flag

    MasterWriteI2C1(deviceRegister);
    while(I2C1STATbits.TBF);   // 8 clock cycles
    while(!IFS1bits.MI2C1IF); // Wait for 9th clock cycle
    IFS1bits.MI2C1IF = 0;     // Clear interrupt flag

    RestartI2C1();            // Second start.
    while(I2C1CONbits.RSEN);

    MasterWriteI2C1((I2CAddress << 1 )+ 1);
    while(I2C1STATbits.TBF);   // 8 clock cycles
    while(!IFS1bits.MI2C1IF); // Wait for 9th clock cycle
    IFS1bits.MI2C1IF = 0;     // Clear interrupt flag

    data = MasterReadI2C1();

    NotAckI2C1();             // Read stop sequence.
    while(I2C1CONbits.ACKEN == 1);
    StopI2C1();
    while(I2C1CONbits.PEN);
    IdleI2C1();

    return(data);
}