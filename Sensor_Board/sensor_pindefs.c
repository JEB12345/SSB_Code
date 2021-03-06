#include "p33Exxxx.h"
#include "sensor_state.h"
#include "sensor_pindefs.h"
#include "MPU60xx/IMU.h"
#include <pps.h>

return_value_t
pin_init ()
{
  //Set all pins to input
  TRISA = 0xFFFF;
  TRISB = 0xFFFF;
  TRISC = 0xFFFF;
  TRISD = 0xFFFF;
  TRISE = 0xFFFF;
  TRISF = 0xFFFF;
  TRISG = 0xFFFF;

  //Configure all analog ports as digital I/O
  ANSELA = 0x0;
  ANSELB = 0x0;
  ANSELC = 0x0;
  ANSELE = 0x0;

  //peripheral pin select
  RPINR7bits.IC1R = 47; //RB15
  RPINR7bits.IC2R = 119; //RG7
  RPINR8bits.IC3R = 121; //RB9

  /*
   * Watchdog
   */
  PTGCONbits.PTGWDT = 0b000; //watchdog disabled

  /*
   * CAN
   */
  TRISCbits.TRISC8 = 0; //TX = output
  _RP56R = 0b001110; //TX
  RPINR26bits.C1RXR = 55; //RX RP55
  //    IN_FN_PPS_C1RX = IN_PIN_PPS_RP36;
  //    OUT_PIN_PPS_RP35 = OUT_FN_PPS_C1TX;


  //RP36/35

  //IMU
  //configured in sensor_imu.c

  //LOAD CELL
  TRISCbits.TRISC6 = 0;
  _RP54R = 0;
  TRISBbits.TRISB0 = 0;
  RPINR8bits.IC4R = 25;
  TRISAbits.TRISA4 = 0;

  //RF
  RPINR1bits.INT2R = 94;
  TRISBbits.TRISB9 = 0;
  XBEE_nSSEL = 1;
  _RP41R = 0;
  TRISFbits.TRISF1 = 0;
  XBEE_SLEEP_RQ = 0;
  _RP97R = 0;
  TRISEbits.TRISE13 = 0;
  XBEE_nRESET = 1;
  _SDI2R = 40; // Map SPI2 DI to RP40
  _RP39R = 8; // Map SPI2 DO to RP39
  TRISBbits.TRISB7 = 0;

  //TRISCbits.TRISC9 = 0;
  _RP57R = 9; // Map SPI2 CLK to RP57
  CNPUEbits.CNPUE14 = 1; // XBEE_nATTN pull up

  //LEDs
  TRISGbits.TRISG6 = 0;
  _RP118R = 0;
  TRISGbits.TRISG8 = 0;
  _RP120R = 0;
  TRISAbits.TRISA0 = 0;
  TRISDbits.TRISD6 = 0;
  TRISDbits.TRISD5 = 0;
  TRISCbits.TRISC13 = 0;
  TRISDbits.TRISD8 = 0;

  //POWER MOSFETS
  TRISCbits.TRISC12 = 0;
  TRISCbits.TRISC15 = 0;
  TRISAbits.TRISA10 = 0;

  //UART 1
  _RP36R = 0b000001; //RB4 UART 1 tx
  RPINR18bits.U1RXR = 44; //RB12 uart 1 rx s

  //UART 2
  _RP35R = 0b000011; // RB3 UART 2 TX
  RPINR19bits.U2RXR = 43; // RB2 UART 2 RX

  //OLD BBB Power Toggle
  TRISBbits.TRISB13 = 1; //MUST BE SET TO INPUT!!
  PORTBbits.RB13 = 0; //MUST BE SET OT OFF!!
//  TRISBbits.TRISB13 = 0;
//  LATBbits.LATB13 = 1;

  //IMU Trigger
  CNENFbits.CNIEF0 = 1; // Enables RF0 as interrupt detection
  IFS1bits.CNIF = 0; // Clears the Interrupt flag
  IEC1bits.CNIE = 1; // Enables CN interrupts

  //P6
#if RB14_IO==PIN_OUTPUT
  TRISBbits.TRISB14 = 0;
#endif
#if RG9_IO==PIN_OUTPUT
  TRISGbits.TRISG9 = 0;
#endif
#if RA11_IO==PIN_OUTPUT
  TRISAbits.TRISA11 = 0;
#endif
#if RA1_IO==PIN_OUTPUT
  TRISAbits.TRISA1 = 0;
#endif
#if RB2_IO==PIN_OUTPUT
  TRISBbits.TRISB2 = 0;
#endif
#if RB15_IO==PIN_OUTPUT
  TRISBbits.TRISB15 = 0;
#endif
#if RA12_IO==PIN_OUTPUT
  TRISAbits.TRISA12 = 0;
#endif
#if RG7_IO==PIN_OUTPUT
  TRISGbits.TRISG7 = 0;
#endif
#if RB1_IO==PIN_OUTPUT
  TRISBbits.TRISB1 = 0;
#endif
  _RP35R = 0;
#if RB3_IO==PIN_OUTPUT
  TRISBbits.TRISB3 = 0;
#endif

  //ANALOG PINS
  ANSELCbits.ANSC0 = 1;
  ANSELCbits.ANSC1 = 1;
  ANSELCbits.ANSC2 = 1;
  ANSELCbits.ANSC11 = 1;

  //P7
#if RE12_IO==PIN_OUTPUT
  TRISEbits.TRISE12 = 0;
#endif
#if RA8_IO==PIN_OUTPUT
  TRISAbits.TRISA8 = 0;
#endif
  _RP43R = 0;
#if RB11_IO==PIN_OUTPUT
  TRISBbits.TRISB11 = 0;
#endif
#if RE13_IO==PIN_OUTPUT
  TRISEbits.TRISE13 = 0;
#endif
#if RB4_IO==PIN_OUTPUT
  TRISBbits.TRISB4 = 0;
#endif
#if RC10_IO==PIN_OUTPUT
  TRISCbits.TRISC10 = 0;
#endif

  return RET_OK;
}
