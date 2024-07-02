/*
 * SPI.h
 *
 *  Created on: 30 jun. 2024
 *      Author: emms1
 */

#ifndef SPI_H_
#define SPI_H_


#include "fsl_dspi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SPI_BASEADDR         SPI0
#define SPI_CLK_SRC          DSPI0_CLK_SRC
#define SPI_CLK_FREQ         CLOCK_GetFreq(DSPI0_CLK_SRC)
#define SPI_PCS_FOR_INIT     kDSPI_Pcs0
#define SPI_PCS_FOR_TRANSFER kDSPI_MasterPcs0

#define SPI_TRANSFER_SIZE    64U     /*! Transfer dataSize */
#define SPI_BAUDRATE         500000U /*! Transfer baudrate - 500k */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void SPI_Init(void);
void SPI_SendData(uint8_t *txData, uint32_t dataSize);
void SPI_Deinit(void);

#endif /* SPI_H_ */
