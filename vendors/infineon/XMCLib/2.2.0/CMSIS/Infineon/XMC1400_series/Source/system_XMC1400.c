/*********************************************************************************************************************
 * @file     system_XMC1400.c
 * @brief    Device specific initialization for the XMC1400-Series according to CMSIS
 * @version  V1.8
 * @date     03 Mar 2020
 *
 * @cond
 *********************************************************************************************************************
 * Copyright (c) 2015-2020, Infineon Technologies AG
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
 *********************************************************************************************************************
 *
 * *************************** Change history ********************************
 * V1.0, 03 Sep 2015, JFT : Initial version
 *                          MCLK = 48MHz, PCLK = 96MHz
 * V1.1, 09 Dec 2015, JFT : Enable prefetch unit
 * V1.2, 19 Jun 2017, Rely on cmsis_compiler.h instead of defining __WEAK
 *                    Added support for ARM Compiler 6 (armclang) 
 * V1.3, 20 Jun 2018, Fixed OSC_HP oscillator watchdog result detection in startup
 *                    Added wait time for RTC_XTAL oscillator startup time ~5s
 * V1.4, 29 Oct 2018, Fix variable location of SystemCoreClock for ARMCC compiler
 * V1.5, 20 Mar 2019, Fix clock initialization if external XTAL is used (clock watchdog issue, see errata SCU_CM.023)
 *                    Added DISABLE_WAIT_RTC_XTAL_OSC_STARTUP preprocessor guard:
 *                      The RTC_XTAL can be used as clock source for RTC or as reference for DCO1 calibration 
 *                      In both cases if no wait is done in the startup after enabling the RTC_XTAL oscillator,
 *                      the RTC_Enable() or the calibration will stall the MCU until the oscillator is stable (max. 5s according datasheet)
 *
 * V1.6, 04 June 2019, Sync. code of SystemCoreClockSetup() to XMC_SCU_CLOCK_Init() in xmc1_scu.c
 * V1.7, 02 Dec 2019, Fix including device header file following the convention: angle brackets are used for standard includes and double quotes for everything else.
 * V1.8, 03 Mar 2020, Fix seeting of ANAOSCHPCTRL accoring to OSC_CM.D001 in errata
 *
 * @endcond
 */

/*******************************************************************************
 * HEADER FILES
 *******************************************************************************/

#include "XMC1400.h"
#include "system_XMC1400.h"

/*******************************************************************************
 * MACROS
 *******************************************************************************/
#define DCO1_FREQUENCY (48000000U)

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*
// <h> Clock configuration
*/

/*
//    <o> External crystal frequency [Hz]
//       <8000000=> 8MHz
//       <12000000=> 12MHz
//       <16000000=> 16MHz
//       <20000000=> 20MHz
//    <i> Defines external crystal frequency
//    <i> Default: 20MHz
*/
#define OSCHP_FREQUENCY (20000000U)

/*
//    <o> DCLK clock source selection
//       <0=> Internal oscillator DCO1 (48MHz)
//       <1=> External crystal oscillator
//    <i> Default: Internal oscillator DCO1 (48MHz)
*/
#define DCLK_CLOCK_SRC 0
#define DCLK_CLOCK_SRC_DCO1 0
#define DCLK_CLOCK_SRC_EXT_XTAL 1

/*
//    <o> OSCHP external oscillator mode
//       <0=> Crystal mode
//       <1=> External clock direct input mode
//    <i> Default: Crystal mode
*/
#define OSCHP_MODE 0
#define OSCHP_MODE_XTAL 0
#define OSCHP_MODE_DIRECT 1

/*
//    <o> RTC clock source selection
//       <0=> Internal oscillator DCO2 (32768Hz)
//       <5=> External crystal oscillator
//    <i> Default: Internal oscillator DCO2 (32768Hz)
*/
#define RTC_CLOCK_SRC 0
#define RTC_CLOCK_SRC_DCO2 0
#define RTC_CLOCK_SRC_EXT_XTAL 5
/*
//    <o> PCLK clock source selection
//       <0=> MCLK
//       <1=> 2xMCLK
//    <i> Default: 2xMCLK
*/
#define PCLK_CLOCK_SRC 1
#define PCLK_CLOCK_SRC_MCLK 0
#define PCLK_CLOCK_SRC_2XMCLK 1

/*
//-------- <<< end of configuration section >>> ------------------
*/

/*******************************************************************************
 * GLOBAL VARIABLES
 *******************************************************************************/

#if defined ( __CC_ARM )
uint32_t SystemCoreClock __attribute__((at(0x20003FFC)));
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
uint32_t SystemCoreClock __attribute__((section(".bss.ARM.__at_0x20003FFC")));
#elif defined ( __ICCARM__ )
__no_init uint32_t SystemCoreClock;
#elif defined ( __GNUC__ )
uint32_t SystemCoreClock __attribute__((section(".no_init")));
#elif defined ( __TASKING__ )
uint32_t SystemCoreClock __at( 0x20003FFC );
#endif

/*******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************/
#if (DCLK_CLOCK_SRC != DCLK_CLOCK_SRC_DCO1) || ((RTC_CLOCK_SRC == RTC_CLOCK_SRC_EXT_XTAL) && (!defined(DISABLE_WAIT_RTC_XTAL_OSC_STARTUP)))
__STATIC_FORCEINLINE void delay(uint32_t cycles)
{
  while(--cycles > 0)
  {
    __NOP();
  }
}
#endif

/*******************************************************************************
 * API IMPLEMENTATION
 *******************************************************************************/

__WEAK void SystemInit(void)
{
  SystemCoreSetup();
  SystemCoreClockSetup();
}

__WEAK void SystemCoreSetup(void)
{
  /* Enable Prefetch unit */
  SCU_GENERAL->PFUCR &= ~SCU_GENERAL_PFUCR_PFUBYP_Msk;
}

__WEAK void SystemCoreClockSetup(void)
{
  /* Clock setup done during SSW using the CLOCK_VAL1 and CLOCK_VAL2 defined in vector table */

  /* disable bit protection */
  SCU_GENERAL->PASSWD = 0x000000C0UL;

#if DCLK_CLOCK_SRC != DCLK_CLOCK_SRC_DCO1

  /* OSC_CM.D001 Additions and corrections related to ANAOSCHPCTRL register */
  if (OSCHP_GetFrequency() <= 20000000U)
  {
    SCU_ANALOG->ANAOSCHPCTRL |= SCU_ANALOG_ANAOSCHPCTRL_HYSCTRL_Msk;
  }

  /* OSCHP source selection - OSC mode */
  SCU_ANALOG->ANAOSCHPCTRL = (SCU_ANALOG->ANAOSCHPCTRL & ~SCU_ANALOG_ANAOSCHPCTRL_MODE_Msk) |
                             (OSCHP_MODE << SCU_ANALOG_ANAOSCHPCTRL_MODE_Pos);

  do 
  {
    /* clear the status bit before restarting the detection. */
    SCU_INTERRUPT->SRCLR1 = SCU_INTERRUPT_SRCLR1_LOECI_Msk;

    /* According to errata SCU_CM.023, to reset the XOWD it is needed to disable/enable the watchdog, 
       keeping in between at least one DCO2 cycle */
    
    /* Disable XOWD */
    SCU_CLK->OSCCSR &= ~SCU_CLK_OSCCSR_XOWDEN_Msk;
      
    /* Clock domains synchronization, at least 1 DCO2 cycle */
    /* delay value calculation assuming worst case DCO1=48Mhz and 3cycles per delay iteration */
    delay(538);
      
    /* Enable XOWD */
    SCU_CLK->OSCCSR |= SCU_CLK_OSCCSR_XOWDEN_Msk | SCU_CLK_OSCCSR_XOWDRES_Msk;

    /* OSCCSR.XOWDRES bit will be automatically reset to 0 after XOWD is reset */
    while (SCU_CLK->OSCCSR & SCU_CLK_OSCCSR_XOWDRES_Msk);

    /* Wait a at least 5 DCO2 cycles for the update of the XTAL OWD result */
    /* delay value calculation assuming worst case DCO1=48Mhz and 3cycles per delay iteration */
    delay(2685);

  } while (SCU_INTERRUPT->SRRAW1 & SCU_INTERRUPT_SRRAW1_LOECI_Msk);

  /* DCLK source using OSC_HP */
  SCU_CLK->CLKCR1 |= SCU_CLK_CLKCR1_DCLKSEL_Msk;
  
#else
    
  /* DCLK source using DCO1 */
  SCU_CLK->CLKCR1 &= ~SCU_CLK_CLKCR1_DCLKSEL_Msk;
  
#endif    

#if RTC_CLOCK_SRC == RTC_CLOCK_SRC_EXT_XTAL
  /* Enable OSC_LP */
  SCU_ANALOG->ANAOSCLPCTRL &= ~SCU_ANALOG_ANAOSCLPCTRL_MODE_Msk;
#ifndef DISABLE_WAIT_RTC_XTAL_OSC_STARTUP  
  /* Wait oscillator startup time ~5s */
  delay(6500000);
#endif  
#endif  

  /* Update PCLK selection mux. */
  /* Fractional divider enabled, MCLK frequency equal DCO1 frequency or external crystal frequency */
  SCU_CLK->CLKCR = (1023UL <<SCU_CLK_CLKCR_CNTADJ_Pos) |
                    (RTC_CLOCK_SRC << SCU_CLK_CLKCR_RTCCLKSEL_Pos) |
                    (PCLK_CLOCK_SRC << SCU_CLK_CLKCR_PCLKSEL_Pos) |
                    0x100U; /* IDIV = 1 */

  /* enable bit protection */
  SCU_GENERAL->PASSWD = 0x000000C3UL;

  SystemCoreClockUpdate();
}

__WEAK void SystemCoreClockUpdate(void)
{
  static uint32_t IDIV, FDIV;

  IDIV = ((SCU_CLK->CLKCR) & SCU_CLK_CLKCR_IDIV_Msk) >> SCU_CLK_CLKCR_IDIV_Pos;

  if (IDIV != 0)
  {
    FDIV = ((SCU_CLK->CLKCR) & SCU_CLK_CLKCR_FDIV_Msk) >> SCU_CLK_CLKCR_FDIV_Pos;
    FDIV |= ((SCU_CLK->CLKCR1) & SCU_CLK_CLKCR1_FDIV_Msk) << 8;
    
    /* Fractional divider is enabled and used */
    if (((SCU_CLK->CLKCR1) & SCU_CLK_CLKCR1_DCLKSEL_Msk) == 0U)
    {
       SystemCoreClock = ((uint32_t)((DCO1_FREQUENCY << 6U) / ((IDIV << 10) + FDIV))) << 4U;
    }
    else
    {
       SystemCoreClock = ((uint32_t)((OSCHP_GetFrequency() << 6U) / ((IDIV << 10) + FDIV))) << 4U;
    }
  }
  else
  {
    /* Fractional divider bypassed. */
    if (((SCU_CLK->CLKCR1) & SCU_CLK_CLKCR1_DCLKSEL_Msk) == 0U)
    {
        SystemCoreClock = DCO1_FREQUENCY;
    }
    else
    {
        SystemCoreClock = OSCHP_GetFrequency();
    }
  }
}

__WEAK uint32_t OSCHP_GetFrequency(void)
{
  return OSCHP_FREQUENCY;
}
