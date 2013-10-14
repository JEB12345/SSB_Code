/*
 *  File:   sensor_spi.c
 *  Author: Jonathan Bruce
 *
 *  Created on: 24th September 2013
 *
 */

#include <p33Exxxx.h>
#include <dma.h>
#include <stdio.h>
#include <stdlib.h>
#include "sensor_rf.h"
#include "sensor_pindefs.h"
#include "sensor_state.h"
#include "superball_circularbuffer.h"
#include "xbee_API.h"


#define SPI_BUFFER_SIZE_TX 16*sizeof(xbee_tx_ip_packet_t)
#define SPI_BUFFER_SIZE_RX 16*sizeof(xbee_rx_ip_packet_t)

volatile rf_data rf_state;
//CircularBuffer TxCB;
//CircularBuffer RxCB;

uint8_t tx_spi_buffer_array[SPI_BUFFER_SIZE_TX];
uint8_t rx_spi_buffer_array[SPI_BUFFER_SIZE_RX];

uint8_t TxBufferKEN[100] __attribute__((aligned(32 * 16)));
uint8_t RxBufferKEN[100] __attribute__((aligned(32 * 16)));

uint8_t TxBufferDummy[1] __attribute__((space(xmemory)));//dummy buffer for transmitting messages & receiving headers
uint8_t RxBufferHeader[3] __attribute__((space(xmemory)));//buffer for receiving headers
/*
 * DMA2 Tx Buffers
 */
//unsigned int TxBufferA[16] __attribute__((space(xmemory)));
//unsigned int TxBufferB[16] __attribute__((space(xmemory)));
/*
 * DMA3 Rx Buffers
 */
//unsigned int RxBufferA[16] __attribute__((space(xmemory)));
//unsigned int RxBufferB[16] __attribute__((space(xmemory)));

/*
 * Sets Up the SPI2 line to interface with the XBee Wifi
 */
return_value_t spi2_init() {

    unsigned int config;
    unsigned int irq;
    unsigned long int stb_address;
    unsigned int pad_address;
    unsigned int count;

    /*
    // Setup Circular Buffers, Crash and Burn if FAIL
    if (!CB_Init(&TxCB, tx_spi_buffer_array, SPI_BUFFER_SIZE)) {
        LED_1 = 1;
        LED_2 = 1;
        LED_3 = 1;
        LED_4 = 1;
        while (1);
    }
    if (!CB_Init(&RxCB, rx_spi_buffer_array, SPI_BUFFER_SIZE)) {
        LED_1 = 1;
        LED_2 = 1;
        LED_3 = 1;
        LED_4 = 1;
        while (1);
    }*/

    rf_state.init_SPI2_return = RET_OK;
    /*
     * SPI2 Peripheral Pin Select
     * CLK = RP57/RC9
     * nSSEL = RP41/RB9
     * MISO = RP40/RB8
     * MOSI = RP39/RB7
     */

    /*********************
     * SPI2 Configuration
     *********************/
    SPI2STATbits.SPIEN = 0;     // Disable SPI2 for Configuration
    IFS2bits.SPI2IF = 0;        // Clear the Interrupt Flag
    
    //IPC8bits.SPI2IP = 6;        // Sets the Interrupt Prioriety to 6

    // SPI2CON1 Register Settings
    SPI2CON1bits.DISSCK = 0;    // Internal Serial Clock is Enabled
    SPI2CON1bits.DISSDO = 0;    // SDO2 pin is controlled by the module
    SPI2CON1bits.MODE16 = 0;    // Communication is 0=8-bits, 1=16bits wide

    SPI2CON1bits.SMP = 0;       // Input Data is Sampled at the Middle of Data Output Time
    SPI2CON1bits.CKE = 0;       // Serial Output data changes on leading edge
    SPI2CON1bits.CKP = 0;       // Idle state for clock is logic level low
    SPI2CON1bits.MSTEN = 1;     // Master Mode Enabled
    // SPI Clock Freq of 3.5Mhz
    // Fsck = Fp/PPRE*SPRE => 3,500,000 = 70,000,000/(4*5)
    SPI2CON1bits.PPRE = 2;      // Primary Prescale 4:1
    SPI2CON1bits.SPRE = 3;      // Secondary Prescale 5:1

    // SPI2CON2 Register Settings
    SPI2CON2bits.FRMEN = 0;     // Framed Mode 0=Disabled, 1=Enabled
    SPI2CON2bits.SPIBEN = 0;    // Enhanced Buffer is Disabled
    
    // Interrupt Controller Settings
    IFS2bits.SPI2EIF = 0;       // Clear the SPI2 Error Interrupt Flag Status bit
    IFS2bits.SPI2IF = 0;        // CLear the Interrupt Flag
    //DMA2REQbits.FORCE=1;
    //while (DMA2REQbits.FORCE == 1);
    IEC2bits.SPI2IE = 0;        // Enable the Interrupt
    

    /*********************
     * DMA2 TX Configuration
     *********************/
    IFS1bits.DMA2IF = 0;        // Clear the DMA Interrupt Flag bit
    IPC6bits.DMA2IP = 0b000;
    DMA2CONbits.CHEN = 0;       // Disable DMA3 for Configuration
    DMA2CONbits.SIZE = 1;       // Data is Byte sized
    DMA2CONbits.DIR = 1;        // Read RAM, Write to Perifpheral
    DMA2CONbits.HALF = 0;       // Interrupt when all data is moved
    DMA2CONbits.NULLW = 0;      // Normal Opertaion
    DMA2CONbits.AMODE = 0b00;   // Register Indirect w/ Post-Increment
    DMA2CONbits.MODE = 0b01;//0b10;    // Continuous, Ping-Pong Enabled

    config = DMA2CON | 0b1000000000000000;
    irq = 0b00100001;                   // Setting for SPI2 Transfer
    count = 1;                  // Nuber of Bytes exchanged
    pad_address = (volatile unsigned int) &SPI2BUF; //Name of SPI2 shared buffer
    stb_address = 0x0;

    // Open DMA call to setup DMA
    OpenDMA2(config, irq,(long unsigned int)TxBufferKEN, stb_address, pad_address, count);
//    DMA2CNT = 0;                // DMA3CNT + 1 DMA Requests
 //   DMA2REQbits.IRQSEL = 33;    // DMA Peripheral set to SPI2 Transfer Done

   // DMA2PAD = (volatile unsigned int) &SPI2BUF;

   // DMA2STAL = (unsigned int) &TxBufferA;
    //DMA2STAH = 0x0000;

    //DMA2STBL = (unsigned int) &TxBufferB;
    //DMA2STBH = 0x0000;

    IEC1bits.DMA2IE = 0;        // Clears the DMA Interrupt Enable bit
    DMA2CONbits.CHEN = 1;       // Enable DMA Channel

    /*********************
     * DMA3 RX Configuration
     *********************/
    IFS2bits.DMA3IF = 0;        // Clear the DMA Interrupt Flag bit
    IPC9bits.DMA3IP = 0b001;
    DMA3CONbits.CHEN = 0;       // Disable DMA3 for Configuration
    DMA3CONbits.SIZE = 1;       // Data is Byte sized
    DMA3CONbits.DIR = 0;        // Read Peripheral, Write to RAM
    DMA3CONbits.HALF = 0;       // Interrupt when all data is moved
    DMA3CONbits.NULLW = 0;      // Normal Write Opertaion
    DMA3CONbits.AMODE = 0b00;   // Register Indirect w/ Post-Increment
    DMA3CONbits.MODE = 0b00;    // Continuous, Ping-Pong Enabled

    config = DMA3CON | 0b1000000000000000;
    irq = 33;                   // Setting for SPI2 Transfer
    count = 1;                  // Nuber of Bytes exchanged
    pad_address = (volatile unsigned int) &SPI2BUF; //Name of SPI2 shared buffer
    stb_address = 0x0;

    // Open DMA call to setup DMA
    OpenDMA3(config, irq, (long unsigned int) RxBufferKEN, stb_address, pad_address, count);
    //DMA3CNT = 0;                // DMA3CNT + 1 DMA Requests
    //DMA3REQbits.IRQSEL = 33;    // DMA Peripheral set to SPI2 Transfer Done

    //DMA3PAD = (volatile unsigned int) &SPI2BUF;

    //DMA3STAL = (unsigned int) &RxBufferA;
    //DMA3STAH = 0x0000;

    //DMA3STBL = (unsigned int) &RxBufferB;
    //DMA3STBH = 0x0000;

    IEC2bits.DMA3IE = 1;        // Set the DMA Intterupt Enable bit
    DMA3CONbits.CHEN = 1;       // Enable DMA Channel

    /*********************
     * SPI2 Enable and DMA Force
     *********************/
//    DMA2REQbits.FORCE = 1;      // Force first two words to fillin Tx Buffer
//    while(DMA2REQbits.FORCE == 1);
//
//    DMA3REQbits.FORCE = 1;      // Force first two words to fillin Tx Buffer
//    while(DMA3REQbits.FORCE == 1);

//    SPI2STATbits.SISEL = 0b011;  // Interrupt when the SPIx receive buffer is full (SPIxRBF bit set)
    SPI2STATbits.SPISIDL = 0;   // Contine Module in Idle Mode
    SPI2STATbits.SPIROV = 0;    // Clear Overflow Flag
    SPI2STATbits.SPIEN = 1;     // Enable SPI Module

    
    return rf_state.init_SPI2_return;
}

/*
 * XBEE Init function.
 */
return_value_t xbee_init() {
    uint32_t i,j;
    bool fail;

//    LED_1 = 0;
//    LED_2 = 0;
//    LED_3 = 0;
//    LED_4 = 0;
    XBEE_nSSEL = 1;
    fail = 1;
    for(i=0;i<XBEE_RESET_RETRIES && fail;++i){
        XBEE_nRESET = 1;
        for(j=0;j<10000;++j){
            XBEE_nRESET = 1;
        }
        XBEE_nRESET = 0;
        XBEE_DOUT_OUTPUT;
        XBEE_DOUT = 0;
//        LED_1 = 1;
//        LED_2 = 1;
        j=0;
        while(XBEE_nATTN && (j++)<XBEE_RESET_WAIT_CYCLES);
        fail = XBEE_nATTN;
        XBEE_nRESET = 1;
        XBEE_DOUT_INPUT;
    }
    if(fail){
        rf_state.init_XBEE_return = RET_ERROR;
        return rf_state.init_XBEE_return;
    }
//    LED_3 = 1;
    /*
//    tx_spi_buffer_array[0] = 0x01;
  //  tx_spi_buffer_array[1] = 0x02;
   // tx_spi_buffer_array[2] = 0x03;
    TxBufferKEN[0]= 1;
    TxBufferKEN[1]= 2;
    TxBufferKEN[2]= 3;

    DMA2CONbits.CHEN = 0;
    DMA3CONbits.CHEN = 0;
    DMA2CNT = 2;
    DMA3CNT = 2;
    DMA2CONbits.CHEN = 1;
    DMA3CONbits.CHEN = 1;
    uint32_t dma2 = rf_state.dma2_int_cnt;
    uint32_t dma3 = rf_state.dma3_int_cnt;

    //SPI2BUF = tx_spi_buffer_array[0];
    XBEE_nSSEL = 0;
    
    DMA2REQbits.FORCE = 1;//start transfer
    //wait for dma interrupt
    while(dma3==rf_state.dma3_int_cnt){
        LED_4 = 1;
    }
    LED_4 = 0;
    if(RxBufferKEN[0]==0x7E){
        LED_1 = 1;
    } else {
        LED_1 = 0;
    }
    XBEE_nSSEL = 1;

    

    //DO IT AGAIN TO MAKE SURE:)
    XBEE_nSSEL = 0;
    for(i=0;i<16*50;++i){
    TxBufferKEN[i]= SPI_BUFFER_SIZE-i;
    }
    TxBufferKEN[0] = RxBufferKEN[0];
    TxBufferKEN[1] = RxBufferKEN[1];
    TxBufferKEN[2] = RxBufferKEN[2];
    DMA2CONbits.CHEN = 0; //NEEDED OR WE CAN ONLY DO ONE TRANSFER!!!
    DMA3CONbits.CHEN = 0;
    DMA2CNT = SPI_BUFFER_SIZE-1;
    DMA3CNT = SPI_BUFFER_SIZE-1;
    DMA2CONbits.CHEN = 1;
    DMA3CONbits.CHEN = 1;
    dma3 = rf_state.dma3_int_cnt;

    DMA2REQbits.FORCE = 1;//start transfer
    //wait for dma interrupt
    while(dma3==rf_state.dma3_int_cnt){
        LED_3 = 1;
    }
    LED_3 = 0;
    XBEE_nSSEL = 1;*/

    rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_IP;

    rf_state.init_XBEE_return = RET_OK;
    return rf_state.init_XBEE_return;
}

return_value_t rf_init()
{
    //init state
    rf_state.process_lock = 1;
    rf_state.xbee_state = XBEE_STATE_INIT;
    rf_state.xbee_at_req = 0;
    rf_state.at_packet.raw_packet.valid = 0;
    rf_state.cur_tx_packet_type = XBEE_API_FRAME_TX_IPV4;
    rf_state.cur_tx_ip_packet.raw_packet.valid = 0;
    rf_state.cur_tx_at_packet.raw_packet.valid = 0;
    rf_state.cur_rx_raw_packet.valid = 0;
    rf_state.dma2_int_cnt = rf_state.dma3_int_cnt = 0;
    rf_state.init_return = RET_OK;
    rf_state.cur_raw_packet = 0;
    rf_state.cur_packet_timeout_ctr = 0;
    rf_state.pending_rx_packet.valid = 0;
    rf_state.cur_modem_status = XBEE_MODEM_STATUS_RESET;
    rf_state.init_return = RET_OK;
    //init Circular buffers
    if(rf_state.init_return==RET_OK){
        if(CB_Init(&rf_state.ip_tx_buffer,tx_spi_buffer_array,  SPI_BUFFER_SIZE_TX)==SUCCESS) {
            //ok
        } else {
            rf_state.init_return = RET_ERROR;
        }
    }

    if(rf_state.init_return==RET_OK){
        if(CB_Init(&rf_state.ip_rx_buffer, rx_spi_buffer_array, SPI_BUFFER_SIZE_RX)==SUCCESS) {
            //ok
        } else {
            rf_state.init_return = RET_ERROR;
        }
    }
    
    //init spi & dma
    if(rf_state.init_return==RET_OK){
        spi2_init();
        if(rf_state.init_SPI2_return!=RET_OK){
            rf_state.init_return = RET_ERROR;
        }
    }
    //init xbee
    if(rf_state.init_return==RET_OK){
        xbee_init();
        if(rf_state.init_XBEE_return!=RET_OK){
            rf_state.init_return = RET_ERROR;
        }
    }
    rf_state.process_lock = 0;
    return rf_state.init_return;
}

void rf_transmit_spi_packet()
{
    long unsigned int sta_address;
    XBEE_nSSEL = 0;
    if(rf_state.cur_tx_packet_type == XBEE_API_FRAME_TX_IPV4){
        rf_state.cur_raw_packet = &rf_state.cur_tx_ip_packet.raw_packet;
    } else {
        rf_state.cur_raw_packet = &rf_state.cur_tx_at_packet.raw_packet;
    }    
    DMA2CONbits.CHEN = 0; //NEEDED OR WE CAN ONLY DO ONE TRANSFER!!!
    DMA3CONbits.CHEN = 0;
    DMA2CNT = rf_state.cur_raw_packet->length-1;
    DMA3CNT = DMA2CNT;
    sta_address = (long unsigned int)rf_state.cur_raw_packet->raw_data;
    DMA2STAL = sta_address & 0xFFFF;
    DMA2STAH = sta_address >> 16;
    sta_address = (long unsigned int)TxBufferDummy;
    DMA3STAL = sta_address & 0xFFFF;
    DMA3STAH = sta_address >> 16;
    DMA2CONbits.AMODE = 0b00; //enable postincrement
    DMA3CONbits.AMODE = 0b01; //disable postincrement (saves memory)
    DMA2CONbits.CHEN = 1;
    DMA3CONbits.CHEN = 1;

    DMA2REQbits.FORCE = 1;//start transfer   
}

void rf_receive_spi_packet()
{
    long unsigned int sta_address;
    XBEE_nSSEL = 0;
    DMA2CONbits.CHEN = 0;
    DMA3CONbits.CHEN = 0;
    DMA2CNT = 2; //3 bytes header
    DMA3CNT = DMA2CNT;
    sta_address = (long unsigned int)TxBufferDummy;
    DMA2STAL = sta_address & 0xFFFF;
    DMA2STAH = sta_address >> 16;
    sta_address = (long unsigned int)RxBufferHeader;
    DMA3STAL = sta_address & 0xFFFF;
    DMA3STAH = sta_address >> 16;
    DMA2CONbits.AMODE = 0b01; //disable postincrement
    DMA3CONbits.AMODE = 0b00; //enable postincrement
    DMA2CONbits.CHEN = 1;
    DMA3CONbits.CHEN = 1;
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    DMA2REQbits.FORCE = 1;//start transfer
}

/*uint8_t compute_checksum(uint8_t* data, unsigned length)
{
        unsigned i,j;
        uint16_t* data_int = (uint16_t*) data;
        uint16_t cks16 = 0x0;
        uint8_t cks8 = 0x0;
        uint8_t res = 0xFF;
        j = (length-1)>>1;

        for(i=1;i<j;++i){
                cks16 ^= data_int[i];
        }

        if((j<<1)<(length-1)){
                cks8^=data[length-2];
        }
        cks8 ^= data[2];
        cks8 ^= cks16&0xFF;
        cks8 ^= cks16>>8;

        res -= cks8;
        return res;
}
 */

inline uint8_t compute_checksum(uint8_t* data, unsigned length){
#define FANCYCKS
#ifdef FANCYCKS
    //TODO: add support for more than 256 bytes (overflow...)
    uint16_t result = 0;
     unsigned int l = length - 5;
     data += 3;
     asm volatile ( "repeat %2\nsub.b %0,[%1++],%0"
           : "+r" (result), "+r" (data)
           : "r" (l)
           : "_RCOUNT");
     result = (0xFF+result)&0xFF;
     /*
      The assembly code is equivalent to:
        uint16_t result = 0;
	for(l=0;l<length-4;){
		result-=data[l++];
	}
     	result = (0xFF+result)&0xFF;

      */
     return result;
#else
     	uint16_t result2;
	unsigned l;
        //uint8_t data_test[100];
        //for(l=0;l<length;++l)
        //    data_test[l] = data[l];
	data+=3;
	result2 = 0;
	l = length-4;
     	while(l){
		//printf("%x\n",data[l-1]);
        	result2 += data[--l];
	}

     	result2 = 0xFF-(result2&0xFF);
        return result2;
#endif
}

return_value_t allocate_ip_packet(uint16_t* allocateAmount, xbee_tx_ip_packet_t* ip_data)
{
    ip_data->raw_packet.raw_data = malloc(allocateAmount + LENGTH_XBEE_IPv4_FRAME_NODATA);
    if(ip_data->raw_packet.raw_data==NULL) {
        return RET_ERROR;
    }
    ip_data->user_data_location = &ip_data->raw_packet.raw_data[LENGTH_XBEE_IPv4_FRAME_NODATA-LENGTH_XBEE_CHECKSUM];
    ip_data->allocationLength = allocateAmount;

    return RET_OK;
}

return_value_t transmit_ip_packet(xbee_tx_ip_packet_t* ip_data)
{
    static uint16_t ip_frame_id = 0;
    uint8_t rawDataSize;

    rawDataSize = (ip_data->raw_packet.length - LENGTH_XBEE_START_DELIMITER - LENGTH_XBEE_API_LENGTH - LENGTH_XBEE_CHECKSUM);

    // Start making the raw data for ip transmission
    ip_data->raw_packet.raw_data[0] = 0x7E;
    ip_data->raw_packet.raw_data[1] = rawDataSize>>8;
    ip_data->raw_packet.raw_data[2] = rawDataSize&0xFF;
    ip_data->raw_packet.raw_data[3] = XBEE_API_FRAME_TX_IPV4;
    ip_data->raw_packet.raw_data[4] = ip_frame_id;

    // Places the destination IP address, IP port, and source port to the packet as defined in datasheet
    ip_data->raw_packet.raw_data[5] = ip_data->options.dest_address[0];
    ip_data->raw_packet.raw_data[6] = ip_data->options.dest_address[1];
    ip_data->raw_packet.raw_data[7] = ip_data->options.dest_address[2];
    ip_data->raw_packet.raw_data[8] = ip_data->options.dest_address[3];

    ip_data->raw_packet.raw_data[9] = ip_data->options.dest_port[0];
    ip_data->raw_packet.raw_data[10] = ip_data->options.dest_port[1];

    ip_data->raw_packet.raw_data[11] = ip_data->options.source_port[0];
    ip_data->raw_packet.raw_data[12] = ip_data->options.source_port[1];

    // This is the user defined protocol UDP/TCP and if the port will be left open
    ip_data->raw_packet.raw_data[13] = ip_data->options.protocol;
    ip_data->raw_packet.raw_data[14] = ip_data->options.leave_open;

    // Creates the Checksum as defined in the Xbee Wifi datasheet
    ip_data->raw_packet.raw_data[15+ip_data->allocationLength] = compute_checksum(ip_data->raw_packet.raw_data, ip_data->raw_packet.length);

    // Sets the dyanmic and valid flags
    ip_data->raw_packet.dynamic = 1;
    ip_data->raw_packet.valid = 1;

    // Writes the raw packet into the Tx Circular Buffer
    //CB_WriteMany(&TxCB, ip_data->raw_packet.raw_data, ip_data->raw_packet.raw_data, 1);
    CB_WriteMany(&rf_state.ip_tx_buffer, ip_data->raw_packet.raw_data, ip_data->raw_packet.raw_data, 1);

    // Iterate IP frame id
    ip_frame_id++;
    return RET_OK;
}

return_value_t xbee_at_cmd_no_cb(const char *atxx, const uint8_t *parmval, int parmlen, bool queued, xbee_at_packet_t* at_data)
{
    return xbee_at_cmd(atxx, parmval, parmlen, queued, at_data,0,0,0);            
}

return_value_t xbee_at_cmd(const char *atxx, const uint8_t *parmval, int parmlen, bool queued, xbee_at_packet_t* at_data, XBEE_TRANSMITTED_CB, XBEE_RESPONSE_CB, uint16_t timeout)
{
    uint16_t i;
    static uint8_t at_frame_id = 1; //if we start from zero, the first cmd wont get a response
    uint8_t* rawPacket;
    uint16_t rawPacketSize;
    uint16_t rawDataSize;

    rawPacketSize = parmlen + LENGTH_XBEE_AT_FRAME_NOPARAM;
    rawPacket = malloc(rawPacketSize);
    if(rawPacket==NULL) {
        return RET_ERROR;
    }

    rawDataSize = (rawPacketSize-LENGTH_XBEE_START_DELIMITER-LENGTH_XBEE_API_LENGTH-LENGTH_XBEE_CHECKSUM);

    // Create the actual raw data based on the XBee Wifi Data sheet for AT command API
    rawPacket[0] = 0x7E;
    rawPacket[1] = rawDataSize>>8;
    rawPacket[2] = rawDataSize&0xFF;
    // Sets the AT command frame to either send immediately or queued based on user input
    if(queued){
        rawPacket[3] = XBEE_API_FRAME_ATCMD_QUEUED;
    }
    else{
        rawPacket[3] = XBEE_API_FRAME_ATCMD;
    }
    rawPacket[4] = at_frame_id;
    rawPacket[5] = atxx[0];
    rawPacket[6] = atxx[1];
    for(i=0;i<parmlen;i++) {
        rawPacket[i+7] = parmval[i];
    }
    rawPacket[i+7] = compute_checksum(rawPacket, rawPacketSize);
    
    // Pass Raw created raw packet into our at_packet struct
    // TODO: add time out call
    at_data->raw_packet.raw_data = rawPacket;
    at_data->raw_packet.length = rawPacketSize;
    at_data->raw_packet.dynamic = 1;
    at_data->raw_packet.valid = 1;
    at_data->raw_packet.response_received.at_cmd = at_cmd;
    at_data->raw_packet.transmitted = ip_tx;
    at_data->raw_packet.response_time_out = timeout;

    // Pass the AT ID and Frame ID to struct
    at_data->options.at_cmd_id[0] = atxx[0];
    at_data->options.at_cmd_id[1] = atxx[1];
    at_data->options.frame_id = at_frame_id;

    // Iterate on the frame id
    at_frame_id++;
    return RET_OK;
}

void rf_tick(unsigned ms){
    if(rf_state.init_return==RET_OK){
        if(rf_state.cur_packet_timeout_ctr>=ms){
            rf_state.cur_packet_timeout_ctr-=ms;
        } else {
            rf_state.cur_packet_timeout_ctr=0;
        }
    }
}


void rf_process()
{
    uint8_t cks;
    uint8_t frame_id, status;
    uint16_t at_cmd;
    xbee_rx_ip_packet_t ip_rx;
    void (*transmitted_cb)() = 0;

    if(rf_state.init_XBEE_return!=RET_OK){
        return; //XBEE not functional
    }

    while(rf_state.process_lock); //wait for interrupt handler
    //rf_state.process_lock = 1;
    //if(!rf_state.process_lock){
    //    return;
    //}
    //Check if pending transmissions response callback timed out
    switch(rf_state.xbee_state){
        case XBEE_STATE_IDLE_TRANSMIT_IP:
        case XBEE_STATE_IDLE_TRANSMIT_AT:
            if(rf_state.cur_raw_packet){
                if(rf_state.cur_raw_packet->valid && rf_state.cur_packet_timeout_ctr==0){
                    //current transmit packet callback timed out
                    rf_state.cur_raw_packet->valid = 0; //we're done with this packet
                } else {
                    //current transmit packet valid and waiting for callback
                }
            }
            //check for data in the raw incoming buffer            
            break;
        case XBEE_STATE_TRANSMIT:
        case XBEE_STATE_TRANSMITTED:
        case XBEE_STATE_PACKET_RECEIVED:
        case XBEE_STATE_INIT:
        case XBEE_STATE_RECEIVE_HEADER:
        case XBEE_STATE_RECEIVE_FRAME:
        default:
            //don't handle incoming data while still receiving/sending or when there's an error
            break;
    };

    //Update the state
    switch(rf_state.xbee_state){
        case XBEE_STATE_TRANSMIT:
            //do nothing, wait till transmitted becomes active after DMA interrupt
            break;
        case XBEE_STATE_IDLE_TRANSMIT_IP:
            if(XBEE_nATTN){
                if(rf_state.xbee_at_req){
                    //go to TRANSMIT_AT MODE
                    rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_AT;
                } else {
                    //at_req is not asserted, remain in transmit_ip mode
                    //TODO: if there's an IP packet to send, start sending it and go to XBEE_STATE_TRANSMIT
                    if(!rf_state.cur_raw_packet || !rf_state.cur_raw_packet->valid) //wait for current packet response to time out
                    if(CB_ReadMany(&rf_state.ip_tx_buffer,(void*)(&rf_state.cur_tx_ip_packet),sizeof(xbee_tx_ip_packet_t))){
                                if(rf_state.cur_tx_ip_packet.raw_packet.valid){
                                    //if not valid, we just discard it
                                    //start the dma
                                    rf_state.xbee_state = XBEE_STATE_TRANSMIT;
                                    rf_state.cur_tx_packet_type = XBEE_API_FRAME_TX_IPV4;
                                    rf_transmit_spi_packet();
                                } else {
                                    //discard packet. note: we do not free the data!
                                }
                            }
                }
            } else {
                //go to receive
                rf_state.xbee_state = XBEE_STATE_RECEIVE_HEADER;
                rf_receive_spi_packet();
            }
            break;
        case XBEE_STATE_IDLE_TRANSMIT_AT:
            if(XBEE_nATTN){
                if(rf_state.xbee_at_req){
                    //check if there's AT data to send
                    //TODO: if there's an AT command to send, start sending it and go to XBEE_STATE_TRANSMIT
                    if(!rf_state.cur_raw_packet || !rf_state.cur_raw_packet->valid){ //wait for current packet response to time out
                        if(rf_state.at_packet.raw_packet.valid){
                                //if not valid, we just discard it
                                //start the dma
                                rf_state.xbee_state = XBEE_STATE_TRANSMIT;
                                rf_state.cur_tx_packet_type = XBEE_API_FRAME_ATCMD;
                                rf_state.cur_tx_at_packet = rf_state.at_packet;//copy packet
                                rf_state.at_packet.raw_packet.valid = 0;
                                rf_transmit_spi_packet();
                            } else {
                                //discard packet. note: we do not free the data!
                        }
                    }
                } else {
                    //at_req was disabled, go back to transmit_ip mode
                    rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_IP;
                }
            } else {
                //go to receive
                rf_state.xbee_state = XBEE_STATE_RECEIVE_HEADER;
                rf_receive_spi_packet();
            }
            break;
        case XBEE_STATE_TRANSMITTED:
            //free packet pointer if necessary.
            if(rf_state.cur_raw_packet->valid && rf_state.cur_raw_packet->dynamic){
                free(rf_state.cur_raw_packet->raw_data);
                rf_state.cur_raw_packet->raw_data = 0;
            }
            if(rf_state.cur_raw_packet->valid){
                if(rf_state.cur_raw_packet->response_time_out==0){
                    //we're done with this packet
                    rf_state.cur_raw_packet->valid = 0;
                    rf_state.cur_packet_timeout_ctr = 0;
                } else {
                    //start countdown
                    rf_state.cur_packet_timeout_ctr = rf_state.cur_raw_packet->response_time_out;
                }
                //call the transmitted callback if set
                transmitted_cb = rf_state.cur_raw_packet->transmitted;
                
            }
            //go back to IDLE_TRANSMIT_IP or IDLE_TRANSMIT_AT depending on the at_req flag
            if(rf_state.xbee_at_req){
                rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_AT;
            } else {
                rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_IP;
            }

            break;
        case XBEE_STATE_PACKET_RECEIVED:
            if(rf_state.cur_rx_raw_packet.valid){
                //compute checksum to see if it is really valid
                cks = compute_checksum(rf_state.cur_rx_raw_packet.raw_data,rf_state.cur_rx_raw_packet.length);
                if(cks==rf_state.cur_rx_raw_packet.raw_data[rf_state.cur_rx_raw_packet.length-1]){
                    //checksum OK
                    //handle packout outside state machine loop
                    rf_state.pending_rx_packet = rf_state.cur_rx_raw_packet;
                    rf_state.cur_rx_raw_packet.valid = 0; //packet handled
                } else {
                    //invalid packet, free data and ignore
                    rf_state.cur_rx_raw_packet.valid = 0;
                    if(rf_state.cur_rx_raw_packet.dynamic){
                        free(rf_state.cur_rx_raw_packet.raw_data);
                        rf_state.cur_rx_raw_packet.raw_data = 0;
                    }
                }                
            }
            //go back to IDLE_TRANSMIT_IP or IDLE_TRANSMIT_AT depending on the at_req flag
            if(rf_state.xbee_at_req){
                rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_AT;
            } else {
                rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_IP;
            }
            break;
        case XBEE_STATE_RECEIVE_FRAME:
            //do nothing, wait till XBEE_STATE_PACKET_RECEIVED is active after the second receive DMA interrupt
            break;
        case XBEE_STATE_RECEIVE_HEADER:
            //do nothing, we will go to XBEE_STATE_RECEIVE_FRAME automatically after a DMA interrupt
            break;
        case XBEE_STATE_INIT:
        default:
            //error!!!
            break;
    };
    //rf_state.process_lock = 0;

    //call callbacks here, outside of the lock
    if(transmitted_cb){
        transmitted_cb();
    }
    if (rf_state.pending_rx_packet.valid) {
        
        //if it is an TX STATUS or AT RESPONSE PACKET, check if we have a pending transmit
        //if IP RX: add to IP RX buffer
        //else ignore for now (free buffer!!!)
        switch (rf_state.pending_rx_packet.raw_data[3]) {//API identifier
            case XBEE_API_FRAME_TX_STATUS:
                //grab the frame id
                
                frame_id = rf_state.pending_rx_packet.raw_data[4];
                //grab the status
                status = rf_state.pending_rx_packet.raw_data[5];
                if (rf_state.cur_raw_packet && rf_state.cur_raw_packet->valid && rf_state.cur_tx_packet_type == XBEE_API_FRAME_TX_IPV4) {
                    //there is a pending packet
                    if(rf_state.cur_tx_ip_packet.options.frame_id == frame_id){
                        //frame id matches
                        rf_state.cur_raw_packet->response_received.ip_tx(frame_id, status);
                        rf_state.cur_raw_packet->valid = 0; //packet is now fully handled
                    }
                }
                if (rf_state.pending_rx_packet.dynamic) {
                    free(rf_state.pending_rx_packet.raw_data);
                    rf_state.pending_rx_packet.raw_data = 0;
                }
                break;
            case XBEE_API_FRAME_ATCMD_RESP:
                //grab the frame id
                LED_2 = 1;
                frame_id = rf_state.pending_rx_packet.raw_data[4];
                //grab the AT command
                at_cmd = (((uint16_t)rf_state.pending_rx_packet.raw_data[5])<<8) | (rf_state.pending_rx_packet.raw_data[6]&0xFF);
                //grab the status
                status = rf_state.pending_rx_packet.raw_data[7];
                if (rf_state.cur_raw_packet && rf_state.cur_raw_packet->valid && rf_state.cur_tx_packet_type == XBEE_API_FRAME_ATCMD
                    && rf_state.cur_tx_at_packet.options.frame_id == frame_id  && rf_state.cur_tx_at_packet.options.at_cmd_id==at_cmd){
                        if(rf_state.cur_raw_packet->response_received.at_cmd(frame_id, at_cmd, status, rf_state.pending_rx_packet.raw_data,rf_state.pending_rx_packet.length,rf_state.pending_rx_packet.dynamic)){
                            rf_state.cur_raw_packet->valid = 0; //packet is now fully handled
                            //CALLBACK NEEDS TO FREE MEMORY!!!
                        } else {
                            //AT command is not fully handled yet (e.g. scan) according to the callback
                        }                    
                } else {
                    //no callback, free message
                    if (rf_state.pending_rx_packet.dynamic) {
                        free(rf_state.pending_rx_packet.raw_data);
                        rf_state.pending_rx_packet.raw_data = 0;

                        LED_4 = 1;
                    }
                }
                break;
            case XBEE_API_FRAME_RX_IPV4:                
                ip_rx.raw_packet = rf_state.pending_rx_packet;
                ip_rx.options.checksum_error = 0;
                ip_rx.options.frame_id = XBEE_API_FRAME_RX_IPV4;
                ip_rx.options.protocol = rf_state.pending_rx_packet.raw_data[12];
                ip_rx.options.source_port = (((uint16_t)rf_state.pending_rx_packet.raw_data[10])<<8) | (rf_state.pending_rx_packet.raw_data[11]&0xFF);
                ip_rx.options.dest_port = (((uint16_t)rf_state.pending_rx_packet.raw_data[8])<<8) | (rf_state.pending_rx_packet.raw_data[9]&0xFF);
                ip_rx.options.source_addr[0] = rf_state.pending_rx_packet.raw_data[4];
                ip_rx.options.source_addr[1] = rf_state.pending_rx_packet.raw_data[5];
                ip_rx.options.source_addr[2] = rf_state.pending_rx_packet.raw_data[6];
                ip_rx.options.source_addr[3] = rf_state.pending_rx_packet.raw_data[7];
                ip_rx.options.total_packet_length = ip_rx.raw_packet.length-15;
                if(CB_WriteMany(&rf_state.ip_rx_buffer,&ip_rx,sizeof(xbee_rx_ip_packet_t),1)){
                    //success
                } else {
                    //if we cannot add it to the circular buffer, free the memory
                    if (rf_state.pending_rx_packet.dynamic) {
                        free(rf_state.pending_rx_packet.raw_data);
                        rf_state.pending_rx_packet.raw_data = 0;
                    }
                }
                break;
            case XBEE_API_FRAME_MODEM_STATUS:
                //grab the status
                LED_1 = 1;
                status = rf_state.pending_rx_packet.raw_data[4];
                rf_state.cur_modem_status = status;
                if (rf_state.cur_rx_raw_packet.dynamic) {
                    free(rf_state.cur_rx_raw_packet.raw_data);
                    rf_state.cur_rx_raw_packet.raw_data = 0;
                }
                break;
            default:
                //free unkown message
                if (rf_state.pending_rx_packet.dynamic) {
                        free(rf_state.pending_rx_packet.raw_data);
                        rf_state.pending_rx_packet.raw_data = 0;
                }
                break;
        };
        rf_state.pending_rx_packet.valid = 0;
    }

}

/***************************
 *  SPI2 DMA3 Receive Interrupt
 ***************************/
void __attribute__((__interrupt__, __auto_psv__)) _DMA3Interrupt(void)
{
    bool fail = 0;
    bool do_start_transmit;
    long unsigned int sta_address;
    //while(rf_state.process_lock);
    rf_state.process_lock = 1;
    switch(rf_state.xbee_state){
        case XBEE_STATE_TRANSMIT:
            //finished sending data, go to XBEE_STATE_TRANSMITTED
            XBEE_nSSEL = 1;            
            rf_state.xbee_state = XBEE_STATE_TRANSMITTED;
            break;
        case XBEE_STATE_RECEIVE_FRAME:
            //full packet received
            rf_state.cur_rx_raw_packet.valid = 1;
            rf_state.xbee_state = XBEE_STATE_PACKET_RECEIVED;
            XBEE_nSSEL = 1;
            break;
        case XBEE_STATE_RECEIVE_HEADER:
            rf_state.cur_rx_raw_packet.valid = 0;
            if(RxBufferHeader[0]==0x7E){                
                rf_state.cur_rx_raw_packet.dynamic = 1;
                rf_state.cur_rx_raw_packet.length = ((((uint16_t)RxBufferHeader[1])<<8)|(RxBufferHeader[2]&0xFF))+4;
                //read N bytes (rest of packet)
                if(rf_state.cur_rx_raw_packet.length<1500 && rf_state.cur_rx_raw_packet.length>4){
                    rf_state.cur_rx_raw_packet.raw_data = malloc(rf_state.cur_rx_raw_packet.length);
                    if(rf_state.cur_rx_raw_packet.raw_data){
                        //we're good, memory was allocated
                        rf_state.cur_rx_raw_packet.raw_data[0] = RxBufferHeader[0];
                        rf_state.cur_rx_raw_packet.raw_data[1] = RxBufferHeader[1];
                        rf_state.cur_rx_raw_packet.raw_data[2] = RxBufferHeader[2];
                        //set up DMA
                        DMA2CONbits.CHEN = 0;
                        DMA3CONbits.CHEN = 0;
                        DMA2CNT = rf_state.cur_rx_raw_packet.length-4; //data+cks bytes
                        DMA3CNT = DMA2CNT;
                        sta_address = (long unsigned int)TxBufferDummy;
                        DMA2STAL = sta_address & 0xFFFF;
                        DMA2STAH = sta_address >> 16;
                        sta_address = (long unsigned int)(&rf_state.cur_rx_raw_packet.raw_data[3]);
                        DMA3STAL = sta_address & 0xFFFF;
                        DMA3STAH = sta_address >> 16;
                        DMA2CONbits.AMODE = 0b01; //disable postincrement
                        DMA3CONbits.AMODE = 0b00; //enable postincrement
                        DMA2CONbits.CHEN = 1;
                        DMA3CONbits.CHEN = 1;
                        rf_state.xbee_state = XBEE_STATE_RECEIVE_FRAME;
                        do_start_transmit = 1;

                    } else {
                        fail = 1;
                    }
                } else {
                    fail = 1;
                }
            } else {
                fail = 1;
            }
            if(fail){
                //error, stop receiving
                XBEE_nSSEL = 1;
                rf_state.xbee_state = XBEE_STATE_PACKET_RECEIVED;
            }
            break;
        case XBEE_STATE_IDLE_TRANSMIT_IP:            
        case XBEE_STATE_IDLE_TRANSMIT_AT:            
        case XBEE_STATE_TRANSMITTED:
        case XBEE_STATE_PACKET_RECEIVED:        
        case XBEE_STATE_INIT:
        default:
            //error, we should never be in any of these states!
            break;
    };

    rf_state.process_lock = 0;
    rf_state.dma3_int_cnt++;
    if(do_start_transmit){
        DMA2REQbits.FORCE = 1;//start transfer
    }
    IFS2bits.DMA3IF = 0;
}

void __attribute__((__interrupt__, __auto_psv__)) _INT2Interrupt(void)
{
    //TODO
}
