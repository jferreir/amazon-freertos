/**
 * @file xmc_fce.c
 * @date 2019-12-16
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
 *     - Initial <br>
 *      
 * 2015-06-20:
 *     - Removed GetDriverVersion API
 *
 * 2017-12-14:
 *     - XMC_FCE_CalculateCRC8()
 *       Ensure 32bit access to IR register
 *     - XMC_FCE_CalculateCRC16()
 *       Ensure 32bit access to IR register
 *       Remove restriction on data source allignment
 *     - XMC_FCE_CalculateCRC32()
 *       Ensure 32bit access to IR register
 *       Remove restriction on data source allignment
 *
 * 2019-03-30:
 *     - Added XMC_FCE_CalculateCRC16Ex() and XMC_FCE_CalculateCRC32Ex()
 * 
 * 2019-12-16:
 *     - Fix including files following the convention: angle brackets are used for standard includes and double quotes for everything else.
 *
 * @endcond 
 *
 */

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "xmc_fce.h"

#if defined (FCE)
#include "xmc_scu.h"

/*******************************************************************************
 * API IMPLEMENTATION
 *********************************************************************************************************************/

/*
 * Initialize the FCE peripheral:
 * Update FCE configuration and initialize seed value
 */
XMC_FCE_STATUS_t XMC_FCE_Init(const XMC_FCE_t *const engine)
{
  engine->kernel_ptr->CFG = engine->fce_cfg_update.regval;
  engine->kernel_ptr->CRC = engine->seedvalue;
  
  return XMC_FCE_STATUS_OK;
}

/* Disable FCE */
void XMC_FCE_Disable(void)
{
  FCE->CLC |= (uint32_t)FCE_CLC_DISR_Msk;
  
  XMC_SCU_RESET_AssertPeripheralReset(XMC_SCU_PERIPHERAL_RESET_FCE);

#if defined(CLOCK_GATING_SUPPORTED)
  XMC_SCU_CLOCK_GatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_FCE);
#endif

}

/* Enable FCE */
void XMC_FCE_Enable(void)
{
#if defined(CLOCK_GATING_SUPPORTED)
  XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_FCE);
#endif

  XMC_SCU_RESET_DeassertPeripheralReset(XMC_SCU_PERIPHERAL_RESET_FCE);

  FCE->CLC &= (uint32_t)~FCE_CLC_DISR_Msk;
}

/* Calculate and return the SAE J1850 CRC8 checksum */
XMC_FCE_STATUS_t XMC_FCE_CalculateCRC8(const XMC_FCE_t *const engine,
                                       const uint8_t *data,
									   uint32_t length,
									   uint8_t *result)
{
  XMC_FCE_STATUS_t status = XMC_FCE_STATUS_OK;
	
  XMC_ASSERT("XMC_FCE_CalculateCRC8: Wrong FCE kernel used", (engine -> kernel_ptr == XMC_FCE_CRC8));

  if (length == 0UL)
  {
    status = XMC_FCE_STATUS_ERROR;
  }
  else
  {
    while (0UL != length)
    {
      engine->kernel_ptr->IR = (uint32_t)*data;
      data++;
      length -= 1U;
    }

    *result = (uint8_t)engine->kernel_ptr->CRC;
  }

  return status;
}

/* Calculate and return calculated CCITT CRC16 checksum */
XMC_FCE_STATUS_t XMC_FCE_CalculateCRC16(const XMC_FCE_t *const engine,
                                        const uint16_t *data,
										uint32_t length,
										uint16_t *result)
{
  XMC_FCE_STATUS_t status = XMC_FCE_STATUS_OK;
	
  XMC_ASSERT("XMC_FCE_CalculateCRC16: Wrong FCE kernel used", (engine -> kernel_ptr == XMC_FCE_CRC16));
  XMC_ASSERT("XMC_FCE_CalculateCRC16: Length field is empty", (length != 0));
  XMC_ASSERT("XMC_FCE_CalculateCRC16: Length is not aligned", ((length & 0x1U) == 0));

  /* Check length is a multiple of 2 */
  if ((length == 0) || ((length & 0x1U) != 0U))
  {
    status = XMC_FCE_STATUS_ERROR;
  }
  else
  {
    while (0UL != length)
    {
      engine->kernel_ptr->IR = (uint32_t)*data;
      data++;
      length -= 2U;
    }
	
    *result = (uint16_t)engine->kernel_ptr->CRC;
  }

  return status;
}

XMC_FCE_STATUS_t XMC_FCE_CalculateCRC16Ex(const XMC_FCE_t *const engine,
                                          const uint8_t *data,
										                      uint32_t length,
										                      uint16_t *const result)
{
  XMC_FCE_STATUS_t status = XMC_FCE_STATUS_OK;
	
  XMC_ASSERT("XMC_FCE_CalculateCRC16: Wrong FCE kernel used", (engine -> kernel_ptr == XMC_FCE_CRC16));
  XMC_ASSERT("XMC_FCE_CalculateCRC16: Length field is empty", (length != 0));
  XMC_ASSERT("XMC_FCE_CalculateCRC16: Length is not aligned", ((length & 0x1U) == 0));

  /* Check length is a multiple of 2 */
  if ((length == 0) || ((length & 0x1U) != 0U))
  {
    status = XMC_FCE_STATUS_ERROR;
  }
  else
  {
    const uint16_t *p = (const uint16_t *)data;
    while (0UL != length)
    {
      engine->kernel_ptr->IR = __REV16(*p);
      ++p;
      length -= 2U;
    }
	
    *result = (uint16_t)engine->kernel_ptr->CRC;
  }

  return status;
}

/* Calculate and return the IEEE 802.3 Ethernet CRC32 checksum */
XMC_FCE_STATUS_t XMC_FCE_CalculateCRC32(const XMC_FCE_t *const engine,
                                        const uint32_t *data,
										uint32_t length,
										uint32_t *result)
{
  XMC_FCE_STATUS_t status = XMC_FCE_STATUS_OK;
	
  XMC_ASSERT("XMC_FCE_CalculateCRC32: Wrong FCE kernel used", ((engine->kernel_ptr == XMC_FCE_CRC32_0) ||
                                                               (engine->kernel_ptr == XMC_FCE_CRC32_1)));
  XMC_ASSERT("XMC_FCE_CalculateCRC32: Length field is empty", (length != 0));
  XMC_ASSERT("XMC_FCE_CalculateCRC32: Length is not aligned", ((length & 0x3U) == 0));

  /* Check length is a multiple of 4 */
  if ((length == 0) || ((length & 0x3U) != 0U))
  {
    status = XMC_FCE_STATUS_ERROR;
  }
  else
  {
    while (0UL != length)
    {
      engine->kernel_ptr->IR = *data;
      data++;
      length -= 4U;
    }

    *result = engine->kernel_ptr->CRC;
  }
  
  return status;
}

/* Calculate and return the IEEE 802.3 Ethernet CRC32 checksum */
XMC_FCE_STATUS_t XMC_FCE_CalculateCRC32Ex(const XMC_FCE_t *const engine,
                                          const uint8_t *data,
										                      uint32_t length,
										                      uint32_t *const result)
{
  XMC_FCE_STATUS_t status = XMC_FCE_STATUS_OK;
	
  XMC_ASSERT("XMC_FCE_CalculateCRC32: Wrong FCE kernel used", ((engine->kernel_ptr == XMC_FCE_CRC32_0) ||
                                                               (engine->kernel_ptr == XMC_FCE_CRC32_1)));
  XMC_ASSERT("XMC_FCE_CalculateCRC32: Length field is empty", (length != 0));
  XMC_ASSERT("XMC_FCE_CalculateCRC32: Length is not aligned", ((length & 0x3U) == 0));

  /* Check length is a multiple of 4 */
  if ((length == 0) || ((length & 0x3U) != 0U))
  {
    status = XMC_FCE_STATUS_ERROR;
  }
  else
  {
    const uint32_t *p = (const uint32_t *)data;
    while (0UL != length)
    {
      engine->kernel_ptr->IR = __REV(*p);
      ++p;
      length -= 4U;
    }

    *result = engine->kernel_ptr->CRC;
  }
  
  return status;
}

/* Trigger mismatch in the CRC registers */
void XMC_FCE_TriggerMismatch(const XMC_FCE_t *const engine, XMC_FCE_CTR_TEST_t test)
{
  /* Create a 0 to 1 transition and clear to 0 once it is done */
  engine->kernel_ptr->CTR &= ~((uint32_t)test);
  engine->kernel_ptr->CTR |= (uint32_t)test;
  engine->kernel_ptr->CTR &= ~((uint32_t)test);
}

/* Change endianness of 16-bit input buffer */
void XMC_FCE_LittleEndian16bit(uint8_t* inbuffer, uint16_t* outbuffer, uint16_t length)
{
  uint16_t counter = 0U;
  uint16_t bytecounter = 0U;

  if ((length & 0x01U)  == 0)
  {
    for (counter = 0U; counter < (length >> 1); counter++)
    {
      outbuffer[counter] = 0U;
    }

    outbuffer[counter] = 0U;
    counter = 0U;

    while (length)
    {
      outbuffer[counter] = ((uint16_t)((uint16_t)inbuffer[bytecounter] << 8U) |
                            (inbuffer[bytecounter + 1U]));
      counter += 1U;
      bytecounter += 2U;
      length -= 2U;
    }
  }
}

/* Change endianness of 32-bit input buffer */
void XMC_FCE_LittleEndian32bit(uint8_t* inbuffer, uint32_t* outbuffer, uint16_t length)
{
  uint16_t counter = 0U;
  uint16_t bytecounter = 0U;
 
  if ((length & 0x03U) == 0)
  {
    for (counter = 0U; counter < (length >> 2U); counter++)
    {
      outbuffer[counter] = 0U;
    }

    outbuffer[counter] = 0U;
    counter = 0U;

    while (length)
    {
      outbuffer[counter] = ((uint32_t)inbuffer[bytecounter]      << 24U) |
                           ((uint32_t)inbuffer[bytecounter + 1U] << 16U) |
                           ((uint32_t)inbuffer[bytecounter + 2U] <<  8U) |
                           (inbuffer[bytecounter + 3U]);
      counter += 1U;
      bytecounter += 4U;
      length -= 4U;
    }
  }
}

#endif
