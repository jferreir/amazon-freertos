/**
 * @file xmc1_gpio.c
 * @date 2019-02-19
 *
 * @cond
 *****************************************************************************
 * XMClib v2.2.0 - XMC Peripheral Driver Library 
 *
 * Copyright (c) 2015-2019, Infineon Technologies AG
 * All rights reserved.                        
 *                                             
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *                                                                              
 * To improve the quality of the software, users are encouraged to share 
 * modifications, enhancements or bug fixes with Infineon Technologies AG 
 * at XMCSupport@infineon.com.
 *****************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-02-20:
 *     - Initial draft <br>
 *      
 * 2015-06-20:
 *     - Removed version macros and declaration of GetDriverVersion API
 *
 * 2017-09-15:
 *     - Fix side effects on output level when programming a pin as input after the same pin in another port has been configured as output
 * 
 * 2019-02-19:
 *     - Fix initialization of initial output level in case pin is an analog pin and configured as push pull or open drain
 *
 * @endcond
 *
 */

#include "xmc_gpio.h"

#if UC_FAMILY == XMC1

/*******************************************************************************
 * MACROS
 *******************************************************************************/

#define PORT_PHCR_Msk             PORT0_PHCR0_PH0_Msk
#define PORT_PHCR_Size            PORT0_PHCR0_PH0_Msk
#define PORT_HWSEL_Msk            PORT0_HWSEL_HW0_Msk
#define XMC_GPIO_MODE_OE          XMC_GPIO_MODE_OUTPUT_PUSH_PULL

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

void XMC_GPIO_Init(XMC_GPIO_PORT_t *const port, const uint8_t pin, const XMC_GPIO_CONFIG_t *const config)
{
  XMC_ASSERT("XMC_GPIO_Init: Invalid port", XMC_GPIO_CHECK_PORT(port));
  XMC_ASSERT("XMC_GPIO_Init: Invalid mode", XMC_GPIO_IsModeValid(config->mode));
  XMC_ASSERT("XMC_GPIO_Init: Invalid input hysteresis", XMC_GPIO_CHECK_INPUT_HYSTERESIS(config->input_hysteresis));
  
  /* Switch to input */
  port->IOCR[pin >> 2U] &= ~(uint32_t)((uint32_t)PORT_IOCR_PC_Msk << (PORT_IOCR_PC_Size * (pin & 0x3U)));

  /* HW port control is disabled */
  port->HWSEL &= ~(uint32_t)((uint32_t)PORT_HWSEL_Msk << ((uint32_t)pin << 1U));

  /* Set input hysteresis */
  port->PHCR[(uint32_t)pin >> 3U] &= ~(uint32_t)((uint32_t)PORT_PHCR_Msk << ((uint32_t)PORT_PHCR_Size * ((uint32_t)pin & 0x7U)));
  port->PHCR[(uint32_t)pin >> 3U] |= (uint32_t)config->input_hysteresis << ((uint32_t)PORT_PHCR_Size * ((uint32_t)pin & 0x7U));
    
  /* Enable digital input */
  if (XMC_GPIO_CHECK_ANALOG_PORT(port))
  {    
    port->PDISC &= ~(uint32_t)((uint32_t)0x1U << pin);
  }

  if ((config->mode & XMC_GPIO_MODE_OE) != 0)
  {
    /* If output is enabled */

    /* Set output level */
    port->OMR = (uint32_t)config->output_level << pin;
  }
  
  /* Set mode */
  port->IOCR[pin >> 2U] |= (uint32_t)config->mode << (PORT_IOCR_PC_Size * (pin & 0x3U));
}

void XMC_GPIO_SetInputHysteresis(XMC_GPIO_PORT_t *const port, 
                                 const uint8_t pin, 
                                 const XMC_GPIO_INPUT_HYSTERESIS_t hysteresis)
{
  XMC_ASSERT("XMC_GPIO_SetInputHysteresis: Invalid port", XMC_GPIO_CHECK_PORT(port));
  XMC_ASSERT("XMC_GPIO_SetInputHysteresis: Invalid input hysteresis", XMC_GPIO_CHECK_INPUT_HYSTERESIS(hysteresis));

  port->PHCR[(uint32_t)pin >> 3U] &= ~(uint32_t)((uint32_t)PORT_PHCR_Msk << ((uint32_t)PORT_PHCR_Size * ((uint32_t)pin & 0x7U)));
  port->PHCR[(uint32_t)pin >> 3U] |= (uint32_t)hysteresis << ((uint32_t)PORT_PHCR_Size * ((uint32_t)pin & 0x7U));
}

#endif /* UC_FAMILY == XMC1 */
