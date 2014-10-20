/* 
 * File:   power_spi.c
 * Author: jonathan
 *
 * Created on October 10, 2014, 11:36 AM
 */

#include "power_adc.h"


#include "power_spi.h"
#include "power_state.h"
#include "power_pindef.h"
#include "nRF24L01/src/nrf24l01.h"
#include <spi.h>
#include <dma.h>
#include <xc.h>

unsigned char global_addr[5] = {0xBA, 0xAB, 0xBA, 0xAB, 0x00};
unsigned char rod_addr[5] = {0xBA, 0xAB, 0xBA, 0xAB, 0x01};

return_value_t init_RF_spi()
{
	RF_GND_EN = 1;

	IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
	IEC0bits.SPI1IE = 0; // Disable the Interrupt

	SPI1BUF = 0;

	// SPI1CON1 Register Settings
	SPI1CON1bits.DISSCK = 0; // Internal SPI clock is enabled
	SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
	SPI1CON1bits.MODE16 = 0; // Communication is byte-wide (8 bits)
	SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time

	SPI1CON1bits.CKE = 0; // Serial output data changes on transition
	// from Idle clock state to active clock state
	SPI1CON1bits.CKP = 0; // Idle state for clock is a low level;
	// active state is a low level
	SPI1CON1bits.MSTEN = 1; // Master mode enabled
	// SPI Baud = Fcy / (PPRE * SPRE) =>  Mbaud = 70000000 / (4 * 7)
	SPI1CON1bits.PPRE = 0b10; //4 // Primary prescale bit for SPI clock; 0b11 = 1:1;  0b10 = 4:1; 0b01 = 16:1; 0b00 = 64:1
	SPI1CON1bits.SPRE = 0b001; //7 // Secondary prescale bit for SPI clock; 0b111 = 1:1; 0b110 = 1:2 ... 0b000 = 1:8
	SPI1CON1bits.SSEN = 0; // Slave select pin disabled

	SPI1STATbits.SPIROV = 0; // Clear SPI overflow bit
	SPI1CON2bits.FRMEN = 0; // Frame mode disabled
	SPI1CON2bits.SPIBEN = 1; // Enhanced Buffer Enabled

	// SPISTAT Register Settings
	SPI1STATbits.SPIEN = 1; // Enable SPI module
	SPI1STATbits.SPISIDL = 0; // Continue module operation when device enters Idle mode

	// Interrupt Controller Settings
	//	SPI1STATbits.SPIROV = 0; // Clear SPI overflow bit
	IFS0bits.SPI1EIF = 0; // Clear SPI1 Error Interrupt Flag Status bit
	IPC2bits.SPI1IP = 0x06; // Set SPI1 Interrupt Priority Level to 1 = low priority
	IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
	IEC0bits.SPI1IE = 1; // Enable the Interrupt

	SG_DESELECT;
}

void init_RF_device_RX()
{
	Delay_us(1000);

	unsigned char config;
	config = nrf24l01_CONFIG_DEFAULT_VAL | nrf24l01_CONFIG_PWR_UP;
	config |= nrf24l01_CONFIG_PRIM_RX;

	nrf24l01_initialize(config,
		true,
		nrf24l01_EN_AA_ENAA_NONE,
		nrf24l01_EN_RXADDR_ERX_ALL,
		nrf24l01_SETUP_AW_5BYTES,
		nrf24l01_SETUP_RETR_ARC_0,
		100, // Channel Value
		0x27, // based off of Ken's robot's code (set bitrate to 250kbps)
		&global_addr, // P0
		&rod_addr, // P1
		nrf24l01_RX_ADDR_P2_DEFAULT_VAL,
		nrf24l01_RX_ADDR_P3_DEFAULT_VAL,
		nrf24l01_RX_ADDR_P4_DEFAULT_VAL,
		nrf24l01_RX_ADDR_P5_DEFAULT_VAL,
		NULL,
		1, // P0 width is 1 byte(s)
		1, // P1 width is 1 byte(s)
		nrf24l01_RX_PW_P2_DEFAULT_VAL,
		nrf24l01_RX_PW_P3_DEFAULT_VAL,
		nrf24l01_RX_PW_P4_DEFAULT_VAL,
		nrf24l01_RX_PW_P5_DEFAULT_VAL);

	nrf24l01_set_as_rx_param(true, config);
//	nrf24l01_write_register(nrf24l01_FEATURE, 0x01, 1);
}

void init_RF_device_TX()
{
	Delay_us(1000);

	unsigned char config;
	config = nrf24l01_CONFIG_DEFAULT_VAL | nrf24l01_CONFIG_PWR_UP;

	nrf24l01_initialize(config,
		false,
		nrf24l01_EN_AA_ENAA_NONE,
		nrf24l01_EN_RXADDR_ERX_ALL,
		nrf24l01_SETUP_AW_5BYTES,
		nrf24l01_SETUP_RETR_ARC_0,
		100, // Channel Value
		0x27, // based off of Ken's robot's code (set bitrate to 250kbps)
		&global_addr, // P0
		NULL, // P1
		nrf24l01_RX_ADDR_P2_DEFAULT_VAL,
		nrf24l01_RX_ADDR_P3_DEFAULT_VAL,
		nrf24l01_RX_ADDR_P4_DEFAULT_VAL,
		nrf24l01_RX_ADDR_P5_DEFAULT_VAL,
		&global_addr, // TX_ADDR
		1, // P0 width is 1 byte(s)
		nrf24l01_RX_PW_P1_DEFAULT_VAL, // P1 width is default byte(s)
		nrf24l01_RX_PW_P2_DEFAULT_VAL,
		nrf24l01_RX_PW_P3_DEFAULT_VAL,
		nrf24l01_RX_PW_P4_DEFAULT_VAL,
		nrf24l01_RX_PW_P5_DEFAULT_VAL);

	nrf24l01_set_as_tx_param(config);
}

unsigned char spi1_send_read_byte(unsigned char byte)
{
	SPI1BUF = byte;

	while (!SPI1STATbits.SRMPT);

	return SPI1BUF;
}

void __attribute__((__interrupt__, no_auto_psv)) _SPI1Interrupt(void)
{
	IFS0bits.SPI1EIF = 0; // Clear SPI1 Fault Interrupt Flag Status bit
	IFS0bits.SPI1IF = 0; // Clear the interrupt Flag
}