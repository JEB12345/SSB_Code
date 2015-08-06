/* 
 * File:   sensor_spi2.c
 * Author: jonathan
 *
 * Created on June 8, 2015, 4:39 PM
 */

#include "sensor_spi2.h"
#include <stdio.h>
#include <stdlib.h>
#include <spi.h>
#include <dma.h>
#include <xc.h>

/** This contains the parameters to be configured in the SPIxCON1 register
 * TODO: !!!!!! NEED TO CHECK IF THESE SETTINGS ARE CORRECT !!!!!!!!
 * DWM1000 SPI mode default: POL=0, PHA=0
 * "Data is sampled on the rising (first) edge of the clock and launched on the falling (second) edge."
 * This seems to correspond to CKP=0, CKE=1, SMP=0
 *
 * Slow Rate:
 * Primary Prescaler = 4, Secondary Prescaler = 7, 2.5MHz = (70,000,000) / (4 * 7)
 *
 * Fast Rate:
 * Primary Prescaler = 1, Secondary Prescaler = 5, 14MHz = (70,000,000) / (1 * 5)
 */
unsigned int config1slow = ENABLE_SCK_PIN &         // Internal Serial Clock is Enabled
                            ENABLE_SDO_PIN &        // SDO2 pin is controlled by the module
                            SPI_MODE16_OFF &        // Communication is 0=8-bits, 1=16bits wide
                            SPI_SMP_OFF &           // Input Data is Sampled at the Middle of Data Output Time
                            SPI_CKE_ON &            // Transmit happens from active clock state to idle clock state
                            SLAVE_ENABLE_OFF &      // Slave Select Disabled
                            CLK_POL_ACTIVE_HIGH &   // Idle state for clock is low, active is high
                            MASTER_ENABLE_ON &      // Master Mode
                            SEC_PRESCAL_4_1 &
                            PRI_PRESCAL_16_1         // SPI CLK at 2.5MHz
                            ;
unsigned int config1fast = ENABLE_SCK_PIN &         // Internal Serial Clock is Enabled
                            ENABLE_SDO_PIN &        // SDO2 pin is controlled by the module
                            SPI_MODE16_OFF &        // Communication is OFF=8-bits, ON=16bits wide
                            SPI_SMP_OFF &           // Input Data is Sampled at the Middle of Data Output Time
                            SPI_CKE_ON &            // Transmit happens from active clock state to idle clock state
                            SLAVE_ENABLE_OFF &      // Slave Select Disable
                            CLK_POL_ACTIVE_HIGH &   // Idle state for clock is low, active is high
                            MASTER_ENABLE_ON &      // Master Mode
                            SEC_PRESCAL_5_1 & //5
                            PRI_PRESCAL_1_1  //1       // // SPI CLK at 14MHz
                            ;

// This contains the parameters to be configured in the SPIxCON2 register
unsigned int config2 = FRAME_ENABLE_OFF &           // Frame SPI support Disable
                        FIFO_BUFFER_DISABLE         // FIFO buffer disabled
;

// This contains the parameters to be configured in the SPIxSTAT register
unsigned int config3 = SPI_ENABLE &                 // Enable module
                        SPI_IDLE_CON &              // Continue module operation in idle mode
                        SPI_RX_OVFLOW_CLR           // Clear receive overflow bit
;

/** Configure and Init SPI 2 module for slow mode
 */
void config_spi2_slow()
{
    CloseSPI2();
    OpenSPI2(config1slow, config2, config3);
    EnableIntSPI2;
}

/** Configure and Init SPI 2 module for fast mode
 */
void config_spi2_fast()
{
    CloseSPI2();
    OpenSPI2(config1fast, config2, config3);
    EnableIntSPI2;
}

void __attribute__((__interrupt__, no_auto_psv)) _SPI2Interrupt(void)
{
    SPI2STATbits.SPIROV = 0; // Clear SPI overflow bit
    IFS2bits.SPI2EIF = 0; // Clear SPI1 Fault Interrupt Flag Status bit
    IFS2bits.SPI2IF = 0; // Clear the interrupt Flag
}
