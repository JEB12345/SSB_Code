#include "p33Exxxx.h"
#include "sensor_loadcell.h"
#include "sensor_pindefs.h"
#include "sensor_state.h"
#include <dma.h>

loadcell_data loadcell_state;

inline void spi_wait() {
    while (loadcell_state.spi_state != SPI_IDLE);
}

return_value_t loadcell_init()
{
    unsigned i;
    loadcell_state.init_return = RET_OK;
    for(i=0;i<4;++i)
        loadcell_state.values[i] = 0;

    SHD = 1;

    IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
    IEC0bits.SPI1IE = 0; // Disable the Interrupt

    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0; // Internal SPI clock is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0; // Communication is byte-wide (8 bits)
    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time

    SPI1CON1bits.CKE = 0; // Serial output data changes on transition
    // from Idle clock state to active clock state
    SPI1CON1bits.CKP = 1; // Idle state for clock is a high level;
    // active state is a low level
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    SPI1CON1bits.PPRE = 0;//0b01; // Primary prescale bit for SPI clock; 0b11 = 1:1;  0b10 = 4:1; 0b01 = 16:1; 0b00 = 64:1
    SPI1CON1bits.SPRE = 0b011; // Secondary prescale bit for SPI clock; 0b111 = 1:1; 0b110 = 1:2 ... 0b000 = 1:8
    SPI1CON1bits.SSEN = 0; // Slave select pin disabled

    SPI1CON2bits.FRMEN = 0; // Frame mode disabled

    // SPISTAT Register Settings
    SPI1STATbits.SPIEN = 1; // Enable SPI module
    SPI1STATbits.SPISIDL = 0; // Continue module operation when device enters Idle mode

    // Interrupt Controller Settings
    SPI1STATbits.SPIROV = 0; // Clear SPI overflow bit
    IFS0bits.SPI1EIF = 0; // Clear SPI1 Error Interrupt Flag Status bit
    IPC2bits.SPI1IP = 0x06; // Set SPI1 Interrupt Priority Level to 1 = low priority
    IFS0bits.SPI1IF = 0; // Clear the Interrupt Flag
    IEC0bits.SPI1IE = 1; // Enable the Interrupt

    SG_DESELECT;
    loadcell_state.data_ready = 0;

    //loadcell_state.spi_busy = 0; // currently no SPI transfer

    loadcell_state.spi_state = SPI_IDLE;

    uint8_t mode_byte_1 = 0;
    uint8_t mode_byte_2 = 0;
    uint8_t mode_byte_3 = 0;
    uint8_t config_byte_1;
    uint8_t config_byte_2;
    uint8_t config_byte_3;


    loadcell_state.spi_state = SPI_VARIOUS;
    SG_SELECT;
    for(i=0;i<65000;++i){
        Nop();Nop();
        Nop();Nop();
        Nop();Nop();
        Nop();Nop();
    }
    for(i=0;i<65000;++i){
        Nop();
        Nop();
    }
    //delay_us(500);
    //reset chip
    SPI1BUF = 0xFF;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = 0xFF;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = 0xFF;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = 0xFF;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = 0xFF;
    spi_wait();
    SG_DESELECT;
    //delay_ms(1);
    for(i=0;i<65000;++i){
        Nop();
        Nop();
    }
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    for(i=0;i<65000;++i){
        Nop();Nop();
        Nop();Nop();
        Nop();Nop();
        Nop();Nop();
    }
    SG_SELECT;
    //write the MODE register
    SPI1BUF = SG_REG_MODE;
    spi_wait();
    mode_byte_1 = 0b00011101;//continuous mode, transmit status reg, MCLK2 is clock, average 2 (FS/2)

    mode_byte_2 = 0b00000100;//sinc4 enabled | no parity | no clock divide | no single | 60hz rejection

    mode_byte_3 = 3;//100Hz

    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = mode_byte_1;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = mode_byte_2;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = mode_byte_3;
    spi_wait();
    SG_DESELECT;
    //delay_ms(1);
    for(i=0;i<65000;++i){
        Nop();Nop();
        Nop();Nop();
        Nop();Nop();
        Nop();Nop();
    }

    SG_SELECT;
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = SG_REG_CONFIG;
    spi_wait();
    //write the CONFIGURATION register
    config_byte_1 =  0b10000000;
    config_byte_2 = 0b11110000;
    config_byte_3 = 0b01011000;
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = config_byte_1;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = config_byte_2;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = config_byte_3;
    spi_wait();
    SG_DESELECT;
    //delay_ms(10);
    for(i=0;i<65000;++i){
        Nop();
        Nop();
    }
    IC4CON1bits.ICM = 0b010; //interrupt on falling edge
    IC4CON2bits.TRIGSTAT = 0;
    for(i=0;i<65000;++i){
        Nop();
        Nop();
    }
    return loadcell_state.init_return;
}

void __attribute__((__interrupt__, no_auto_psv)) _SPI1Interrupt(void) {
    SPI1STATbits.SPIROV = 0; // Clear SPI overflow bit
    switch (loadcell_state.spi_state) {
        case SPI_SG_READ_DATA_1:
            SPI1BUF = 0x0;
            loadcell_state.spi_state = SPI_SG_READ_DATA_2;
            break;
        case SPI_SG_READ_DATA_2:
            loadcell_state.sg_data_1 = SPI1BUF;
            SPI1BUF = 0x0;
            loadcell_state.spi_state = SPI_SG_READ_DATA_3;
            break;
        case SPI_SG_READ_DATA_3:
            loadcell_state.sg_data_2 = SPI1BUF;
            SPI1BUF = 0x0;
            loadcell_state.spi_state = SPI_SG_READ_DATA_4;
            break;
        case SPI_SG_READ_DATA_4:
            loadcell_state.sg_data_3 = SPI1BUF;
            SPI1BUF = 0x0;
            loadcell_state.spi_state = SPI_SG_READ_DATA_END;
            break;
        case SPI_SG_READ_DATA_END:
            loadcell_state.sg_status = SPI1BUF;
            loadcell_state.spi_state = SPI_IDLE;
            //copy the data to the right location
            LED_3 = !LED_3;
            if(!(loadcell_state.sg_status&0b10000000)){
                //ready bit is not set, so data is available
                //if(loadcell_state.sg_status&0b01000000){ //check for strain gauge error
                //    loadcell_state.state |= NODE_STATE_SG_ERROR;
                    //node_state.spring_forces[0] =14;
                //} else {
                //    loadcell_state.state &= !NODE_STATE_SG_ERROR;
                    //node_state.spring_forces[0] =sg_data_2;
                //}
                //if((sg_status&0b111)==0b000)
                //    ram_state.spring_forces[0] = (((uint32)(sg_data_1&0xFF))<<16) | (((uint32)(sg_data_2&0xFF))<<8) | (((uint32)(sg_data_3&0xFF)));
                if(loadcell_state.sg_status&0b00000100)
                {
                    //one of the correct channels was converted, store the result
                    loadcell_state.values[loadcell_state.sg_status&0b11] =
                            (((uint32_t)(loadcell_state.sg_data_1&0xFF))<<16)
                            | (((uint32_t)(loadcell_state.sg_data_2&0xFF))<<8)
                            | (((uint32_t)(loadcell_state.sg_data_3&0xFF)));
                    //ram_state.spring_forces[sg_status&0b11] |= sg_data_3&0xFF;
                    LED_4 = !LED_4;

                }
            }
            SG_DESELECT;
            Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
            Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
            Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
            Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
            SG_SELECT;
            loadcell_state.data_ready = 0;
            IEC2bits.IC4IE = 1;
            IFS2bits.IC4IF = 0; 
            
            break;
        case SPI_VARIOUS:
            loadcell_state.spi_state = SPI_IDLE;
            break;
        default:
            loadcell_state.spi_state = SPI_IDLE;
            break;
    };

    IFS0bits.SPI1EIF = 0; // Clear SPI1 Fault Interrupt Flag Status bit
    IFS0bits.SPI1IF = 0; // Clear the interrupt Flag

    //loadcell_state.spi_busy = 0; // indicate that next spi transfer may start
}







inline uint8_t spi_is_busy() {
    return loadcell_state.spi_state != SPI_IDLE;
}


/*void spi_read_id(){
    spi_wait();
    SG_SELECT;
    //delay_us(100);
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = 0b01100000;
    spi_wait();
    loadcell_state.spi_state = SPI_VARIOUS;
    SPI1BUF = 0b0;
    spi_wait();
    loadcell_state.values[0] =SPI1BUF;
    SG_DESELECT;
}*/

/*

void sg_read_data(){
    spi_wait();
    SG_SELECT;
    if(loadcell_state.data_ready){
        //no data available
        SG_DESELECT;
        return;
    } else {
        loadcell_state.data_ready = 0;
    }

    //read data register
    loadcell_state.spi_state = SPI_SG_READ_DATA_1;
    SPI1BUF = SG_REG_DATA | 0b01000000;
    spi_wait();
    SG_DESELECT;
    
}*/

void __attribute__((__interrupt__, no_auto_psv)) _IC4Interrupt(void) {
    unsigned i;
    LED_1 = !LED_1;
    if((!loadcell_state.data_ready) && (!SG_MISO) ){
        LED_2 = !LED_2;
        //disable interrupt
        IEC2bits.IC4IE = 0;
        //read data register
        //SG_SELECT;
        //Nop();Nop();Nop();
        loadcell_state.data_ready = 1;
        loadcell_state.spi_state = SPI_SG_READ_DATA_1;
        SPI1BUF = SG_REG_DATA | 0b01000000;

        //spi_wait();
    }
    IFS2bits.IC4IF = 0; // Reset respective interrupt flag
}

void loadcell_start()
{
    SG_SELECT;
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    IFS2bits.IC4IF = 0; // Clear the IC1 interrupt status flag
    IEC2bits.IC4IE = 1; // Enable IC1 interrupts
    _IC4Interrupt();
}



#ifdef SOMETHING

//internal state variables


unsigned char dma_spi_lc_tx_buffer[16] __attribute__((aligned(32 * 16)));
volatile unsigned char dma_spi_lc_rx_buffer[16] __attribute__((aligned(32 * 16)));


#define dma_spi_lc_start() do{\
	gpio_clear(dma_spi_lc.spi_cs);\
}while(0)


#define dma_spi_lc_stop() do{\
	gpio_set(dma_spi_lc.spi_cs);\
}while(0)

#define dma_spi_lc_write() do{\
        dma_spi_lc_stop();\
        dma_spi_lc_start();\
        DMA4CONbits.CHEN  = 1;\
        DMA3CONbits.CHEN  = 1;\
        DMA4REQbits.FORCE = 1;\
}while(0)

void init_load_cell(load_cell * e){
	e->torque = 0;
	e->flags = LC_F_ONBOARD_PROCESSING_UNFINISHED;
}

void init_load_cells(){
    SHD = 1; //ENABLE LDO

    loadcell_state.state = DMA_SPI_LC_IDLE;

    /************************************
     SPI1-MODULE
     ************************************/

    SPI1STATbits.SPIEN  = 0;     //Disable SPI module during configuration
    IEC0bits.SPI1IE     = 0; //disable interrupt. This is needed because we use DMA
    IFS0bits.SPI1IF     = 0; //clear the interrupt flag.
    IPC2bits.SPI1IP     = 0b000;
    SPI1CON1bits.MSTEN  = 1; //enable master mode
    SPI1STATbits.SPIROV = 0; // clear overflow flag

    SPI1CON1bits.DISSCK = 0; //Use the clock
    SPI1CON1bits.DISSDO = 0; //Enable data output. 
    SPI1CON1bits.MODE16 = 0; //Transmit bytes. Rx buffer is in byte, but we don't care because we are transmitting an even number of byte

    SPI1CON1bits.CKE    = 0; //data valid on rising edge
    SPI1CON1bits.CKP    = 1; //clock idle state is at high level
    SPI1CON1bits.SMP    = 0; //0=data is sampled at middle of clock time

    SPI1CON1bits.SSEN   = 0; //disable chip select bit (we do this ourselves)
    SPI1CON2bits.FRMEN  = 0;     //Frame support

    //Choose a clock frequency of 875 kHz, max accepted by AS5045 is 1Mhz
    //TODO: set frequency
    SPI1CON1bits.SPRE   = 0b011; //Select a secondary prescaler of 1:5
    SPI1CON1bits.PPRE   = 0b01; //select a primary prescaler of 16:1

    IEC0bits.SPI1IE     = 0;    //enable interrupt.
    SPI1STATbits.SPIEN  = 1;     //Enable SPI 1 module

    /************************************
     DMA3-MODULE
     ************************************/
    unsigned int config;
    unsigned int irq;
    unsigned long int stb_address;
    unsigned int pad_address;
    unsigned int count;
    
    DMA3CONbits.SIZE = 1;
    DMA3CONbits.DIR = 0; //Read to RAM from peripheral
    DMA3CONbits.AMODE = 0b00;// Register indirect with posincrement
    DMA3CONbits.MODE = 0b00;// continuous, No Ping Pong
    DMA3CONbits.HALF  = 0;
    IPC9bits.DMA3IP = 0b001; 
    config = DMA3CON|0b1000000000000000;
    irq = 0b00001010;// Select SPI1 as DMA Request source
    count = 0;   //1 byte per transfer
    IEC2bits.DMA3IE = 0; // Enable DMA Channel 3 interrupt
    IFS2bits.DMA3IF = 0;
    //DMA0CONbits.CHEN = 1; // Enable DMA Channel 0
    pad_address = (volatile unsigned int) &SPI1BUF;
    stb_address = 0x0;
    OpenDMA3( config, irq, (long unsigned int)dma_spi_lc_rx_buffer,
        stb_address,pad_address, count );
    IEC2bits.DMA3IE = 1;

    /*
    IEC2bits.DMA3IE = 0;
    IFS2bits.DMA3IF = 0;
    IPC9bits.DMA3IP = 0b001; //low priority, but needs to be higher than DMA4IP
    DMA3CONbits.CHEN  = 0;
    DMA3CONbits.SIZE  = 1;
    DMA3CONbits.DIR   = 0;//read, don't send
    DMA3CONbits.HALF  = 0;

    DMA3CONbits.AMODE = 0b00;// Register indirect with posincrement
    DMA3CONbits.MODE  = 0b00;// continuous, No Ping Pong
    DMA3STA = __builtin_dmaoffset(dma_spi_lc_rx_buffer);
    DMA3PAD = (volatile unsigned int) & SPI2BUF;
    DMA3REQbits.IRQSEL = 0b0100001; //SPI2
    DMA3CNT = 0;
    IEC2bits.DMA3IE = 1;
     */

    /************************************
     DMA4-MODULE
     ************************************/

    DMA4CONbits.SIZE = 1;
    DMA4CONbits.DIR = 0; //Read to RAM from peripheral
    DMA4CONbits.AMODE = 0b00;// Register indirect with posincrement
    DMA4CONbits.MODE = 0b00;// continuous, No Ping Pong
    DMA4CONbits.HALF  = 0;
    IPC9bits.DMA4IP = 0b001;
    config = DMA3CON|0b1000000000000000;
    irq = 0b00001010;// Select SPI1 as DMA Request source
    count = 0;   //1 byte per transfer
    IEC2bits.DMA3IE = 0; // Enable DMA Channel 3 interrupt
    IFS2bits.DMA3IF = 0;
    //DMA0CONbits.CHEN = 1; // Enable DMA Channel 0
    pad_address = (volatile unsigned int) &SPI1BUF;
    stb_address = 0x0;
    OpenDMA3( config, irq, (long unsigned int)dma_spi_lc_rx_buffer,
        stb_address,pad_address, count );
    IEC2bits.DMA3IE = 1;

    IEC2bits.DMA4IE = 0;
    IFS2bits.DMA4IF = 0;
    IPC11bits.DMA4IP = 0b000; //low priority

    DMA4CONbits.CHEN  = 0;
    DMA4CONbits.SIZE  = 1; //send per byte
    DMA4CONbits.DIR   = 1; //send, don't read
    DMA4CONbits.HALF  = 0; //only one buffer

    DMA4CONbits.NULLW = 0;

    DMA4CONbits.AMODE = 0b00;// Register indirect with post-increment
    DMA4CONbits.MODE  = 0b01;// 0b01 One - shot, No Ping Pong

    DMA4REQbits.IRQSEL = 0b0100001; //SPI2
    DMA4CNT = 0; //number of bytes to send

    DMA4STA = __builtin_dmaoffset(dma_spi_lc_tx_buffer); //transmission buffer
    DMA4PAD = (volatile unsigned int) & SPI2BUF;

    IEC2bits.DMA4IE = 0; //we don't need this interrupt, we use the interupt when everything is received

    /************************************
     CN19-MODULE
     ***e*********************************/

    CNEN2bits.CN19IE = 1;
    CNPU2bits.CN19PUE = 0;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 0; //don't enable it yet

    init_load_cell(&(lcs[0]));
    init_load_cell(&(lcs[1]));
    init_load_cell(&(lcs[2]));

    load_cell_reset();
}

inline void set_lc_torque(load_cell lc, int value, int adr) {
    lc.flags = LC_F_OK;
    lc.torque = value;
    sbcp_me_reg(adr,LCX_VALUE).u = value;
    sbcp_mark_new_low_latency_data_available();
}

#define NUMARGS(...)  (sizeof((char[]){__VA_ARGS__})/sizeof(char))
#define spi_write_bytes(...) do{\
    memcpy(dma_spi_lc_tx_buffer, (char [NUMARGS(__VA_ARGS__)]) {__VA_ARGS__}, NUMARGS(__VA_ARGS__)*sizeof(char));\
    DMA3CNT = NUMARGS(__VA_ARGS__)-1;\
    DMA4CNT = NUMARGS(__VA_ARGS__)-1;\
    dma_spi_lc_write();\
}while(0)

#define spi_led_on() spi_write_bytes(0x28,0x31)
#define spi_led_off() spi_write_bytes(0x28,0x30)
#define spi_led_blink() spi_write_bytes(0x28,0x30|BLINK)
#define spi_settings 0b00001000,0b00011000,0b00100000,0b00000001,  /*mode register*/\
                     0b00010000,0b00000000,0b00000111,0b11010111,  /*configuration register*/

int lc_error_count=0;

int reset_counter;
volatile short start_reading = 0;

void load_cell_process(){
    int v;
    int index;
    DMA_SPI_LC_read_value value;
    unsigned short p;
    if(start_reading){
        start_reading=0;
        dma_spi_lc.state = DMA_SPI_LC_READING_DEVICES;
        spi_write_bytes(0x58,0x00,0x00,0x00,0x00); // read 4 bytes
    }
    if(circular_buffer_ready){
        for(index = 0; index<CIRCULAR_BUFFER_SIZE; index++){

            IEC2bits.DMA3IE = 0;//disable writing to circular buffer while reading from it, without losing interrupts.
            value = circular_buffer[index]; //copy to remove race conditions with interupt
            IEC2bits.DMA3IE = 1;
            // step 1: check parity
            v = value.DATA[0] ^ value.DATA[1] ^ value.DATA[2];
            v = (v ^ v>>4) & 0x0f;
            p = (0x6996 >> v) & 1; //Look-up table
            if(value.DATA[0] == 0 && value.DATA[1] == 0 && value.DATA[2] == 0 && value.STATUS == 0){//while strictly speaking, this is a correct packet, it is more likely something is going wrong
                lc_error_count++;
            }
            if(p != (value.STATUS & 0b00010000)>>4){
                lc_error_count++;
            }else if(value.STATUS & 0b11100000){ //RDY, ERR, NOREF
                lc_error_count++;
            }else {
                switch(value.STATUS & 0b00001111){
                    case 0:
                        set_lc_torque(lcs[0], (value.DATA[0]<<8) | (value.DATA[1]),MDV_LC_AXIS_1);
                        break;
                    case 1:
                        set_lc_torque(lcs[1], (value.DATA[0]<<8) | (value.DATA[1]),MDV_LC_AXIS_2);
                        break;
                    case 2:
                        set_lc_torque(lcs[2], (value.DATA[0]<<8) | (value.DATA[1]),MDV_LC_AXIS_3);
                        break;
                    default:
                        lc_error_count++;
                }
            }
        }
        if(lc_error_count>100){
            if(dma_spi_lc.state == DMA_SPI_LC_WAITING_FOR_READOUT
            || dma_spi_lc.state == DMA_SPI_LC_READING_DEVICES){
                lc_error_count=0;
                load_cell_reset();
            }
        }
    }
}

void load_cell_reset(){
    IEC1bits.CNIE = 0;
    circular_buffer_ready = 0;
    reset_counter = 0;
    start_reading=0;
    dma_spi_lc.state = DMA_SPI_LC_WRITING_RESET;
    spi_write_bytes(0xff,0xff,0xff,0xff,0xff);
}

void load_cell_start_reading(){
    if(dma_spi_lc.state == DMA_SPI_LC_IDLE){
        //start reading
        dma_spi_lc.state = DMA_SPI_LC_WAITING_FOR_READOUT;
        IEC1bits.CNIE = 1;
    }
    if(dma_spi_lc.state == DMA_SPI_LC_WAITING_TO_WRITE_SETTINGS){
        if(reset_counter == 0){ //you need to wait at least 500us to start writing the settings. We wait for an additional 1ms so we are sure we waited long enough.
            reset_counter++;
        }else{
            dma_spi_lc.state = DMA_SPI_LC_WRITING_SETTINGS;
            spi_write_bytes(spi_settings);
        }
    }
}


/*******************************************************************************
 *
 * Interrupt
 *
 ******************************************************************************/

/**
 * Interrupt when the DMA finished reading all the bytes
 */
void __attribute__((__interrupt__ , no_auto_psv)) _DMA3Interrupt(){

    switch(dma_spi_lc.state){
        case DMA_SPI_LC_WRITING_RESET:
            dma_spi_lc.state = DMA_SPI_LC_WAITING_TO_WRITE_SETTINGS;
            break;
        case DMA_SPI_LC_WRITING_SETTINGS:
            spi_led_on();
            dma_spi_lc.state = DMA_SPI_LC_WRITING_INSTRUCTION_2; //todo,
            break;
        case DMA_SPI_LC_WRITING_INSTRUCTION_2:
            dma_spi_lc.state = DMA_SPI_LC_IDLE; //todo,
            break;
        case DMA_SPI_LC_WRITING_INSTRUCTION_3:
            dma_spi_lc.state = DMA_SPI_LC_IDLE; //todo,
            break;
        case DMA_SPI_LC_READING_DEVICES:
            dma_spi_lc.state = DMA_SPI_LC_WAITING_FOR_READOUT;
            circular_buffer[circular_buffer_index].DATA[0] = dma_spi_lc_rx_buffer[1];
            circular_buffer[circular_buffer_index].DATA[1] = dma_spi_lc_rx_buffer[2];
            circular_buffer[circular_buffer_index].DATA[2] = dma_spi_lc_rx_buffer[3];
            circular_buffer[circular_buffer_index].STATUS  = dma_spi_lc_rx_buffer[4];
            circular_buffer_index++;
            if(circular_buffer_index >= CIRCULAR_BUFFER_SIZE){
                circular_buffer_index = 0;
                circular_buffer_ready = 1;
            }
            IEC1bits.CNIE = 1;// re-enable the read interrupt after communication is done
            break;
        default:
            dma_spi_lc.state = DMA_SPI_LC_IDLE; //todo,
            break;
    }
    //gpio_set(dma_spi_lc.spi_mosi);//Idle high
    IFS2bits.DMA3IF = 0;//clear the interrupt flag
}

/**
 * Interrupt when the DMA finished its writing of all the bytes
*/
void __attribute__((__interrupt__ , no_auto_psv)) _DMA4Interrupt(){
    //clear the interruption flag
    //DMA4CONbits.CHEN  = 0;
    //dma_spi_lc.state = DMA_SPI_LC_IDLE;
    //dma_spi_lc_stop();
    IFS2bits.DMA4IF = 0;
}

/**
 * Interrupt when the SPI 2 finished writing and reading a byte
*/
void __attribute__((__interrupt__, no_auto_psv)) _SPI2Interrupt(void)
{
    //SPI2STATbits.SPIROV = 0;
    IFS2bits.SPI2IF = 0; // Clear the SPI1 Interrupt Flag
    //SPI1BUF=0;      // send next byte, not necassary if NULLW set
}

void __attribute__((__interrupt__ , no_auto_psv)) _CNInterrupt(){
    if(dma_spi_lc.state == DMA_SPI_LC_WAITING_FOR_READOUT){
        if(gpio_read(dma_spi_lc.spi_miso) == 0){
            IEC1bits.CNIE = 0;// disable this interrupt during communication
            start_reading = 1;
        }
    }
    IFS1bits.CNIF = 0;
}

int lc_get_torque(load_cell * e){
	return e->torque;
}

lc_error_flags lc_get_error(load_cell * e){
	return e->flags;
}

void lc_load_persistent_sbcp_settings(){

}
#endif