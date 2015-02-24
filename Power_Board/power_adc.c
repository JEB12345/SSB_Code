/* 
 * File:   power_adc.c
 * Author: jonathan
 *
 * Created on March 25, 2014, 8:52 AM
 */

#include <p33Exxxx.h>
#include "power_adc.h"
#include "power_pindef.h"
#include "power_state.h"
#include "us_delay.h"
#include "power_can.h"

//__eds__ uint16_t BufferA[8] __attribute__((eds,aligned(64)));
//__eds__ uint16_t BufferB[8] __attribute__((eds,aligned(64)));

__eds__ unsigned int BufferA[48] __attribute__((eds,aligned(64)));
__eds__ unsigned int BufferB[48] __attribute__((eds,aligned(64)));

analog_data adc_values;
extern timer_data timer_state;
extern nrf24l01_data nrf24l01_state;

return_value_t init_adc()
{
    /*******************************
     * Initializes the ADC Module
     *******************************/
    /**
     * Set port configuration
     */
    ANSELA = ANSELB = ANSELC = ANSELE = 0x0000;
    ANSELCbits.ANSC0 = 1;       //AN6
    ANSELCbits.ANSC1 = 1;       //AN7
    ANSELCbits.ANSC2 = 1;       //AN8
    ANSELCbits.ANSC11 = 1;      //AN11
    ANSELEbits.ANSE12 = 1;      //AN12
    ANSELEbits.ANSE13 = 1;      //AN13

    AD1CON1bits.ADON = 0;       //Turn off Module
    //AD1CON1 Settings
    AD1CON1bits.ADSIDL = 0;     //Continues module operation in Idle mode
    AD1CON1bits.ADDMABM = 0;    //Don't Care ignored by DMA
    AD1CON1bits.AD12B = 1;      //12-bit, 1-CH operation
    AD1CON1bits.FORM = 0b00;    //Unsigned Integer output
    AD1CON1bits.SSRC = 0b100;   //Timer5 compare ends sampling and starts conversion
    AD1CON1bits.SSRCG = 0;      //Default no external triggering?
    AD1CON1bits.SIMSAM = 0;     //Has to be off for 12-bit mode
    AD1CON1bits.ASAM = 1;       //Auto sampling, SAMP bit is auto-set

    //AD1CON2 Settigns
    AD1CON2bits.VCFG = 0b000;   //Vrefh = AVdd, Vrefl = AVss
    AD1CON2bits.CSCNA = 1;      //Scans inputs for CH0+ during Sample
    AD1CON2bits.CHPS = 0b00;    //Converts CH0
    AD1CON2bits.SMPI = 5;  //Increments the DMA address after completion of every 6th sample/conversion operation
    AD1CON2bits.BUFM = 0;       //Always starts filling the buffer from the start address
    AD1CON2bits.ALTS = 0;       //Always use channel input selects for Sample MUXA

    //AD1CON3 Settings
    AD1CON3bits.ADRC = 0;       //ADC internal RC clock
    AD1CON3bits.ADCS = 9;      //ADC Conversion Clock, Should be 500kbps

    //AD1CON4 Settings
    AD1CON4bits.ADDMAEN = 1;    //Use DMA
    AD1CON4bits.DMABL = 0b011;  //Allocates 8 words of buffer to each analog input

    //AD1CHS0 Settigns
    AD1CHS0bits.CH0NA = 0;      //Channel 0 negative input is V REFL
    AD1CHS0bits.CH0SA = 0;      //CH0 positive set to AIN0

    //AD1CSSL Settings
    AD1CSSH = 0x00;
    AD1CSSL = 0x00;             // Scan Selection Bits, 1=scan
    AD1CSSLbits.CSS6 = 1;       
    AD1CSSLbits.CSS7 = 1;
    AD1CSSLbits.CSS8 = 1;
    AD1CSSLbits.CSS11 = 1;
    AD1CSSLbits.CSS12 = 1;
    AD1CSSLbits.CSS13 = 1;


    //Flags and Interrupts
    IFS0bits.AD1IF = 0;         //Clear ADC Interrupt flag bit
    IEC0bits.AD1IE = 0;         //Disable ADC interrupt
    
    /*******************************
     * Initializes the DMA2 Module
     *******************************/
    unsigned int config;
    unsigned int irq;
    unsigned long int stb_address;
    unsigned int pad_address;
    unsigned int count;

    IFS1bits.DMA2IF = 0;        //Clear the DMA Interrupt Flag bit
    IEC1bits.DMA2IE = 0;        //Disable DMA CH0 Interrupt

    DMA2CONbits.CHEN = 0;       //Disable DMA2 for Configuration
    DMA2CONbits.AMODE = 0b00;   //Register indirect mode w/ post-increment
    DMA2CONbits.MODE = 0b10;    //Continuous Ping-Pong mode
    DMA2CONbits.SIZE = 0;       //Data is Word Sized
    DMA2CONbits.DIR = 0;        //Peripheral to DMA
    DMA2CONbits.HALF = 0;       //Initiate interrupt when all of the data has been moved
    DMA2CONbits.NULLW = 0;      //Normal Opertaion

//    config = DMA2CON | 0b1000000000000000;
//    irq = 0b00001101;
//    count = 1;
//    pad_address = (volatile unsigned int)&ADC1BUF0; //Points DMA to ADC buffer
//    stb_address = 0x0;
//    OpenDMA2(config,irq,__builtin_dmaoffset(&BufferA),stb_address,pad_address,count);

    DMA2PAD = (volatile unsigned int)&ADC1BUF0; //Points DMA to ADC buffer
    DMA2CNT = 47;               //32 DMA request (6 buffers, each with 8 words) -1
    DMA2REQ = 13;               //Select ADC1 as DMA source

    DMA2STBL = __builtin_dmaoffset(BufferA);
    DMA2STBH = 0x0000;

    DMA2STAL = __builtin_dmaoffset(BufferB);
    DMA2STAH = 0x0000;

    IFS1bits.DMA2IF = 0;        //Clear the DMA Interrupt Flag bit
    IEC1bits.DMA2IE = 1;        //Enable DMA Interrupt bit

    /*********************
     * Turning on Modules
     *********************/
    DMA2CONbits.CHEN = 1;       //Enable DMA
    AD1CON1bits.ADON = 1;       //Turn on the ADC
    Delay_us(20);

    adc_values.motor_current_offset = 0x7B6;

    return RET_OK;
}

inline void adc_update_state()
{
    static uint16_t ctr = 0;
    static uint32_t offset = 0;
    if(ctr<256){
        ctr++;
        offset += adc_values.AN11;
        //disable kill switch during initialization
        nrf24l01_state.rf_killswitch_state = 0;
    } else if(ctr==256) {
        ctr++;
        adc_values.motor_current_offset  = offset>>8;
    }
}

void adc_update_output() {
    //compute voltages, currents and power
    adc_values.mV_5V5_out = ((((uint32_t)adc_values.AN6)*6600))>>12;
    adc_values.mV_vbackup_battery = ((((uint32_t)adc_values.AN8)*6600))>>12;
    adc_values.mV_main_battery = ((((uint32_t)adc_values.AN7)*36300))>>12;
    adc_values.mV_motor_voltage = ((((uint32_t)adc_values.AN12)*36300))>>12;

    adc_values.mA_5V5_out = ((((uint32_t)adc_values.AN13)*3300))>>12;
    adc_values.mA_motor_current = ((((int32_t)adc_values.AN11)-adc_values.motor_current_offset)*30000)/4096; //110mv/A

    adc_values.mW_5V5_out = (adc_values.mV_5V5_out*adc_values.mA_5V5_out)/1000;
    adc_values.mW_motor_power = (adc_values.mA_motor_current*((int32_t)adc_values.mV_motor_voltage))/1000;

    //copy to object dictionary
    CO(adc_state_mV_5V5_out) = adc_values.mV_5V5_out;
    CO(adc_state_mA_5V5_out) = adc_values.mA_5V5_out;
    CO(adc_state_mW_5V5_out) = adc_values.mW_5V5_out;
    CO(adc_state_mV_vbackup_battery) = adc_values.mV_vbackup_battery;
    CO(adc_state_mV_main_battery) = adc_values.mV_main_battery;
    CO(adc_state_mA_motor_current) = adc_values.mA_motor_current;
    CO(adc_state_mW_motor_power) = adc_values.mW_motor_power;
    CO(adc_state_mV_motor_voltage) = adc_values.mV_motor_voltage;

    if ((adc_values.mV_main_battery) > 21000) { 
        VBAT_5V5_EN = ON;
        EN_BACKUP_5V5 = OFF;
        EN_VBAT_5V5 = ON;
    } else {
        EN_BACKUP_5V5 = ON;
        EN_VBAT_5V5 = OFF;
        VBAT_5V5_EN = OFF;
    }

    //Motor power
    //TODO: enable/disable over CAN
    //if(((adc_values.AN7) > 0x0960)  && nrf24l01_state.rf_killswitch_state){
    if(((adc_values.mV_main_battery) > 21000) &&
        nrf24l01_state.rf_killswitch_state){
        KILLSWITCH_uC = ON;
    } else {
        KILLSWITCH_uC = OFF; //REMOVE
    }
}

void __attribute__((interrupt, no_auto_psv)) _DMA2Interrupt(void)
{
    static uint8_t DMAbuffer = 1;
    static uint8_t ADC_State = 0;
    if(DMAbuffer){
        switch(ADC_State){
            //TODO: VMOTOR_V, 5V_CUR, EX_4
            case 0:
                adc_values.AN6 = BufferA[ADC_State];
                ADC_State++;
                //break;
            case 1:
                adc_values.AN7 = BufferA[ADC_State];
                ADC_State++;
               // break;
            case 2:
                adc_values.AN8 = BufferA[ADC_State];
                ADC_State++;
                // break;
            case 3:
                adc_values.AN11 = BufferA[ADC_State];
                ADC_State++;
                break;
            case 4:
                adc_values.AN12 = BufferA[ADC_State];
                ADC_State++;
                break;
            case 5:
                adc_values.AN13 = BufferA[ADC_State];
                ADC_State = 0;
                break;
            default:
                ADC_State = 0;
        }
    }
    else{
        switch(ADC_State){
            case 0:
                adc_values.AN6 = BufferB[ADC_State];
                ADC_State++;
                //break;
            case 1:
                adc_values.AN7 = BufferB[ADC_State];
                ADC_State++;
                //break;
            case 2:
                adc_values.AN8 = BufferB[ADC_State];
                ADC_State++;
                //break;
            case 3:
                adc_values.AN11 = BufferB[ADC_State];
                ADC_State++;
                break;
            case 4:
                adc_values.AN12 = BufferB[ADC_State];
                ADC_State++;
                break;
            case 5:
                adc_values.AN13 = BufferB[ADC_State];
                ADC_State = 0;
                break;
            default:
                ADC_State = 0;
        }
    }
    DMAbuffer ^= 1;

    IFS1bits.DMA2IF = 0;        //Clear the DMA Interrupt Flag bit
}
