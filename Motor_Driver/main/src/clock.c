#include "../include/config.h"
#include PICINCLUDE
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
_FWDT(FWDTEN_OFF);
/* Disable JTAG */
_FICD(JTAGEN_OFF & ICS_PGD2);

void clock_init(){
    PLLFBD = 76;
    CLKDIVbits.PLLPRE = 2;
    CLKDIVbits.PLLPOST = 2;
}