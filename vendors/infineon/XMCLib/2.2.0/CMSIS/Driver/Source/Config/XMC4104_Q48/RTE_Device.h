/*
 *
 * Copyright (c) 2015-2018, Infineon Technologies AG
 * All rights reserved.                        
 *                                             
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                                  
 *                                                                              
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes with 
 * Infineon Technologies AG dave@infineon.com).                                                          
 *
 */

/**
 * @file RTE_Device.h
 * @date 09 October, 2018
 * @version 1.1.1
 *
 * @brief RTE Device Configuration for Infineon XMC4104_Q48
 *
 * History
 *
 * Version 1.0.0 
 *  Initial version
 *
 * Version 1.0.1 
 *  Fix pin assignment
 *
 * Version 1.1.0
 * - [New] SAI drivers 
 * - [Changed] Limit RX and TX FIFO sum of single channel to 32 entries
 * - [Fixed] Several pin configurations missing. 
 *
 * Version 1.1.1
 * - [Fixed] Format on I2S0_MCLK Output Pin Configuration
 *
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

#include "xmc_device.h"
#include "xmc_can_map.h"
#include "xmc4_gpio_map.h"
#include "xmc4_usic_map.h"

#define NO_FIFO 0
#define FIFO_SIZE_2 1
#define FIFO_SIZE_4 2
#define FIFO_SIZE_8 3
#define FIFO_SIZE_16 4
#define FIFO_SIZE_32 5

// <e> UART0 (Universal asynchronous receiver transmitter) [Driver_USART0]
// <i> Configuration settings for Driver_USART0 in component ::Drivers:UART
#define RTE_UART0                      0

//   <o> UART0_TX Pin <0=>P1_5
#define RTE_UART0_TX_ID                0
#if    (RTE_UART0_TX_ID == 0)
#define RTE_UART0_TX_PORT              P1_5
#define RTE_UART0_TX_AF                P1_5_AF_U0C0_DOUT0
#else
#error "Invalid UART0_TX Pin Configuration!"
#endif

//   <o> UART0_RX Pin <0=>P1_5 <1=>P1_4
#define RTE_UART0_RX_ID                1
#if    (RTE_UART0_RX_ID == 0)
#define RTE_UART0_RX_PORT              P1_5
#define RTE_UART0_RX_INPUT             USIC0_C0_DX0_P1_5
#elif  (RTE_UART0_RX_ID == 1)
#define RTE_UART0_RX_PORT              P1_4
#define RTE_UART0_RX_INPUT             USIC0_C0_DX0_P1_4
#else
#error "Invalid UART0_RX Pin Configuration!"
#endif

//   <o> UART0_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_UART0_RX_FIFO_SIZE_ID                4
#if    (RTE_UART0_RX_FIFO_SIZE_ID == 0)
#define RTE_UART0_RX_FIFO_SIZE         NO_FIFO
#define RTE_UART0_RX_FIFO_SIZE_NUM     0
#elif  (RTE_UART0_RX_FIFO_SIZE_ID == 1)
#define RTE_UART0_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_UART0_RX_FIFO_SIZE_NUM     2
#elif  (RTE_UART0_RX_FIFO_SIZE_ID == 2)
#define RTE_UART0_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_UART0_RX_FIFO_SIZE_NUM     4
#elif  (RTE_UART0_RX_FIFO_SIZE_ID == 3)
#define RTE_UART0_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_UART0_RX_FIFO_SIZE_NUM     8
#elif  (RTE_UART0_RX_FIFO_SIZE_ID == 4)
#define RTE_UART0_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_UART0_RX_FIFO_SIZE_NUM     16
#elif  (RTE_UART0_RX_FIFO_SIZE_ID == 5)
#define RTE_UART0_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_UART0_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid UART0_RX FIFO SIZE Configuration!"
#endif

//   <o> UART0_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_UART0_TX_FIFO_SIZE_ID                4
#if    (RTE_UART0_TX_FIFO_SIZE_ID == 0)
#define RTE_UART0_TX_FIFO_SIZE         NO_FIFO
#define RTE_UART0_TX_FIFO_SIZE_NUM     0
#elif  (RTE_UART0_TX_FIFO_SIZE_ID == 1)
#define RTE_UART0_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_UART0_TX_FIFO_SIZE_NUM     2
#elif  (RTE_UART0_TX_FIFO_SIZE_ID == 2)
#define RTE_UART0_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_UART0_TX_FIFO_SIZE_NUM     4
#elif  (RTE_UART0_TX_FIFO_SIZE_ID == 3)
#define RTE_UART0_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_UART0_TX_FIFO_SIZE_NUM     8
#elif  (RTE_UART0_TX_FIFO_SIZE_ID == 4)
#define RTE_UART0_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_UART0_TX_FIFO_SIZE_NUM     16
#elif  (RTE_UART0_TX_FIFO_SIZE_ID == 5)
#define RTE_UART0_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_UART0_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid UART0_TX FIFO SIZE Configuration!"
#endif
//</e>

// <e> UART1 (Universal asynchronous receiver transmitter) [Driver_USART1]
// <i> Configuration settings for Driver_USART1 in component ::Drivers:UART
#define RTE_UART1                      0

//   <o> UART1_TX Pin <0=>P2_5
#define RTE_UART1_TX_ID                0
#if    (RTE_UART1_TX_ID == 0)
#define RTE_UART1_TX_PORT              P2_5
#define RTE_UART1_TX_AF                P2_5_AF_U0C1_DOUT0
#else
#error "Invalid UART1_TX Pin Configuration!"
#endif

//   <o> UART1_RX Pin <0=>P2_2 <1=>P2_5
#define RTE_UART1_RX_ID                1
#if    (RTE_UART1_RX_ID == 0)
#define RTE_UART1_RX_PORT              P2_2
#define RTE_UART1_RX_INPUT             USIC0_C1_DX0_P2_2
#elif  (RTE_UART1_RX_ID == 1)
#define RTE_UART1_RX_PORT              P2_5
#define RTE_UART1_RX_INPUT             USIC0_C1_DX0_P2_5
#else
#error "Invalid UART1_RX Pin Configuration!"
#endif

//   <o> UART1_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_UART1_RX_FIFO_SIZE_ID                4
#if    (RTE_UART1_RX_FIFO_SIZE_ID == 0)
#define RTE_UART1_RX_FIFO_SIZE         NO_FIFO
#define RTE_UART1_RX_FIFO_SIZE_NUM     0
#elif  (RTE_UART1_RX_FIFO_SIZE_ID == 1)
#define RTE_UART1_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_UART1_RX_FIFO_SIZE_NUM     2
#elif  (RTE_UART1_RX_FIFO_SIZE_ID == 2)
#define RTE_UART1_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_UART1_RX_FIFO_SIZE_NUM     4
#elif  (RTE_UART1_RX_FIFO_SIZE_ID == 3)
#define RTE_UART1_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_UART1_RX_FIFO_SIZE_NUM     8
#elif  (RTE_UART1_RX_FIFO_SIZE_ID == 4)
#define RTE_UART1_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_UART1_RX_FIFO_SIZE_NUM     16
#elif  (RTE_UART1_RX_FIFO_SIZE_ID == 5)
#define RTE_UART1_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_UART1_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid UART1_RX FIFO SIZE Configuration!"
#endif

//   <o> UART1_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_UART1_TX_FIFO_SIZE_ID                4
#if    (RTE_UART1_TX_FIFO_SIZE_ID == 0)
#define RTE_UART1_TX_FIFO_SIZE         NO_FIFO
#define RTE_UART1_TX_FIFO_SIZE_NUM     0
#elif  (RTE_UART1_TX_FIFO_SIZE_ID == 1)
#define RTE_UART1_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_UART1_TX_FIFO_SIZE_NUM     2
#elif  (RTE_UART1_TX_FIFO_SIZE_ID == 2)
#define RTE_UART1_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_UART1_TX_FIFO_SIZE_NUM     4
#elif  (RTE_UART1_TX_FIFO_SIZE_ID == 3)
#define RTE_UART1_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_UART1_TX_FIFO_SIZE_NUM     8
#elif  (RTE_UART1_TX_FIFO_SIZE_ID == 4)
#define RTE_UART1_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_UART1_TX_FIFO_SIZE_NUM     16
#elif  (RTE_UART1_TX_FIFO_SIZE_ID == 5)
#define RTE_UART1_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_UART1_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid UART1_TX FIFO SIZE Configuration!"
#endif
//</e>
// <e> UART2 (Universal asynchronous receiver transmitter) [Driver_USART2]
// <i> Configuration settings for Driver_USART2 in component ::Drivers:UART
#define RTE_UART2                      0

//   <o> UART2_TX Pin <0=>P0_5
#define RTE_UART2_TX_ID                2
#if    (RTE_UART2_TX_ID == 0)
#define RTE_UART2_TX_PORT              P0_5
#define RTE_UART2_TX_AF                P0_5_AF_U1C0_DOUT0
#else
#error "Invalid UART2_TX Pin Configuration!"
#endif

//   <o> UART2_RX Pin <0=>P0_4 <1=>P0_5
#define RTE_UART2_RX_ID                3
#if    (RTE_UART2_RX_ID == 0)
#define RTE_UART2_RX_PORT              P0_4
#define RTE_UART2_RX_INPUT             USIC1_C0_DX0_P0_4
#elif  (RTE_UART2_RX_ID == 1)
#define RTE_UART2_RX_PORT              P0_5
#define RTE_UART2_RX_INPUT             USIC1_C0_DX0_P0_5
#else
#error "Invalid UART2_RX Pin Configuration!"
#endif

//   <o> UART2_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_UART2_RX_FIFO_SIZE_ID                4
#if    (RTE_UART2_RX_FIFO_SIZE_ID == 0)
#define RTE_UART2_RX_FIFO_SIZE         NO_FIFO
#define RTE_UART2_RX_FIFO_SIZE_NUM     0
#elif  (RTE_UART2_RX_FIFO_SIZE_ID == 1)
#define RTE_UART2_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_UART2_RX_FIFO_SIZE_NUM     2
#elif  (RTE_UART2_RX_FIFO_SIZE_ID == 2)
#define RTE_UART2_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_UART2_RX_FIFO_SIZE_NUM     4
#elif  (RTE_UART2_RX_FIFO_SIZE_ID == 3)
#define RTE_UART2_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_UART2_RX_FIFO_SIZE_NUM     8
#elif  (RTE_UART2_RX_FIFO_SIZE_ID == 4)
#define RTE_UART2_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_UART2_RX_FIFO_SIZE_NUM     16
#elif  (RTE_UART2_RX_FIFO_SIZE_ID == 5)
#define RTE_UART2_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_UART2_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid UART2_RX FIFO SIZE Configuration!"
#endif

//   <o> UART2_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_UART2_TX_FIFO_SIZE_ID                4
#if    (RTE_UART2_TX_FIFO_SIZE_ID == 0)
#define RTE_UART2_TX_FIFO_SIZE         NO_FIFO
#define RTE_UART2_TX_FIFO_SIZE_NUM     0
#elif  (RTE_UART2_TX_FIFO_SIZE_ID == 1)
#define RTE_UART2_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_UART2_TX_FIFO_SIZE_NUM     2
#elif  (RTE_UART2_TX_FIFO_SIZE_ID == 2)
#define RTE_UART2_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_UART2_TX_FIFO_SIZE_NUM     4
#elif  (RTE_UART2_TX_FIFO_SIZE_ID == 3)
#define RTE_UART2_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_UART2_TX_FIFO_SIZE_NUM     8
#elif  (RTE_UART2_TX_FIFO_SIZE_ID == 4)
#define RTE_UART2_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_UART2_TX_FIFO_SIZE_NUM     16
#elif  (RTE_UART2_TX_FIFO_SIZE_ID == 5)
#define RTE_UART2_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_UART2_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid UART2_TX FIFO SIZE Configuration!"
#endif
//</e>
// <e> UART3 (Universal asynchronous receiver transmitter) [Driver_USART3]
// <i> Configuration settings for Driver_USART3 in component ::Drivers:UART
#define RTE_UART3                      0

//   <o> UART3_TX Pin <0=>P0_1
#define RTE_UART3_TX_ID                0
#if    (RTE_UART3_TX_ID == 0)
#define RTE_UART3_TX_PORT              P0_1
#define RTE_UART3_TX_AF                P0_1_AF_U1C1_DOUT0
#else
#error "Invalid UART3_TX Pin Configuration!"
#endif

//   <o> UART3_RX Pin <0=>P0_1  
#define RTE_UART3_RX_ID                0
#if    (RTE_UART3_RX_ID == 0)
#define RTE_UART3_RX_PORT              P0_0
#define RTE_UART3_RX_INPUT             USIC1_C1_DX0_P0_0
#else
#error "Invalid UART3_RX Pin Configuration!"
#endif

//   <o> UART3_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_UART3_RX_FIFO_SIZE_ID                4
#if    (RTE_UART3_RX_FIFO_SIZE_ID == 0)
#define RTE_UART3_RX_FIFO_SIZE         NO_FIFO
#define RTE_UART3_RX_FIFO_SIZE_NUM     0
#elif  (RTE_UART3_RX_FIFO_SIZE_ID == 1)
#define RTE_UART3_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_UART3_RX_FIFO_SIZE_NUM     2
#elif  (RTE_UART3_RX_FIFO_SIZE_ID == 2)
#define RTE_UART3_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_UART3_RX_FIFO_SIZE_NUM     4
#elif  (RTE_UART3_RX_FIFO_SIZE_ID == 3)
#define RTE_UART3_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_UART3_RX_FIFO_SIZE_NUM     8
#elif  (RTE_UART3_RX_FIFO_SIZE_ID == 4)
#define RTE_UART3_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_UART3_RX_FIFO_SIZE_NUM     16
#elif  (RTE_UART3_RX_FIFO_SIZE_ID == 5)
#define RTE_UART3_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_UART3_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid UART3_RX FIFO SIZE Configuration!"
#endif

//   <o> UART3_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_UART3_TX_FIFO_SIZE_ID                4
#if    (RTE_UART3_TX_FIFO_SIZE_ID == 0)
#define RTE_UART3_TX_FIFO_SIZE         NO_FIFO
#define RTE_UART3_TX_FIFO_SIZE_NUM     0
#elif  (RTE_UART3_TX_FIFO_SIZE_ID == 1)
#define RTE_UART3_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_UART3_TX_FIFO_SIZE_NUM     2
#elif  (RTE_UART3_TX_FIFO_SIZE_ID == 2)
#define RTE_UART3_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_UART3_TX_FIFO_SIZE_NUM     4
#elif  (RTE_UART3_TX_FIFO_SIZE_ID == 3)
#define RTE_UART3_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_UART3_TX_FIFO_SIZE_NUM     8
#elif  (RTE_UART3_TX_FIFO_SIZE_ID == 4)
#define RTE_UART3_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_UART3_TX_FIFO_SIZE_NUM     16
#elif  (RTE_UART3_TX_FIFO_SIZE_ID == 5)
#define RTE_UART3_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_UART3_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid UART3_TX FIFO SIZE Configuration!"
#endif


// </e>
// <e> SPI0 (Serial peripheral interface) [Driver_SPI0]
// <i> Configuration settings for Driver_SPI0 in component ::Drivers:SPI
#define RTE_SPI0                      0

//   <o> SPI0 TX: MOSI(master) MISO(slave) Pin <0=>P1_5
#define RTE_SPI0_TX_ID                1
#if    (RTE_SPI0_TX_ID == 0)
#define RTE_SPI0_TX_PORT              P1_5
#define RTE_SPI0_TX_AF                P1_5_AF_U0C0_DOUT0
#else
#error "Invalid SPI0_TX Pin Configuration!"
#endif

//   <o> SPI0 RX MISO(master) MOSI(slave) Pin <0=>P1_5 <1=>P1_4
#define RTE_SPI0_RX_ID                0
#if    (RTE_SPI0_RX_ID == 0)
#define RTE_SPI0_RX_PORT              P1_5
#define RTE_SPI0_RX_INPUT             USIC0_C0_DX0_P1_5
#elif  (RTE_SPI0_RX_ID == 1)
#define RTE_SPI0_RX_PORT              P1_4
#define RTE_SPI0_RX_INPUT             USIC0_C0_DX0_P1_4
#else
#error "Invalid SPI0_RX Pin Configuration!"
#endif

//   <o> SPI0_CLK OUTPUT Pin <0=>P0_8 <1=>P1_1
#define RTE_SPI0_CLK_OUTPUT_ID                0
#if    (RTE_SPI0_CLK_OUTPUT_ID == 0)
#define RTE_SPI0_CLK_OUTPUT_PORT              P0_8
#define RTE_SPI0_CLK_AF                       P0_8_AF_U0C0_SCLKOUT 
#elif  (RTE_SPI0_CLK_OUTPUT_ID == 1)
#define RTE_SPI0_CLK_OUTPUT_PORT              P1_1
#define RTE_SPI0_CLK_AF                       P1_1_AF_U0C0_SCLKOUT
#else
#error "Invalid SPI0 CLOCK OUTPUT Pin Configuration!"
#endif

//   <h> SPI0_SLAVE SELECT Pins 
// <e> SLAVE SELECT LINE 0
// <i> Enable slave select line 0
#define RTE_SPI0_SLAVE_SELECT_LINE0 0
//   <o> SPI0_SLAVE SELECT LINE 0 Pin <0=>P0_7 <1=>P1_0 
#define RTE_SPI0_SLAVE_SELECT_LINE_0_ID                1
#if    (RTE_SPI0_SLAVE_SELECT_LINE_0_ID == 0)
#define RTE_SPI0_SLAVE_SELECT_LINE_0_PORT              P0_7
#define RTE_SPI0_SLAVE_SELECT_LINE_0_AF                P0_7_AF_U0C0_SELO0
#elif  (RTE_SPI0_SLAVE_SELECT_LINE_0_ID == 1)
#define RTE_SPI0_SLAVE_SELECT_LINE_0_PORT              P1_0
#define RTE_SPI0_SLAVE_SELECT_LINE_0_AF                P1_0_AF_U0C0_SELO0
#else
#error "Invalid SPI0 SLAVE SELECT LINE 0 Pin Configuration!"
#endif
// </e>

#define RTE_SPI0_SLAVE_SELECT_LINE1 0

#define RTE_SPI0_SLAVE_SELECT_LINE2 0

#define RTE_SPI0_SLAVE_SELECT_LINE3 0

#define RTE_SPI0_SLAVE_SELECT_LINE4 0

#define RTE_SPI0_SLAVE_SELECT_LINE5 0
// </h>

//   <o> SPI0_CLK INPUT Pin <0=>P1_1 <1=>P0_8 
#define RTE_SPI0_CLK_INPUT_ID                1
#if    (RTE_SPI0_CLK_INPUT_ID == 0)
#define RTE_SPI0_CLK_INPUT_PORT              P1_1
#define RTE_SPI0_CLK_INPUT                   USIC0_C0_DX1_P1_1
#elif  (RTE_SPI0_CLK_INPUT_ID == 1)
#define RTE_SPI0_CLK_INPUT_PORT              P0_8
#define RTE_SPI0_CLK_INPUT                   USIC0_C0_DX1_P0_8
#else
#error "Invalid SPI0 CLOCK INPUT Pin Configuration!"
#endif
//   <o> RTE_SPI0_SLAVE_SELECT INPUT Pin <0=>P1_0 <1=>P0_7
#define RTE_SPI0_SLAVE_SELECT_INPUT_ID                0
#if    (RTE_SPI0_SLAVE_SELECT_INPUT_ID == 0)
#define RTE_SPI0_SLAVE_SELECT_INPUT_PORT              P1_0
#define RTE_SPI0_SLAVE_SELECT_INPUT                   USIC0_C0_DX2_P1_0
#elif  (RTE_SPI0_SLAVE_SELECT_INPUT_ID == 1)
#define RTE_SPI0_SLAVE_SELECT_INPUT_PORT              P0_7
#define RTE_SPI0_SLAVE_SELECT_INPUT                   USIC0_C0_DX2_P0_7
#else
#error "Invalid SPI0 SLAVE SELECT INPUT Pin Configuration!"
#endif

//   <o> SPI0_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_SPI0_RX_FIFO_SIZE_ID                4
#if    (RTE_SPI0_RX_FIFO_SIZE_ID == 0)
#define RTE_SPI0_RX_FIFO_SIZE         NO_FIFO
#define RTE_SPI0_RX_FIFO_SIZE_NUM     0
#elif  (RTE_SPI0_RX_FIFO_SIZE_ID == 1)
#define RTE_SPI0_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_SPI0_RX_FIFO_SIZE_NUM     2
#elif  (RTE_SPI0_RX_FIFO_SIZE_ID == 2)
#define RTE_SPI0_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_SPI0_RX_FIFO_SIZE_NUM     4
#elif  (RTE_SPI0_RX_FIFO_SIZE_ID == 3)
#define RTE_SPI0_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_SPI0_RX_FIFO_SIZE_NUM     8
#elif  (RTE_SPI0_RX_FIFO_SIZE_ID == 4)
#define RTE_SPI0_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_SPI0_RX_FIFO_SIZE_NUM     16
#elif  (RTE_SPI0_RX_FIFO_SIZE_ID == 5)
#define RTE_SPI0_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_SPI0_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid SPI0_RX FIFO SIZE Configuration!"
#endif

//   <o> SPI0_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_SPI0_TX_FIFO_SIZE_ID                4
#if    (RTE_SPI0_TX_FIFO_SIZE_ID == 0)
#define RTE_SPI0_TX_FIFO_SIZE         NO_FIFO
#define RTE_SPI0_TX_FIFO_SIZE_NUM     0
#elif  (RTE_SPI0_TX_FIFO_SIZE_ID == 1)
#define RTE_SPI0_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_SPI0_TX_FIFO_SIZE_NUM     2
#elif  (RTE_SPI0_TX_FIFO_SIZE_ID == 2)
#define RTE_SPI0_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_SPI0_TX_FIFO_SIZE_NUM     4
#elif  (RTE_SPI0_TX_FIFO_SIZE_ID == 3)
#define RTE_SPI0_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_SPI0_TX_FIFO_SIZE_NUM     8
#elif  (RTE_SPI0_TX_FIFO_SIZE_ID == 4)
#define RTE_SPI0_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_SPI0_TX_FIFO_SIZE_NUM     16
#elif  (RTE_SPI0_TX_FIFO_SIZE_ID == 5)
#define RTE_SPI0_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_SPI0_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid SPI0_TX FIFO SIZE Configuration!"
#endif
//</e>

// <e> SPI1 (Serial peripheral interface) [Driver_SPI1]
// <i> Configuration settings for Driver_SPI1 in component ::Drivers:SPI
#define RTE_SPI1                      0

//   <o> SPI1 TX MOSI(master) MISO(slave) Pin <0=>P2_5   
#define RTE_SPI1_TX_ID                0
#if    (RTE_SPI1_TX_ID == 0)
#define RTE_SPI1_TX_PORT              P2_5
#define RTE_SPI1_TX_AF                P2_5_AF_U0C1_DOUT0
#else
#error "Invalid SPI1_TX Pin Configuration!"
#endif

//   <o> SPI1 RX MISO(master) MOSI(slave) Pin <0=>P2_2 <1=>P2_5
#define RTE_SPI1_RX_ID                1
#if    (RTE_SPI1_RX_ID == 0)
#define RTE_SPI1_RX_PORT              P2_2
#define RTE_SPI1_RX_INPUT             USIC0_C1_DX0_P2_2
#elif  (RTE_SPI1_RX_ID == 1)
#define RTE_SPI1_RX_PORT              P2_5
#define RTE_SPI1_RX_INPUT             USIC0_C1_DX0_P2_5
#else
#error "Invalid SPI1_RX Pin Configuration!"
#endif


//   <o> SPI1_CLK OUTPUT Pin <0=>P2_4
#define RTE_SPI1_CLK_OUTPUT_ID                1
#if    (RTE_SPI1_CLK_OUTPUT_ID == 0)
#define RTE_SPI1_CLK_OUTPUT_PORT              P2_4
#define RTE_SPI1_CLK_AF                       P2_4_AF_U0C1_SCLKOUT
#else
#error "Invalid SPI1 CLOCK OUTPUT Pin Configuration!"
#endif

// <h> SPI1_SLAVE SELECT Pins
// <e> SLAVE SELECT LINE 0
// <i> Enable slave select line 0
#define RTE_SPI1_SLAVE_SELECT_LINE0 0
//   <o> SPI1_SLAVE SELECT LINE 0 Pin <0=>P2_3
#define RTE_SPI1_SLAVE_SELECT_LINE_0_ID                0
#if    (RTE_SPI1_SLAVE_SELECT_LINE_0_ID == 0)
#define RTE_SPI1_SLAVE_SELECT_LINE_0_PORT              P2_3
#define RTE_SPI1_SLAVE_SELECT_LINE_0_AF                P2_3_AF_U0C1_SELO0
#else
#error "Invalid SPI1 SLAVE SELECT LINE 0 Pin Configuration!"
#endif
// </e>

#define RTE_SPI1_SLAVE_SELECT_LINE1 0 

#define RTE_SPI1_SLAVE_SELECT_LINE2 0 

#define RTE_SPI1_SLAVE_SELECT_LINE3 0 
// </h>

//   <o> SPI1_CLK INPUT Pin <0=>P2_4
#define RTE_SPI1_CLK_INPUT_ID                1
#if    (RTE_SPI1_CLK_INPUT_ID == 0)
#define RTE_SPI1_CLK_INPUT_PORT              P2_4
#define RTE_SPI1_CLK_INPUT                   USIC0_C1_DX1_P2_4
#else
#error "Invalid SPI1 CLOCK INPUT Pin Configuration!"
#endif

//   <o> RTE_SPI1_SLAVE_SELECT INPUT Pin <0=>P2_3
#define RTE_SPI1_SLAVE_SELECT_INPUT_ID                0
#if    (RTE_SPI1_SLAVE_SELECT_INPUT_ID == 0)
#define RTE_SPI1_SLAVE_SELECT_INPUT_PORT              P2_3
#define RTE_SPI1_SLAVE_SELECT_INPUT                   USIC0_C1_DX2_P2_3
#else
#error "Invalid SPI1 SLAVE SELECT INPUT Pin Configuration!"
#endif

//   <o> SPI1_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_SPI1_RX_FIFO_SIZE_ID                4
#if    (RTE_SPI1_RX_FIFO_SIZE_ID == 0)
#define RTE_SPI1_RX_FIFO_SIZE         NO_FIFO
#define RTE_SPI1_RX_FIFO_SIZE_NUM     0
#elif  (RTE_SPI1_RX_FIFO_SIZE_ID == 1)
#define RTE_SPI1_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_SPI1_RX_FIFO_SIZE_NUM     2
#elif  (RTE_SPI1_RX_FIFO_SIZE_ID == 2)
#define RTE_SPI1_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_SPI1_RX_FIFO_SIZE_NUM     4
#elif  (RTE_SPI1_RX_FIFO_SIZE_ID == 3)
#define RTE_SPI1_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_SPI1_RX_FIFO_SIZE_NUM     8
#elif  (RTE_SPI1_RX_FIFO_SIZE_ID == 4)
#define RTE_SPI1_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_SPI1_RX_FIFO_SIZE_NUM     16
#elif  (RTE_SPI1_RX_FIFO_SIZE_ID == 5)
#define RTE_SPI1_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_SPI1_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid SPI1_RX FIFO SIZE Configuration!"
#endif

//   <o> SPI1_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_SPI1_TX_FIFO_SIZE_ID                4
#if    (RTE_SPI1_TX_FIFO_SIZE_ID == 0)
#define RTE_SPI1_TX_FIFO_SIZE         NO_FIFO
#define RTE_SPI1_TX_FIFO_SIZE_NUM     0
#elif  (RTE_SPI1_TX_FIFO_SIZE_ID == 1)
#define RTE_SPI1_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_SPI1_TX_FIFO_SIZE_NUM     2
#elif  (RTE_SPI1_TX_FIFO_SIZE_ID == 2)
#define RTE_SPI1_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_SPI1_TX_FIFO_SIZE_NUM     4
#elif  (RTE_SPI1_TX_FIFO_SIZE_ID == 3)
#define RTE_SPI1_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_SPI1_TX_FIFO_SIZE_NUM     8
#elif  (RTE_SPI1_TX_FIFO_SIZE_ID == 4)
#define RTE_SPI1_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_SPI1_TX_FIFO_SIZE_NUM     16
#elif  (RTE_SPI1_TX_FIFO_SIZE_ID == 5)
#define RTE_SPI1_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_SPI1_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid SPI1_TX FIFO SIZE Configuration!"
#endif
//</e>

#define RTE_SPI2                      0

#define RTE_SPI3                      0

// <e> I2C0 (Inter-Integrated circuit) [Driver_I2C0]
// <i> Configuration settings for Driver_I2C0 in component ::Drivers:I2C
#define RTE_I2C0                      0

//   <o> I2C0_TX Pin <0=>P1_5
#define RTE_I2C0_TX_ID                0
#if    (RTE_I2C0_TX_ID == 0)
#define RTE_I2C0_TX_PORT              P1_5
#define RTE_I2C0_TX_AF                P1_5_AF_U0C0_DOUT0
#else
#error "Invalid I2C0_TX Pin Configuration!"
#endif

//   <o> I2C0_RX Pin <0=>P1_5 <1=>P1_4 
#define RTE_I2C0_RX_ID                0
#if    (RTE_I2C0_RX_ID == 0)
#define RTE_I2C0_RX_PORT              P1_5
#define RTE_I2C0_RX_INPUT             USIC0_C0_DX0_P1_5
#elif  (RTE_I2C0_RX_ID == 1)
#define RTE_I2C0_RX_PORT              P1_4
#define RTE_I2C0_RX_INPUT             USIC0_C0_DX0_P1_4
#else
#error "Invalid I2C0_RX Pin Configuration!"
#endif

//   <o> I2C0_CLK OUTPUT Pin <0=>P0_8 <1=>P1_1
#define RTE_I2C0_CLK_OUTPUT_ID                0
#if    (RTE_I2C0_CLK_OUTPUT_ID == 0)
#define RTE_I2C0_CLK_OUTPUT_PORT              P0_8
#define RTE_I2C0_CLK_AF                       P0_8_AF_U0C0_SCLKOUT 
#elif  (RTE_I2C0_CLK_OUTPUT_ID == 1)
#define RTE_I2C0_CLK_OUTPUT_PORT              P1_1
#define RTE_I2C0_CLK_AF                       P1_1_AF_U0C0_SCLKOUT
#else
#error "Invalid I2C0 CLOCK OUTPUT Pin Configuration!"
#endif

//   <o> I2C0_CLK INPUT Pin <0=>P1_1 <1=>P0_8 
#define RTE_I2C0_CLK_INPUT_ID                1
#if    (RTE_I2C0_CLK_INPUT_ID == 0)
#define RTE_I2C0_CLK_INPUT_PORT              P1_1
#define RTE_I2C0_CLK_INPUT                   USIC0_C0_DX1_P1_1
#elif  (RTE_I2C0_CLK_INPUT_ID == 1)
#define RTE_I2C0_CLK_INPUT_PORT              P0_8
#define RTE_I2C0_CLK_INPUT                   USIC0_C0_DX1_P0_8
#else
#error "Invalid I2C0 CLOCK INPUT Pin Configuration!"
#endif

//   <o> I2C0_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_I2C0_RX_FIFO_SIZE_ID                4
#if    (RTE_I2C0_RX_FIFO_SIZE_ID == 0)
#define RTE_I2C0_RX_FIFO_SIZE         NO_FIFO
#define RTE_I2C0_RX_FIFO_SIZE_NUM     0
#elif  (RTE_I2C0_RX_FIFO_SIZE_ID == 1)
#define RTE_I2C0_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_I2C0_RX_FIFO_SIZE_NUM     2
#elif  (RTE_I2C0_RX_FIFO_SIZE_ID == 2)
#define RTE_I2C0_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_I2C0_RX_FIFO_SIZE_NUM     4
#elif  (RTE_I2C0_RX_FIFO_SIZE_ID == 3)
#define RTE_I2C0_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_I2C0_RX_FIFO_SIZE_NUM     8
#elif  (RTE_I2C0_RX_FIFO_SIZE_ID == 4)
#define RTE_I2C0_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_I2C0_RX_FIFO_SIZE_NUM     16
#elif  (RTE_I2C0_RX_FIFO_SIZE_ID == 5)
#define RTE_I2C0_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_I2C0_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid I2C0_RX FIFO SIZE Configuration!"
#endif

//   <o> I2C0_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_I2C0_TX_FIFO_SIZE_ID                4
#if    (RTE_I2C0_TX_FIFO_SIZE_ID == 0)
#define RTE_I2C0_TX_FIFO_SIZE         NO_FIFO
#define RTE_I2C0_TX_FIFO_SIZE_NUM     0
#elif  (RTE_I2C0_TX_FIFO_SIZE_ID == 1)
#define RTE_I2C0_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_I2C0_TX_FIFO_SIZE_NUM     2
#elif  (RTE_I2C0_TX_FIFO_SIZE_ID == 2)
#define RTE_I2C0_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_I2C0_TX_FIFO_SIZE_NUM     4
#elif  (RTE_I2C0_TX_FIFO_SIZE_ID == 3)
#define RTE_I2C0_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_I2C0_TX_FIFO_SIZE_NUM     8
#elif  (RTE_I2C0_TX_FIFO_SIZE_ID == 4)
#define RTE_I2C0_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_I2C0_TX_FIFO_SIZE_NUM     16
#elif  (RTE_I2C0_TX_FIFO_SIZE_ID == 5)
#define RTE_I2C0_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_I2C0_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid I2C0_TX FIFO SIZE Configuration!"
#endif

//</e>

// <e> I2C1 (Inter-Integrated circuit) [Driver_I2C1]
// <i> Configuration settings for Driver_I2C1 in component ::Drivers:I2C
#define RTE_I2C1                      0

//   <o> I2C1_TX Pin <0=>P2_5   
#define RTE_I2C1_TX_ID                0
#if    (RTE_I2C1_TX_ID == 0)
#define RTE_I2C1_TX_PORT              P2_5
#define RTE_I2C1_TX_AF                P2_5_AF_U0C1_DOUT0
#else
#error "Invalid I2C1_TX Pin Configuration!"
#endif

//   <o> I2C1_RX Pin <0=>P2_2 <1=>P2_5 
#define RTE_I2C1_RX_ID                0
#if    (RTE_I2C1_RX_ID == 0)
#define RTE_I2C1_RX_PORT              P2_2
#define RTE_I2C1_RX_INPUT             USIC0_C1_DX0_P2_2
#elif  (RTE_I2C1_RX_ID == 1)
#define RTE_I2C1_RX_PORT              P2_5
#define RTE_I2C1_RX_INPUT             USIC0_C1_DX0_P2_5
#else
#error "Invalid I2C1_RX Pin Configuration!"
#endif

//   <o> I2C1_CLK OUTPUT Pin <0=>P2_4
#define RTE_I2C1_CLK_OUTPUT_ID                0
#if    (RTE_I2C1_CLK_OUTPUT_ID == 0)
#define RTE_I2C1_CLK_OUTPUT_PORT              P2_4
#define RTE_I2C1_CLK_AF                       P2_4_AF_U0C1_SCLKOUT
#else
#error "Invalid I2C1 CLOCK OUTPUT Pin Configuration!"
#endif

//   <o> I2C1_CLK INPUT Pin <0=>P2_4
#define RTE_I2C1_CLK_INPUT_ID                0
#if    (RTE_I2C1_CLK_INPUT_ID == 0)
#define RTE_I2C1_CLK_INPUT_PORT              P2_4
#define RTE_I2C1_CLK_INPUT                   USIC0_C1_DX1_P2_4
#else
#error "Invalid I2C1 CLOCK INPUT Pin Configuration!"
#endif

//   <o> I2C1_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_I2C1_RX_FIFO_SIZE_ID                4
#if    (RTE_I2C1_RX_FIFO_SIZE_ID == 0)
#define RTE_I2C1_RX_FIFO_SIZE         NO_FIFO
#define RTE_I2C1_RX_FIFO_SIZE_NUM     0
#elif  (RTE_I2C1_RX_FIFO_SIZE_ID == 1)
#define RTE_I2C1_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_I2C1_RX_FIFO_SIZE_NUM     2
#elif  (RTE_I2C1_RX_FIFO_SIZE_ID == 2)
#define RTE_I2C1_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_I2C1_RX_FIFO_SIZE_NUM     4
#elif  (RTE_I2C1_RX_FIFO_SIZE_ID == 3)
#define RTE_I2C1_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_I2C1_RX_FIFO_SIZE_NUM     8
#elif  (RTE_I2C1_RX_FIFO_SIZE_ID == 4)
#define RTE_I2C1_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_I2C1_RX_FIFO_SIZE_NUM     16
#elif  (RTE_I2C1_RX_FIFO_SIZE_ID == 5)
#define RTE_I2C1_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_I2C1_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid I2C1_RX FIFO SIZE Configuration!"
#endif

//   <o> I2C1_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_I2C1_TX_FIFO_SIZE_ID                4
#if    (RTE_I2C1_TX_FIFO_SIZE_ID == 0)
#define RTE_I2C1_TX_FIFO_SIZE         NO_FIFO
#define RTE_I2C1_TX_FIFO_SIZE_NUM     0
#elif  (RTE_I2C1_TX_FIFO_SIZE_ID == 1)
#define RTE_I2C1_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_I2C1_TX_FIFO_SIZE_NUM     2
#elif  (RTE_I2C1_TX_FIFO_SIZE_ID == 2)
#define RTE_I2C1_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_I2C1_TX_FIFO_SIZE_NUM     4
#elif  (RTE_I2C1_TX_FIFO_SIZE_ID == 3)
#define RTE_I2C1_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_I2C1_TX_FIFO_SIZE_NUM     8
#elif  (RTE_I2C1_TX_FIFO_SIZE_ID == 4)
#define RTE_I2C1_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_I2C1_TX_FIFO_SIZE_NUM     16
#elif  (RTE_I2C1_TX_FIFO_SIZE_ID == 5)
#define RTE_I2C1_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_I2C1_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid I2C1_TX FIFO SIZE Configuration!"
#endif
//</e>

#define RTE_I2C2                      0

#define RTE_I2C3                      0

// <e> I2S0 (Inter-Integrated Sound) [Driver_SAI0]
// <i> Configuration settings for Driver_SAI0 in component ::Drivers:SAI
#define RTE_I2S0                      0

//   <o> I2S0_TX Pin <0=>P1_5
#define RTE_I2S0_TX_ID                0
#if    (RTE_I2S0_TX_ID == 0)
#define RTE_I2S0_TX_PORT              P1_5
#define RTE_I2S0_TX_AF                P1_5_AF_U0C0_DOUT0
#else
#error "Invalid I2S0_TX Pin Configuration!"
#endif

//   <o> I2S0_RX Pin <0=>P1_5 <1=>P1_4
#define RTE_I2S0_RX_ID                2
#if    (RTE_I2S0_RX_ID == 0)
#define RTE_I2S0_RX_PORT              P1_5
#define RTE_I2S0_RX_INPUT             USIC0_C0_DX0_P1_5
#elif  (RTE_I2S0_RX_ID == 1)
#define RTE_I2S0_RX_PORT              P1_4
#define RTE_I2S0_RX_INPUT             USIC0_C0_DX0_P1_4
#else
#error "Invalid I2S0_RX Pin Configuration!"
#endif

//   <o> I2S0_CLK OUTPUT Pin <0=>P0_8 <1=>P1_1
#define RTE_I2S0_CLK_OUTPUT_ID                0
#if    (RTE_I2S0_CLK_OUTPUT_ID == 0)
#define RTE_I2S0_CLK_OUTPUT_PORT              P0_8
#define RTE_I2S0_CLK_AF                       P0_8_AF_U0C0_SCLKOUT
#elif  (RTE_I2S0_CLK_OUTPUT_ID == 1)
#define RTE_I2S0_CLK_OUTPUT_PORT              P1_1
#define RTE_I2S0_CLK_AF                       P1_1_AF_U0C0_SCLKOUT
#else
#error "Invalid I2S0_CLK Output Pin Configuration!"
#endif

//   <o> I2S0_CLK INPUT Pin <0=>P1_1 <1=>P0_8
#define RTE_I2S0_CLK_INPUT_ID                1
#if    (RTE_I2S0_CLK_INPUT_ID == 0)
#define RTE_I2S0_CLK_INPUT_PORT              P1_1
#define RTE_I2S0_CLK_INPUT                   USIC0_C0_DX1_P1_1
#elif  (RTE_I2S0_CLK_INPUT_ID == 1)
#define RTE_I2S0_CLK_INPUT_PORT              P0_8
#define RTE_I2S0_CLK_INPUT                   USIC0_C0_DX1_P0_8
#else
#error "Invalid I2S0_CLK Input Pin Configuration!"
#endif

//   <o> I2S0_WS OUTPUT Pin <0=>P0_7 <1=>P1_0
#define RTE_I2S0_WS_OUTPUT_ID                0
#if     (RTE_I2S0_WS_OUTPUT_ID == 0)
#define RTE_I2S0_WS_OUTPUT_PORT              P0_7
#define RTE_I2S0_WS_AF                       P0_7_AF_U0C0_SELO0
#elif   (RTE_I2S0_WS_OUTPUT_ID == 1)
#define RTE_I2S0_WS_OUTPUT_PORT              P1_0
#define RTE_I2S0_WS_AF                       P1_0_AF_U0C0_SELO0
#else
#error "Invalid I2S0_WS Output Pin Configuration!"
#endif

//   <o> I2S0_WS INPUT Pin <0=>P0_7 <1=>P1_0
#define RTE_I2S0_WS_INPUT_ID                 0
#if    (RTE_I2S0_WS_INPUT_ID == 0)
#define RTE_I2S0_WS_INPUT_PORT               P0_7
#define RTE_I2S0_WS_INPUT_ID_INPUT           USIC0_C0_DX2_P0_7
#elif  (RTE_I2S0_WS_INPUT_ID == 1)
#define RTE_I2S0_WS_INPUT_PORT               P1_0
#define RTE_I2S0_WS_INPUT_ID_INPUT           USIC0_C0_DX2_P1_0
#else
#error "Invalid I2S0_WS Input Pin Configuration!"
#endif

// <e> Enable MCLK output
#define RTE_I2S0_MCLK_OUTPUT_ENABLE          0
//   <o> I2S0_MCLK OUTPUT Pin <0=>P1_3
#define RTE_I2S0_MCLK_OUTPUT_ID              0
#if    (RTE_I2S0_MCLK_OUTPUT_ID == 0)
#define RTE_I2S0_MCLK_OUTPUT_PORT            P1_3
#define RTE_I2S0_MCLK_AF                     P1_3_AF_U0C0_MCLKOUT
#else
#error "Invalid I2S0_MCLK Output Pin Configuration!"
#endif
// </e>

//   <o> I2S0_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_I2S0_RX_FIFO_SIZE_ID                4
#if    (RTE_I2S0_RX_FIFO_SIZE_ID == 0)
#define RTE_I2S0_RX_FIFO_SIZE         NO_FIFO
#define RTE_I2S0_RX_FIFO_SIZE_NUM     0
#elif  (RTE_I2S0_RX_FIFO_SIZE_ID == 1)
#define RTE_I2S0_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_I2S0_RX_FIFO_SIZE_NUM     2
#elif  (RTE_I2S0_RX_FIFO_SIZE_ID == 2)
#define RTE_I2S0_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_I2S0_RX_FIFO_SIZE_NUM     4
#elif  (RTE_I2S0_RX_FIFO_SIZE_ID == 3)
#define RTE_I2S0_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_I2S0_RX_FIFO_SIZE_NUM     8
#elif  (RTE_I2S0_RX_FIFO_SIZE_ID == 4)
#define RTE_I2S0_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_I2S0_RX_FIFO_SIZE_NUM     16
#elif  (RTE_I2S0_RX_FIFO_SIZE_ID == 5)
#define RTE_I2S0_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_I2S0_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid I2S0_RX FIFO SIZE Configuration!"
#endif

//   <o> I2S0_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_I2S0_TX_FIFO_SIZE_ID                4
#if    (RTE_I2S0_TX_FIFO_SIZE_ID == 0)
#define RTE_I2S0_TX_FIFO_SIZE         NO_FIFO
#define RTE_I2S0_TX_FIFO_SIZE_NUM     0
#elif  (RTE_I2S0_TX_FIFO_SIZE_ID == 1)
#define RTE_I2S0_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_I2S0_TX_FIFO_SIZE_NUM     2
#elif  (RTE_I2S0_TX_FIFO_SIZE_ID == 2)
#define RTE_I2S0_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_I2S0_TX_FIFO_SIZE_NUM     4
#elif  (RTE_I2S0_TX_FIFO_SIZE_ID == 3)
#define RTE_I2S0_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_I2S0_TX_FIFO_SIZE_NUM     8
#elif  (RTE_I2S0_TX_FIFO_SIZE_ID == 4)
#define RTE_I2S0_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_I2S0_TX_FIFO_SIZE_NUM     16
#elif  (RTE_I2S0_TX_FIFO_SIZE_ID == 5)
#define RTE_I2S0_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_I2S0_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid I2S0_TX FIFO SIZE Configuration!"
#endif
//</e>

// <e> I2S1 (Inter-Integrated Sound) [Driver_SAI1]
// <i> Configuration settings for Driver_SAI1 in component ::Drivers:SAI
#define RTE_I2S1                      0

//   <o> I2S1_TX Pin <0=>P2_5
#define RTE_I2S1_TX_ID                0
#if    (RTE_I2S1_TX_ID == 0)
#define RTE_I2S1_TX_PORT              P2_5
#define RTE_I2S1_TX_AF                P2_5_AF_U0C1_DOUT0
#else
#error "Invalid I2S1_TX Pin Configuration!"
#endif

//   <o> I2S1_RX Pin <0=>P2_2 <1=>P2_5
#define RTE_I2S1_RX_ID                0
#if    (RTE_I2S1_RX_ID == 0)
#define RTE_I2S1_RX_PORT              P2_2
#define RTE_I2S1_RX_INPUT             USIC0_C1_DX0_P2_2
#elif  (RTE_I2S1_RX_ID == 1)
#define RTE_I2S1_RX_PORT              P2_5
#define RTE_I2S1_RX_INPUT             USIC0_C1_DX0_P2_5
#else
#error "Invalid I2S1_RX Pin Configuration!"
#endif

//   <o> I2S1_CLK OUTPUT Pin <0=>P2_4
#define RTE_I2S1_CLK_OUTPUT_ID                0
#if    (RTE_I2S1_CLK_OUTPUT_ID == 0)
#define RTE_I2S1_CLK_OUTPUT_PORT              P2_4
#define RTE_I2S1_CLK_AF                       P2_4_AF_U0C1_SCLKOUT
#else
#error "Invalid I2S1 CLOCK OUTPUT Pin Configuration!"
#endif

//   <o> I2S1_CLK INPUT Pin <0=>P2_4
#define RTE_I2S1_CLK_INPUT_ID                0
#if    (RTE_I2S1_CLK_INPUT_ID == 0)
#define RTE_I2S1_CLK_INPUT_PORT              P2_4
#define RTE_I2S1_CLK_INPUT                   USIC0_C1_DX1_P2_4
#else
#error "Invalid I2S1 CLOCK INPUT Pin Configuration!"
#endif

//   <o> I2S1_WS OUTPUT Pin <0=>P2_3
#define RTE_I2S1_WS_OUTPUT_ID                0
#if     (RTE_I2S1_WS_OUTPUT_ID == 0)
#define RTE_I2S1_WS_OUTPUT_PORT              P2_3
#define RTE_I2S1_WS_AF                       P2_3_AF_U0C1_SELO0
#else
#error "Invalid I2S1_WS Output Pin Configuration!"
#endif

//   <o> I2S1_WS INPUT Pin <0=>P2_3
#define RTE_I2S1_WS_INPUT_ID                 0
#if    (RTE_I2S1_WS_INPUT_ID == 0)
#define RTE_I2S1_WS_INPUT_PORT               P2_3
#define RTE_I2S1_WS_INPUT_ID_INPUT           USIC0_C1_DX2_P2_3
#else
#error "Invalid I2S1_WS Input Pin Configuration!"
#endif

#define RTE_I2S1_MCLK_OUTPUT_ENABLE          0

//   <o> I2S1_RX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_I2S1_RX_FIFO_SIZE_ID                4
#if    (RTE_I2S1_RX_FIFO_SIZE_ID == 0)
#define RTE_I2S1_RX_FIFO_SIZE         NO_FIFO
#define RTE_I2S1_RX_FIFO_SIZE_NUM     0
#elif  (RTE_I2S1_RX_FIFO_SIZE_ID == 1)
#define RTE_I2S1_RX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_I2S1_RX_FIFO_SIZE_NUM     2
#elif  (RTE_I2S1_RX_FIFO_SIZE_ID == 2)
#define RTE_I2S1_RX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_I2S1_RX_FIFO_SIZE_NUM     4
#elif  (RTE_I2S1_RX_FIFO_SIZE_ID == 3)
#define RTE_I2S1_RX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_I2S1_RX_FIFO_SIZE_NUM     8
#elif  (RTE_I2S1_RX_FIFO_SIZE_ID == 4)
#define RTE_I2S1_RX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_I2S1_RX_FIFO_SIZE_NUM     16
#elif  (RTE_I2S1_RX_FIFO_SIZE_ID == 5)
#define RTE_I2S1_RX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_I2S1_RX_FIFO_SIZE_NUM     32
#else
#error "Invalid I2S1_RX FIFO SIZE Configuration!"
#endif

//   <o> I2S1_TX FIFO ENTRIES <0=>0 <1=>2 <2=>4 <3=>8 <4=>16 <5=>32
#define RTE_I2S1_TX_FIFO_SIZE_ID                4
#if    (RTE_I2S1_TX_FIFO_SIZE_ID == 0)
#define RTE_I2S1_TX_FIFO_SIZE         NO_FIFO
#define RTE_I2S1_TX_FIFO_SIZE_NUM     0
#elif  (RTE_I2S1_TX_FIFO_SIZE_ID == 1)
#define RTE_I2S1_TX_FIFO_SIZE         FIFO_SIZE_2
#define RTE_I2S1_TX_FIFO_SIZE_NUM     2
#elif  (RTE_I2S1_TX_FIFO_SIZE_ID == 2)
#define RTE_I2S1_TX_FIFO_SIZE         FIFO_SIZE_4
#define RTE_I2S1_TX_FIFO_SIZE_NUM     4
#elif  (RTE_I2S1_TX_FIFO_SIZE_ID == 3)
#define RTE_I2S1_TX_FIFO_SIZE         FIFO_SIZE_8
#define RTE_I2S1_TX_FIFO_SIZE_NUM     8
#elif  (RTE_I2S1_TX_FIFO_SIZE_ID == 4)
#define RTE_I2S1_TX_FIFO_SIZE         FIFO_SIZE_16
#define RTE_I2S1_TX_FIFO_SIZE_NUM     16
#elif  (RTE_I2S1_TX_FIFO_SIZE_ID == 5)
#define RTE_I2S1_TX_FIFO_SIZE         FIFO_SIZE_32
#define RTE_I2S1_TX_FIFO_SIZE_NUM     32
#else
#error "Invalid I2S1_TX FIFO SIZE Configuration!"
#endif
//</e>

#define RTE_I2S2                      0

#define RTE_I2S3                      0

#if ((RTE_UART0+RTE_I2C0+RTE_SPI0+RTE_I2S0)>1)
#error "Choose just one Driver_I2C0/SPI0/UART0/SAI0 driver !"
#elif ((RTE_UART1+RTE_I2C1+RTE_SPI1+RTE_I2S1)>1)
#error "Choose just one Driver_I2C1/SPI1/UART1/SAI1 driver !"
#elif ((RTE_UART2+RTE_I2C2+RTE_SPI2+RTE_I2S2)>1)
#error "Choose just one Driver_I2C/SPI/UART2/SAI2 driver !"
#elif ((RTE_UART3+RTE_I2C3+RTE_SPI3+RTE_I2S3)>1)
#error "Choose just one Driver_I2C/SPI/UART3/SAI3 driver !"
#endif

#if (((RTE_UART0_RX_FIFO_SIZE_NUM*RTE_UART0)+\
      (RTE_I2C0_RX_FIFO_SIZE_NUM*RTE_I2C0)+\
      (RTE_SPI0_RX_FIFO_SIZE_NUM*RTE_SPI0)+\
      (RTE_I2S0_RX_FIFO_SIZE_NUM*RTE_I2S0)+\
      (RTE_UART1_RX_FIFO_SIZE_NUM*RTE_UART1)+\
      (RTE_I2C1_RX_FIFO_SIZE_NUM*RTE_I2C1)+\
      (RTE_SPI1_RX_FIFO_SIZE_NUM*RTE_SPI1)+\
      (RTE_I2S1_RX_FIFO_SIZE_NUM*RTE_I2S1)+\
      (RTE_UART0_TX_FIFO_SIZE_NUM*RTE_UART0)+\
      (RTE_I2C0_TX_FIFO_SIZE_NUM*RTE_I2C0)+\
      (RTE_SPI0_TX_FIFO_SIZE_NUM*RTE_SPI0)+\
      (RTE_I2S0_TX_FIFO_SIZE_NUM*RTE_I2S0)+\
      (RTE_UART1_TX_FIFO_SIZE_NUM*RTE_UART1)+\
      (RTE_I2C1_TX_FIFO_SIZE_NUM*RTE_I2C1)+\
      (RTE_SPI1_TX_FIFO_SIZE_NUM*RTE_SPI1)+\
      (RTE_I2S1_TX_FIFO_SIZE_NUM*RTE_I2S1))>64)
#error "Just 64 positions in a FIFO shared by RTE_x0 and RTE_x1 !"
#elif (((RTE_UART2_RX_FIFO_SIZE_NUM*RTE_UART2)+\
        (RTE_I2C2_RX_FIFO_SIZE_NUM*RTE_I2C2)+\
        (RTE_SPI2_RX_FIFO_SIZE_NUM*RTE_SPI2)+\
        (RTE_I2S2_RX_FIFO_SIZE_NUM*RTE_I2S2)+\
        (RTE_UART3_RX_FIFO_SIZE_NUM*RTE_UART3)+\
        (RTE_I2C3_RX_FIFO_SIZE_NUM*RTE_I2C3)+\
        (RTE_SPI3_RX_FIFO_SIZE_NUM*RTE_SPI3)+\
        (RTE_I2S3_RX_FIFO_SIZE_NUM*RTE_I2S3)+\
        (RTE_UART2_TX_FIFO_SIZE_NUM*RTE_UART2)+\
        (RTE_I2C2_TX_FIFO_SIZE_NUM*RTE_I2C2)+\
        (RTE_SPI2_TX_FIFO_SIZE_NUM*RTE_SPI2)+\
        (RTE_I2S2_TX_FIFO_SIZE_NUM*RTE_I2S2)+\
        (RTE_UART3_TX_FIFO_SIZE_NUM*RTE_UART3)+\
        (RTE_I2C3_TX_FIFO_SIZE_NUM*RTE_I2C3)+\
        (RTE_SPI3_TX_FIFO_SIZE_NUM*RTE_SPI3)+\
        (RTE_I2S3_TX_FIFO_SIZE_NUM*RTE_I2S3))>64)
#error "Just 64 positions in a FIFO shared by RTE_x2 and RTE_x3 !"
#endif

#endif  /* __RTE_DEVICE_H */
