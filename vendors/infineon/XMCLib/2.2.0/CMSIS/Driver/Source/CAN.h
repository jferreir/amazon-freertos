/*
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
 *
 */

/**
 * @file CAN.h
 * @date 19 July, 2016
 * @version 1.0
 *
 * @brief CAN Driver for Infineon XMC devices
 *
 * History
 *
 * Version 1.0 Initial version<br>
 */

#include "Driver_CAN.h"
#include "xmc_scu.h"
#include "xmc_gpio.h"
#include "xmc_can.h"

// CAN flags
#define CAN_INITIALIZED       (1 << 0)
#define CAN_POWERED           (1 << 1)

#if (UC_SERIES == XMC14)
#define  CAN0_0_IRQn         0U                            // CAN SR0 Interrupt                      
#define  CAN0_1_IRQn         1U                            // CAN SR1 Interrupt                      
#define  CAN0_ISR            IRQ0_Handler
#define  CAN1_ISR            IRQ1_Handler
#else
#define  CAN0_ISR            CAN0_0_IRQHandler
#define  CAN1_ISR            CAN0_1_IRQHandler
#define  CAN2_ISR            CAN0_2_IRQHandler
#define  CAN3_ISR            CAN0_3_IRQHandler
#define  CAN4_ISR            CAN0_4_IRQHandler
#define  CAN5_ISR            CAN0_5_IRQHandler
#endif

// GPIO
typedef struct XMC_GPIO 
{
  XMC_GPIO_PORT_t *const port;
  const uint8_t pin;
} XMC_GPIO_t;

typedef struct CAN_STATUS 
{
  uint32_t unit_state       : 4;                            // Unit bus state
  uint32_t last_error_code  : 4;                            // Last error code
  uint32_t tx_error_count   : 8;                            // Transmitter error count
  uint32_t rx_error_count   : 8;                            // Receiver error count
} CAN_STATUS_t;

// CAN Information (Run-Time)
typedef struct CAN_INFO
{
  ARM_CAN_SignalUnitEvent_t      cb_unit_event;             // Unit event callback
  ARM_CAN_SignalObjectEvent_t    cb_object_event;           // Object event callback
  CAN_STATUS_t                   status;                    // Status flags
  uint8_t                        RTR_response;              // Automatic Data Message response on RTR
  uint8_t                        flags;                     // CAN driver flags (node dependent)  
} CAN_INFO_t;

// CAN Resources definitions
typedef struct CAN_RESOURCES
{
  XMC_GPIO_t                     tx_port;                   // TX pin identifier
  uint32_t                       tx_alternate_function;     // TX pin alternate function
  XMC_GPIO_t                     rx_port;                   // RX pin identifier
  uint32_t                       rx_input;                  // RX pin input configuration
  IRQn_Type                      irq_num;                   // CAN IRQ Number
  const uint8_t                  current_node_index;        // Currently used CAN node index
  uint32_t                       mo_index;                  // MO allocated to the current node
  volatile CAN_INFO_t            *info;                     // Pointer to run-time information
  XMC_CAN_t                      *can;                      // Pointer to CAN peripheral
  XMC_CAN_NODE_t                 *can_node;                 // Pointer to CAN Node
  XMC_CAN_MO_t                   *can_mo;                   // Pointer to Message Object
} CAN_RESOURCES_t;
