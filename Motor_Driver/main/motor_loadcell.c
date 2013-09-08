#include "p33Exxxx.h"
#include "motor_loadcell.h"
#include "motor_state.h"
loadcell_data loadcell_state;
#ifdef ENABLE_LOADCELLS
loadcell_data loadcell_state;

return_value_t loadcell_init()
{
    unsigned i;
    loadcell_state.init_return = RET_OK;
    for(i=0;i<4;++i)
        loadcell_state.values[i] = 0;
    return loadcell_state.init_return;
}

typedef struct DMA_SPI_LC_read_value{
    unsigned char DATA[3];
    unsigned char STATUS;
} DMA_SPI_LC_read_value;

#define CIRCULAR_BUFFER_SIZE 3
volatile unsigned char circular_buffer_ready = 0;
volatile unsigned char circular_buffer_index = 0;
volatile DMA_SPI_LC_read_value circular_buffer[CIRCULAR_BUFFER_SIZE];

unsigned char dma_spi_lc_tx_buffer[16] __attribute__((space(dma)));

volatile unsigned char dma_spi_lc_rx_buffer[16] __attribute__((space(dma)));


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

    //Peripheral Pin Select

    //PPSUnLock;
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    PPSOutput(0, OUT_PIN_PPS_RP25); // no output on rp5
    IN_FN_PPS_SDI2 = 0;// no input on rp2
    IN_FN_PPS_SCK2 = 0;// no input on rp5
    IN_FN_PPS_SS2 = 0;// no input on rp23
    OUT_PIN_PPS_RP2 = 0;
    OUT_PIN_PPS_RP5 = 0;
    OUT_PIN_PPS_RP23 = 0;
    OUT_PIN_PPS_RP24 = 0;
    OUT_PIN_PPS_RP25 = 0;
    PPSOutput(OUT_FN_PPS_SDO2, OUT_PIN_PPS_RP23); // MOSI to rp23
    PPSOutput(OUT_FN_PPS_SS2, OUT_PIN_PPS_RP2); // chip select to rp2
    PPSOutput(OUT_FN_PPS_SCK2, OUT_PIN_PPS_RP5); // clock out to rp5
    PPSInput(PPS_SDI2, PPS_RP25);// MISO to rp25
    //PPSLock;
    //__builtin_write_OSCCONL(OSCCON | 0x40);

    dma_spi_lc.spi_mosi = gpio_create(GPIO_PORT_C,GPIO_PIN_7,GPIO_OUTPUT);
    gpio_clear(dma_spi_lc.spi_mosi);

    dma_spi_lc.spi_miso = gpio_create(GPIO_PORT_C,GPIO_PIN_9,GPIO_INPUT);
    gpio_set(dma_spi_lc.spi_miso);

    dma_spi_lc.spi_clk = gpio_create(GPIO_PORT_B,GPIO_PIN_5,GPIO_OUTPUT);
    gpio_set(dma_spi_lc.spi_clk);

    dma_spi_lc.spi_sync = gpio_create(GPIO_PORT_C,GPIO_PIN_8,GPIO_OUTPUT);
    gpio_set(dma_spi_lc.spi_sync);

    dma_spi_lc.spi_cs = gpio_create(GPIO_PORT_B,GPIO_PIN_2,GPIO_OUTPUT);
    gpio_set(dma_spi_lc.spi_cs);

    dma_spi_lc.state  = DMA_SPI_LC_IDLE;

    /************************************
     SPI2-MODULE
     ************************************/

    SPI2STATbits.SPIEN  = 0;     //Disable SPI 2 module during configuration
    //SPI 1 is for magentic encoders :
    IEC2bits.SPI2IE     = 0; //disable interrupt. This is needed because we use DMA
    IFS2bits.SPI2IF     = 0; //clear the interrupt flag.
    IPC8bits.SPI2IP     = 0b000;
    SPI2CON1bits.MSTEN  = 1; //enable master mode
    SPI2STATbits.SPIROV = 0; // clear overflow flag

    SPI2CON1bits.DISSCK = 0; //Use the clock
    SPI2CON1bits.DISSDO = 0; //Disable data output. This is not needed by the application, no pin are routed
    SPI2CON1bits.MODE16 = 0; //Transmit bytes. Rx buffer is in byte, but we don't care because we are transmitting an even number of byte

    SPI2CON1bits.CKE    = 0; //data valid on rising edge
    SPI2CON1bits.CKP    = 1; //clock idle state is at high level
    SPI2CON1bits.SMP    = 0; //0=data is sampled at middle of clock time

    SPI2CON1bits.SSEN   = 0; //disable chip select bit (we do this ourselves)
    SPI2CON2bits.FRMEN  = 0;     //Frame support

    //Choose a clock frequency of 625 kHz, max accepted by AS5045 is 1Mhz
    //TODO: set frequency
    SPI2CON1bits.SPRE   = 0b000; //Select a secondary prescaler of 1:1
    SPI2CON1bits.PPRE   = 0b10 ; //select a primary prescaler of 64:1

    IEC2bits.SPI2IE     = 0;    //enable interrupt.
    SPI2STATbits.SPIEN  = 1;     //Enable SPI 2 module

    /************************************
     DMA3-MODULE
     ************************************/

    IEC2bits.DMA3IE = 0;
    IFS2bits.DMA3IF = 0;

    IPC9bits.DMA3IP = 0b001; //low priority, but needs to be higher than DMA4IP


    DMA3CONbits.CHEN  = 0;
    DMA3CONbits.SIZE  = 1;
    DMA3CONbits.DIR   = 0;//read, don't send
    DMA3CONbits.HALF  = 0;

    DMA3CONbits.NULLW = 0;

    DMA3CONbits.AMODE = 0b00;// Register indirect with posincrement
    DMA3CONbits.MODE  = 0b00;// continuous, No Ping Pong

    DMA3STA = __builtin_dmaoffset(dma_spi_lc_rx_buffer);

    DMA3PAD = (volatile unsigned int) & SPI2BUF;

    DMA3REQbits.IRQSEL = 0b0100001; //SPI2
    DMA3CNT = 0;

    IEC2bits.DMA3IE = 1;

    /************************************
     DMA4-MODULE
     ************************************/

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