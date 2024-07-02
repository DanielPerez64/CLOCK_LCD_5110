/*
 * SPI.c
 *
 *  Created on: 30 jun. 2024
 *      Author: emms1
 */
#include "SPI.h"
#include "fsl_device_registers.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_dspi.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

static volatile bool g_transferCompleted = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

void SPI_Init(void)
{
	BOARD_InitBootPins();
    BOARD_InitBootClocks();
   // BOARD_InitDebugConsole();

    dspi_master_config_t masterConfig;
    uint32_t srcClock_Hz;

    /* Master config */
    masterConfig.whichCtar                                = kDSPI_Ctar0;
    masterConfig.ctarConfig.baudRate                      = SPI_BAUDRATE;
    masterConfig.ctarConfig.bitsPerFrame                  = 8U;
    masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
    masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
    masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
    masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / SPI_BAUDRATE;
    masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / SPI_BAUDRATE;
    masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / SPI_BAUDRATE;

    masterConfig.whichPcs           = SPI_PCS_FOR_INIT;
    masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

    masterConfig.enableContinuousSCK        = false;
    masterConfig.enableRxFifoOverWrite      = false;
    masterConfig.enableModifiedTimingFormat = false;
    masterConfig.samplePoint                = kDSPI_SckToSin0Clock;

    srcClock_Hz = SPI_CLK_FREQ;
    DSPI_MasterInit(SPI_BASEADDR, &masterConfig, srcClock_Hz);

   // DSPI_MasterTransferCreateHandle(SPI_BASEADDR, &g_dspiHandle, NULL, NULL);
}

void SPI_SendData(uint8_t *txData, uint32_t dataSize)
{
	//volatile uint32_t g_systickCounter = 20U;
    dspi_transfer_t masterXfer;

    masterXfer.txData      = txData;
    masterXfer.rxData      = NULL;
    masterXfer.dataSize    = dataSize;
    masterXfer.configFlags = kDSPI_MasterCtar0 | SPI_PCS_FOR_TRANSFER | kDSPI_MasterPcsContinuous;

    DSPI_MasterTransferBlocking(SPI_BASEADDR, &masterXfer);

    if (SysTick_Config(SystemCoreClock / 1000U))
           {
               while (1)
               {
               }
           }
}

void SPI_Deinit(void)
{
    DSPI_Deinit(SPI_BASEADDR);
}
