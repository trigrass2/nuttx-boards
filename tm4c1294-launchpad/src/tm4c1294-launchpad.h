/************************************************************************************
 * configs/tm4c1294-launchpad/src/ek-tm4c1294xl.h
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __CONFIGS_TM4C1294_LAUNCHPAD_TM4C1294_LAUNCHPAD_H
#define __CONFIGS_TM4C1294_LAUNCHPAD_TM4C1294_LAUNCHPAD_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include "chip.h"
#include "tiva_gpio.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Configuration ********************************************************************/

/* How many SSI modules does this chip support? */

#if TIVA_NSSI < 1
#  undef CONFIG_TIVA_SSI0
#  undef CONFIG_TIVA_SSI0
#elif TIVA_NSSI < 2
#  undef CONFIG_TIVA_SSI0
#endif

/* LED definitions ******************************************************************/
/* The EK-TM4C1294XL has a four green LEDs.
 *
 *   --- ------------
 *   Pin Pin Function
 *   --- ------------
 *   PN1 Green LED D1
 *   PN0 Green LED D2
 *   PF4 Green LED D3
 *   PF0 Green LED D4
 *   --- ------------
 *
 * A high output illuminates the LED.
 */

#define GPIO_LED_D1   (GPIO_FUNC_OUTPUT | GPIO_VALUE_ZERO | GPIO_PORTN | GPIO_PIN_1)
#define GPIO_LED_D2   (GPIO_FUNC_OUTPUT | GPIO_VALUE_ZERO | GPIO_PORTN | GPIO_PIN_0)
#define GPIO_LED_D3   (GPIO_FUNC_OUTPUT | GPIO_VALUE_ZERO | GPIO_PORTF | GPIO_PIN_4)
#define GPIO_LED_D4   (GPIO_FUNC_OUTPUT | GPIO_VALUE_ZERO | GPIO_PORTF | GPIO_PIN_0)

/* Button definitions ***************************************************************/
/* There are four push buttons on the board. Two of them are user controllable.
 * The others are RESET and WAKE
 *
 *   --- ------------
 *   Pin Pin Function
 *   --- ------------
 *   PJ0 USR_SW1
 *   PJ1 USR_SW2
 *   --- ------------
 */
#define GPIO_SW1   (GPIO_FUNC_INPUT | GPIO_PORTJ | GPIO_PIN_0)
#define GPIO_SW2   (GPIO_FUNC_INPUT | GPIO_PORTJ | GPIO_PIN_1)

/* SPI Chip selects ****************************************************************/
/*   SSI0: PA3 is used for SSI0 chip select to the second booster pack (No pull-
*          ups)
 *   SSI3: PH4 selects the SD card and PQ1 selects the on-board SPI flash.  Both
 *         pulled up on board.
 */

#define GPIO_BSTR2_CS (GPIO_FUNC_OUTPUT | GPIO_PADTYPE_STDWPU | GPIO_STRENGTH_4MA | \
                       GPIO_VALUE_ONE | GPIO_PORTA | GPIO_PIN_3)
#define GPIO_FLASH_CS (GPIO_FUNC_OUTPUT | GPIO_PADTYPE_STD | GPIO_STRENGTH_4MA | \
                       GPIO_VALUE_ONE | GPIO_PORTH | GPIO_PIN_4)
#define GPIO_SD_CS    (GPIO_FUNC_OUTPUT | GPIO_PADTYPE_STD | GPIO_STRENGTH_4MA | \
                       GPIO_VALUE_ONE | GPIO_PORTH | GPIO_PIN_4)

/* I2C *****************************************************************************/
/*   I2C3: PG4-5 are provide to the BoostPack 1 interface
 *   I2C7: PA4-5 are provide to the BoostPack 2 interface
 *   I2C6: PB6-7 are used for I2C to the TMP100 and the EM connector.
 *         J18 and J20 must be closed to connect the TMP100.
 *         I2C address is 0x4A
 */

#define TMP100_I2CBUS  6
#define TMP100_I2CADDR 0x4a

/* Speaker outputs *****************************************************************/
/* PB2/PD4 are used for the speaker output */

/* Touchscreen *********************************************************************/
/* PE7/PP7/PT2-3 are used for the touch screen */

/************************************************************************************
 * Public Functions
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Name: tm4c_ssiinitialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the EK-TM4C1294XL.
 *
 ************************************************************************************/

void weak_function tm4c_ssiinitialize(void);

/****************************************************************************
 * Name: tm4c_ledinit
 *
 * Description:
 *   Called to initialize the on-board LEDs.
 *
 ****************************************************************************/

#ifdef CONFIG_ARCH_LEDS
void tm4c_ledinit(void);
#endif

/****************************************************************************
 * Name: tm4c_bringup
 *
 * Description:
 *   Bring up board features
 *
 ****************************************************************************/

int tm4c_bringup(void);

/****************************************************************************
 * Name: tiva_timer_initialize
 *
 * Description:
 *   Configure the timer driver
 *
 ****************************************************************************/

#ifdef CONFIG_TM4C1294_LAUNCHPAD_TIMER
int tiva_timer_initialize(void);
#endif

#endif /* __ASSEMBLY__ */
#endif /* __CONFIGS_TM4C1294_LAUNCHPAD_TM4C1294_LAUNCHPAD_H */