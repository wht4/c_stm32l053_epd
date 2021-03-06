#ifndef SPI_H_
#define SPI_H_
/******************************************************************************/
/** \file       spi1.h
 *******************************************************************************
 *
 *  \brief      Driver for stm32l053 spi1
 *
 *  \author     wht4
 *
 ******************************************************************************/
/*
 *  function    .
 *
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****** Header-Files **********************************************************/
#include <stdint.h>

#include "stm32l0xx.h"
#include "gpio.h"

/****** Macros ****************************************************************/

/****** Data types ************************************************************/

/****** Function prototypes ****************************************************/
typedef void (*pfSpiCSHandler)(GpioState_t tGpioState);

/****** Data ******************************************************************/

/****** Implementation ********************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* SPI_H_ */
