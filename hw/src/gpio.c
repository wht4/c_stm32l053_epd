/******************************************************************************/
/** @file       gpio.c
 *******************************************************************************
 *
 *  @brief      General gpio handling for stm32l053
 *
 *  @author     wht4
 *
 *  @remark     Last modifications
 *                 \li V1.0, February 2016, wht4, initial release
 *
 ******************************************************************************/
/*
 *  functions  global:
 *              gpio_init
 *              gpio_setAF
 *  functions  local:
 *              .
 *
 ******************************************************************************/

/****** Header-Files **********************************************************/
#include <assert.h>
#include <stddef.h>

#include "gpio.h"

/****** Macros ****************************************************************/
#define IS_GPIO_BASE(ptGpioBase) \
	(((ptGpioBase) == GPIOA) || \
	 ((ptGpioBase) == GPIOB) || \
     ((ptGpioBase) == GPIOC) || \
     ((ptGpioBase) == GPIOD) || \
     ((ptGpioBase) == GPIOH) )

#define IS_GPIO_PIN(u32Pin) \
	((u32Pin < 0xffUL ) )

#define IS_GPIO_MODE(tGpioMode)              \
	(((tGpioMode) == GPIO_MODE_INPUT) ||     \
	 ((tGpioMode) == GPIO_MODE_OUTPUT) ||    \
	 ((tGpioMode) == GPIO_MODE_ALTERNATE) || \
     ((tGpioMode) == GPIO_MODE_ANALOG))

#define IS_GPIO_OUTPUT(tGpioOutput)              \
	(((tGpioOutput) == GPIO_OUTPUT_PUSH_PULL) || \
	 ((tGpioOutput) == GPIO_OUTPUT_OPEN_DRAIN))

#define IS_GPIO_SPEED(tGpioSpeed)             \
	(((tGpioSpeed) == GPIO_SPEED_VERY_LOW) || \
	 ((tGpioSpeed) == GPIO_SPEED_LOW) ||      \
	 ((tGpioSpeed) == GPIO_SPEED_MEDIUM) ||   \
     ((tGpioSpeed) == GPIO_SPEED_HIGH))

#define IS_GPIO_PULL(tGpioPull)        \
	(((tGpioPull) == GPIO_PULL_NONE) || \
	 ((tGpioPull) == GPIO_PULL_UP) ||  \
	 ((tGpioPull) == GPIO_PULL_DOWN))

#define IS_GPIO_AF(tGpioAF)          \
	(((tGpioAF) == GPIO_AF_0) ||     \
	 ((tGpioAF) == GPIO_AF_1) ||     \
	 ((tGpioAF) == GPIO_AF_2) ||     \
	 ((tGpioAF) == GPIO_AF_3) ||     \
	 ((tGpioAF) == GPIO_AF_4) ||     \
	 ((tGpioAF) == GPIO_AF_5) ||     \
	 ((tGpioAF) == GPIO_AF_6) ||     \
	 ((tGpioAF) == GPIO_AF_6))

/****** Data types ************************************************************/

/****** Function prototypes ****************************************************/

/****** Data ******************************************************************/

/****** Implementation ********************************************************/

/*******************************************************************************
 *  function :    gpio_init
 ******************************************************************************/
void
gpio_init (GPIO_TypeDef * ptGpioBase, uint32_t u32Pin, GpioInit_t * ptGpioInit) {

    assert(IS_GPIO_BASE(ptGpioBase));
    assert(IS_GPIO_PIN(u32Pin));
    assert(IS_GPIO_MODE(ptGpioInit->tGpioMode));
    assert(IS_GPIO_OUTPUT(ptGpioInit->tGpioOutput));
    assert(IS_GPIO_SPEED(ptGpioInit->tGpioSpeed));
    assert(IS_GPIO_PULL(ptGpioInit->tGpioPull));

    if((ptGpioBase != NULL) && (ptGpioInit != NULL)) {
        /* set the mode register of the desired gpio */
        ptGpioBase->MODER &= ~(0x03UL << (u32Pin << 1UL));
        ptGpioBase->MODER |= ((0x03UL & ptGpioInit->tGpioMode) << (u32Pin << 1UL));

        /* set the gpio output type register */
        if (ptGpioInit->tGpioOutput == GPIO_OUTPUT_PUSH_PULL) {

            ptGpioBase->OTYPER &= ~(0x01UL << u32Pin);

        } else {

            ptGpioBase->OTYPER |= (0x01UL << u32Pin);
        }

        /* set the output speed register */
        ptGpioBase->OSPEEDR &= ~(0x03UL << (u32Pin << 1UL));
        ptGpioBase->OSPEEDR |= ((0x03UL & ptGpioInit->tGpioSpeed) << (u32Pin << 1UL));

        /* set port pull-up/pull-down register */
        ptGpioBase->PUPDR &= ~(0x03UL << (u32Pin << 2UL));
        ptGpioBase->PUPDR |= ((0x03UL & ptGpioInit->tGpioPull) << (u32Pin << 1UL));
    }
}

/*******************************************************************************
 *  function :    gpio_setAF
 ******************************************************************************/
void
gpio_setAF(GPIO_TypeDef * ptGpioBase, uint32_t u32Pin, GpioAF_t tGpioAF) {

    assert(IS_GPIO_BASE(ptGpioBase));
    assert(IS_GPIO_PIN(u32Pin));
    assert(IS_GPIO_AF(tGpioAF));

    if (ptGpioBase != NULL) {

        if(u32Pin < 8) {

            ptGpioBase->AFR[0] |= (tGpioAF << (u32Pin << 2));

        } else {

            ptGpioBase->AFR[1] |= (tGpioAF << ((u32Pin - 8) << 2));
        }
    }
}
