/*
	Copyright (C) 2011-2012 Michiel D'Haene <michiel.dhaene at gmail dot com>,
        Ken Caluwaerts <ken@caluwaerts.eu>

	UGent Reservoir lab (http://reslab.elis.ugent.be/michiel)
	Ghent University (http://www.ugent.be)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
	\defgroup spi_rf COMMAND
	\brief 	SPI interface for radio frequency module.

	This file contains the declarations of the spi interface functions for the radio frequency module.

	\author 	Michiel D'Haene
	\version 	1.0
	\date		2012-02-16
*/
/*@{*/

/** \file 	spi_rf.c
	\brief 	SPI interface for radio frequency module.
*/
#include "power_nrf24l01.h"
#include "power_adc.h"
#include "power_state.h"
#include "power_pindef.h"
//#include "nRF24L01/src/nrf24l01.h"
#include <spi.h>
#include <dma.h>
#include <xc.h>


/*************************************************************************
*
*		VARIABLES
*
*************************************************************************/
nrf24l01_data nrf24l01_state;
extern system_data system_state;

/************************************************************************
 *
 * Private functions
 *
 ***********************************************************************/
void rf_spi_send(); /*Transmits all pending messages over SPI to the
                           * module and updates the status*/


void rf_init_data();

void nrf24l01_handle_rx();
void nrf24l01_handle_wait_tx();
void nrf24l01_handle_start_tx();

/*************************************************************************
*
*		INTERRUPT ROUTINES
*
*************************************************************************/
/** \brief SPI1 receiver interrupt routine

	This interrupt routine is called after bytes/words are sent/received
	by the SPI receiver.

	\param 	no parameters
	\return	no returns
*/

void __attribute__((__interrupt__, no_auto_psv)) _SPI1Interrupt(void)
{
	SPI1STATbits.SPIROV = 0; 	// Clear SPI overflow bit
	IFS0bits.SPI1IF = 0; 		// Clear the interrupt Flag

	nrf24l01_state.spi_rf_busy = 0;		// indicate that next spi transfer may start
}


void __attribute__((__interrupt__, no_auto_psv)) _CNInterrupt(void)
{
    //TODO!!!
    //TODO: check RF_IRQ
    //NRF24_INTERRUPT = (RF_IRQ == 0);

    IFS1bits.CNIF = 0;
}



/*************************************************************************
*
*		FUNCTIONS
*
*************************************************************************/
/** \brief SPI initialization function

        This function is used to initialize all SPIs. It should be called in
        the main initialization function.

        \param 	no parameters
        \return	no returns
 */

return_value_t nrf24l01_init(void) {
    uint16_t i;

    //power toggle the chip
    RF_GND_EN = 0;
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    RF_GND_EN = 1;
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    Delay_us(1000);
    

    SPI1STATbits.SPIEN = 0; // Disable SPI module
    
    //TX
    IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
    IEC0bits.SPI1IE = 0; // Disable the Interrupt

    SPI1BUF=0;

    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0; // Internal SPI clock is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0; // Communication is byte-wide (8 bits)
    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time

    SPI1CON1bits.CKE = 0; // Serial output data changes on transition
    // from Idle clock state to active clock state
    SPI1CON1bits.CKP = 0; // Idle state for clock is a low level;
    // active state is a high level
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    SPI1CON1bits.PPRE = 0b00; // Primary prescale bit for SPI clock; 0b11 = 1:1; 0b10 = 4:1; 0b01 = 16:1; 0b00 = 64:1
    SPI1CON1bits.SPRE = 0b001; // Secondary prescale bit for SPI clock; 0b111 = 1:1; 0b110 = 1:2 ... 0b000 = 1:8
    SPI1CON1bits.SSEN = 0; // Slave select pin disabled

    SPI1CON2bits.FRMEN = 0; // Frame mode disabled
    SPI1CON2bits.SPIBEN = 1;

    // SPISTAT Register Settings
    SPI1STATbits.SPISIDL = 0; // Discontinue module operation when device enters Idle mode

    // Interrupt Controller Settings
    SPI1STATbits.SPIROV = 0; // Clear SPI overflow bit
    IPC2bits.SPI1IP = 0x06; // Set SPI1 Interrupt Priority Level to 1 = low priority
    IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
    IEC0bits.SPI1IE = 1; // Enable the Interrupt

    nrf24l01_state.spi_rf_busy = 0;

    SPI1STATbits.SPIEN = 1; // Enable SPI module
    rf_init_data();

    /*wait >=100 ms for the RF to go in power down mode*/
    for(i=0;i<200;++i){
        Delay_us(1000);
    };

    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_CONFIG, nrf24l01_CONFIG_DEFAULT_VAL);
    rf_spi_send();
    for(i=0;i<20;++i){
        Delay_us(1000);
    };

    /*Write CONFIG to RF */
    //RF_RX_SEND_2(nrf24l01_W_REGISTER | nrf24l01_CONFIG, nrf24l01_CONFIG_EN_CRC);
    /*Disable auto ACK*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_EN_AA, 0x00);
    rf_spi_send();
    /*enable/disable RX data pipes*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_EN_RXADDR, 0b00111111); //4 pipes enabled
    rf_spi_send();
    /*set number of bytes in RX0 pipe*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_PW_P0, 0b0100000); //32 bytes payload
    rf_spi_send();
    /*set number of bytes in RX1 pipe*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_PW_P1, 0b0100000); //32 bytes payload
    rf_spi_send();
    /*set number of bytes in RX2 pipe*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_PW_P2, 0b0100000); //32 bytes payload
    rf_spi_send();
    /*set number of bytes in RX3 pipe*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_PW_P3, 0b0100000); //32 bytes payload
    rf_spi_send();
    /*set number of bytes in RX4 pipe*/
    //RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_PW_P4, 0b0100000); //32 bytes payload
    //rf_spi_send();
    /*set number of bytes in RX5 pipe*/
    //RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_PW_P5, 0b0100000); //32 bytes payload
    //rf_spi_send();
    /*Set address width to 3bytes*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_SETUP_AW, nrf24l01_SETUP_AW_3BYTES);
    rf_spi_send();
    /*Disable retry sending*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_SETUP_RETR, nrf24l01_SETUP_RETR_ARC_0);
    rf_spi_send();
    /*Set the RF channel*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RF_CH, 100);//nrf24l01_RF_CH_DEFAULT_VAL);
    rf_spi_send();
    /*Set RF properties*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RF_SETUP, 0b00001110); //250Kbps
    rf_spi_send();
    /*Set RX addresses*/
    RF_SEND_4(nrf24l01_W_REGISTER | nrf24l01_RX_ADDR_P0, 0xB0, 0x0B, system_state.system_id); //direct command
    rf_spi_send();
    /*Set RX addresses*/
    RF_SEND_4(nrf24l01_W_REGISTER | nrf24l01_RX_ADDR_P1, 0x12, 0x34, 0x01); //MOTOR COMMANDS 1
    rf_spi_send();
    /*Set RX addresses*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_ADDR_P2, 0x02); //
    rf_spi_send();
    /*Set RX addresses*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_ADDR_P3, 0x03); //
    rf_spi_send();
    /*Set RX addresses*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_ADDR_P4, 0x04);
    rf_spi_send();
    /*Set RX addresses*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_RX_ADDR_P5, 0x05);
    rf_spi_send();
    /*disable ACK*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_FEATURE, 0b00000001);
    rf_spi_send();

    /*power up the RF*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_CONFIG, nrf24l01_CONFIG_EN_CRC | nrf24l01_CONFIG_PWR_UP);
    rf_spi_send();
    /*Clear TX and RX and MAX_RT bits in status register*/
    RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_STATUS, nrf24l01_STATUS_MAX_RT | nrf24l01_STATUS_TX_DS | nrf24l01_STATUS_RX_DR);
    rf_spi_send();

    /*delay to go from power down to standby-1*/
    for(i=0;i<20;++i){
        Delay_us(1000);
    };


    /*Set PRIM_RX high*/
    RF_SEND_2( nrf24l01_W_REGISTER | nrf24l01_CONFIG, nrf24l01_CONFIG_PWR_UP | nrf24l01_CONFIG_PRIM_RX | nrf24l01_CONFIG_EN_CRC );
    /*Transmit everything in the SPI buffer*/
    rf_spi_send();

//    RF_SEND_2( nrf24l01_CONFIG,0xFF); //read config reg
//    rf_spi_send();

    nrf24l01_state.rf_data_available = 0;

    for(i=0;i<20;++i){
        Delay_us(1000);
    };

    RF_CE = 1; //start in RX mode
    nrf24l01_state.init_return = RET_OK;
    return RET_OK;
}


void rf_init_data()
{
    nrf24l01_state.spi_rf_buffer_ind[0] = 0;
    nrf24l01_state.spi_rf_cur_msg = 1;
    nrf24l01_state.spi_rf_num_msg = 0;
    nrf24l01_state.rf_state = RF_STATE_RX;
    nrf24l01_state.rx_buffer = &nrf24l01_state.rx_packets[0];
    nrf24l01_state.rx_packets_start = 0;
    nrf24l01_state.rx_packets_end = 0;
    nrf24l01_state.tx_packets_start = 0;
    nrf24l01_state.tx_packets_end = 0;
}

void rf_spi_send_test(){
    uint16_t j;

    RF_CSN =0;
    for(nrf24l01_state.spi_rf_buffer_ind[0]; j<nrf24l01_state.spi_rf_buffer_ind[1];++j){
        nrf24l01_state.spi_rf_busy = 1;
        RF_BUF = nrf24l01_state.spi_rf_buffer[j];
        while(nrf24l01_state.spi_rf_busy);
        nrf24l01_state.spi_rf_buffer_rec[j] = RF_BUF;
    }
    RF_CSN = 1;
    nrf24l01_state.RF_status = nrf24l01_state.spi_rf_buffer_rec[nrf24l01_state.spi_rf_buffer_ind[0]];
    nrf24l01_state.spi_rf_num_msg = 0;
    nrf24l01_state.spi_rf_cur_msg = 1;
    nrf24l01_state.spi_rf_buffer_i = 0;
}

void rf_spi_send(){
    /*Transmits all pending messages over SPI to the module*/
    uint16_t j;
    int16_t k;

    while(nrf24l01_state.spi_rf_busy);
    for(k=-1;nrf24l01_state.spi_rf_cur_msg<=nrf24l01_state.spi_rf_num_msg;++nrf24l01_state.spi_rf_cur_msg){
        /*spi_cur_msg==current message to send*/
        /*k==current received byte index*/
        /*Pull CSN low*/
        RF_CSN = 0;

        Delay_us(10);//TODO: is this needed?
        
        for(j=nrf24l01_state.spi_rf_buffer_ind[nrf24l01_state.spi_rf_cur_msg-1];
                j<nrf24l01_state.spi_rf_buffer_ind[nrf24l01_state.spi_rf_cur_msg];
                ++j){
            nrf24l01_state.spi_rf_busy = 1;

            //while(SPI1STATbits.SPITBF);
            SPI1BUF = nrf24l01_state.spi_rf_buffer[j];
            /*check if TX buffers are not full*/
            ++k;
            //while(nrf24l01_state.spi_rf_busy);
            /*TODO: check if there's something in the receive buffer*/

            //while(!SPI1STATbits.SPIRBF);
            while (!SPI1STATbits.SRMPT);
            nrf24l01_state.spi_rf_buffer_rec[k] = SPI1BUF;
            
            Delay_us(1);
        }
        Delay_us(10);//TODO: is this needed?
        /*CSN high*/
        RF_CSN = 1;

        Delay_us(10);//TODO: is this needed?

    }
    if(nrf24l01_state.spi_rf_num_msg>0){
        nrf24l01_state.RF_status =
                nrf24l01_state.spi_rf_buffer_rec[nrf24l01_state.spi_rf_buffer_ind[nrf24l01_state.spi_rf_num_msg-1]]; /*Store the last received status byte*/
    }
    /*reset transmit state*/
    nrf24l01_state.spi_rf_num_msg = 0;
    nrf24l01_state.spi_rf_cur_msg = 1;
    nrf24l01_state.spi_rf_buffer_i = 0;
}

void nrf24l01_update() {
    switch (nrf24l01_state.rf_state) {
        case RF_STATE_RX:
            nrf24l01_handle_rx();
            break;
        case RF_STATE_WAIT_TX:
            nrf24l01_handle_wait_tx();
            break;
        case RF_STATE_START_TX:
            nrf24l01_handle_start_tx();
            break;
        default:
            //ERROR!!!
            //reset to RX
            nrf24l01_state.rf_state = RF_STATE_RX;
            break;
    };
}

void nrf24l01_handle_rx(){
    uint8_t rx_pipe;
    uint16_t rf_data[32];
    nrf24l01_tx_packet* tx_pkt;
    uint16_t i;
    
    //check whether there's new data in SPI RX
    if (!RF_IRQ) {
        RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_STATUS, nrf24l01_state.RF_status | nrf24l01_STATUS_RX_DR);
        rf_spi_send();
        //get result
        if (nrf24l01_state.RF_status & nrf24l01_STATUS_RX_DR) {
            RF_SEND_33(nrf24l01_R_RX_PAYLOAD, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP, nrf24l01_NOP);
            rf_spi_send();
            RF_CE = 0;
            Delay_us(15);
            RF_CE = 1;

            LED_STATUS = OFF; //toggle status LED
            //get the pipe number
            rx_pipe = (nrf24l01_state.RF_status & nrf24l01_STATUS_RX_P_NO) >> 1;

            //store data
            nrf24l01_state.rx_buffer->pipe = rx_pipe;
            for(i=0;i<32;++i){
                nrf24l01_state.rx_buffer->data[i] = nrf24l01_state.spi_rf_buffer_rec[i+1];
            }
            nrf24l01_state.rx_buffer->data_length = 32; //TODO: read actual data length

            //prepare for next packet
            if(nrf24l01_state.rx_packets_end==RF_RX_PACKET_BUFF_LEN-1){
                nrf24l01_state.rx_packets_end = 0;
            } else {
                ++nrf24l01_state.rx_packets_end;
            }
            nrf24l01_state.rx_buffer = &nrf24l01_state.rx_packets[nrf24l01_state.rx_packets_end];
        }
    } else if (nrf24l01_state.tx_packets_start!=nrf24l01_state.tx_packets_end) {
        //a packet needs to be sent
        RF_CE = 0;
        tx_pkt = &nrf24l01_state.tx_packets[nrf24l01_state.tx_packets_start];

        ++nrf24l01_state.tx_packets_start;
        if (nrf24l01_state.tx_packets_start >= RF_TX_PACKET_BUFF_LEN) {
            nrf24l01_state.tx_packets_start = 0;
        }

        //send RF message
        RF_SEND_VAR_CMD(nrf24l01_W_REGISTER | nrf24l01_TX_ADDR, tx_pkt->address, tx_pkt->address_length);
        //RF_SEND_4(nrf24l01_W_REGISTER | nrf24l01_TX_ADDR, 0xC2, 0xC2, 0xC2);
        RF_SEND_VAR_CMD(nrf24l01_W_TX_PAYLOAD_NOACK, tx_pkt->data, 32);//tx_pkt->data_length);
        rf_spi_send();
        Delay_us(20);
        //go to TX mode
        RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_CONFIG, nrf24l01_CONFIG_PWR_UP | nrf24l01_CONFIG_EN_CRC);
        rf_spi_send();

        Delay_us(20);
        RF_CE = 1;

        nrf24l01_state.rf_state = RF_STATE_START_TX; //waits for IRQ and goes back to RX mode
    }

}

void nrf24l01_handle_wait_tx() {
    uint16_t i;
    uint16_t rf_data[32];
    
    if (nrf24l01_state.rf_tx_delay > 0) {
        nrf24l01_state.rf_tx_delay--;
        return;
    }
    
    //update state
    nrf24l01_state.rf_state = RF_STATE_START_TX;
    //send state over rf
    RF_SEND_4(nrf24l01_W_REGISTER | nrf24l01_TX_ADDR, 0x12, 0x34, 0xFF);

    for(i=0;i<32;++i){
        rf_data[0] = i;//insert the data you want to send here
    }

    RF_SEND_VAR_CMD(nrf24l01_W_TX_PAYLOAD_NOACK, rf_data, 32);
    rf_spi_send();
    RF_CE = 1;
}

void nrf24l01_handle_start_tx() {
//    RF_CE = 0;
    
    
    memset(nrf24l01_state.spi_rf_buffer_rec,0xFF,10);
    RF_SEND_2( nrf24l01_CONFIG,1);
    rf_spi_send();

    //wait for irq
    if (!RF_IRQ) {
        //IRQ received, reset it and prepare for next transmit
        RF_CE = 0;
        Delay_us(100);
        //acknowledge
        RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_STATUS, nrf24l01_STATUS_TX_DS); 
        //back to RX mode
        RF_SEND_2(nrf24l01_W_REGISTER | nrf24l01_CONFIG, nrf24l01_CONFIG_PWR_UP |
                nrf24l01_CONFIG_PRIM_RX | nrf24l01_CONFIG_EN_CRC);
        rf_spi_send();

        nrf24l01_state.rf_state = RF_STATE_RX;
        
        RF_CE = 1;

        LED_STATUS = OFF;
    }
}

nrf24l01_tx_packet* nrf24l01_tx_cur_packet()
{
    return &nrf24l01_state.tx_packets[nrf24l01_state.tx_packets_end];
}

void nrf24l01_tx_update_index()
{
    if (nrf24l01_state.tx_packets_end >= RF_TX_PACKET_BUFF_LEN - 1){
        nrf24l01_state.tx_packets_end = 0;
    }
    else {
        ++nrf24l01_state.tx_packets_end;
    }
}

nrf24l01_rx_packet* nrf24l01_rx_cur_packet()
{
    if(nrf24l01_state.rx_packets_start != nrf24l01_state.rx_packets_end) {
        //handle a single packet
        return &nrf24l01_state.rx_packets[nrf24l01_state.rx_packets_start];
    } else {
        return 0;
    }
}

void nrf24l01_rx_packet_consumed()
{
    if (nrf24l01_state.rx_packets_start >= RF_RX_PACKET_BUFF_LEN - 1){
        nrf24l01_state.rx_packets_start = 0;
    }
    else {
        ++nrf24l01_state.rx_packets_start;
    }
}

/*@}*/

