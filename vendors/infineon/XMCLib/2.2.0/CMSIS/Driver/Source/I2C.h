/*
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
 *
 */

/**
 * @file I2C.h
 * @date 16 Dec., 2019
 * @version 2.4
 *
 * @brief I2C Driver for Infineon XMC devices
 *
 * History
 *
 * Version 1.0 Initial version<br>
 * Version 2.2 Added Status Structure for handling the driver status<br>
 * Version 2.3 Adapted to xmc1400 devices<br>
 * Version 2.4 Added IRQ priority and HDEL settings<br>
 *
 */


#include "Driver_I2C.h"
#include "xmc_scu.h"
#include "xmc_gpio.h"
#include "xmc_i2c.h"


// I2C flags
#define I2C_FLAG_INITIALIZED       (1 << 0)
#define I2C_FLAG_POWERED           (1 << 1)
#define I2C_FLAG_CONFIGURED        (1 << 2)


#if (UC_SERIES == XMC14)
#define USIC0_0_IRQn 9
#define I2C0_ISR     IRQ9_Handler

#define USIC0_1_IRQn 10U
#define I2C1_ISR     IRQ10_Handler

#define USIC1_0_IRQn 11U
#define I2C2_ISR_0   IRQ11_Handler

#define USIC1_1_IRQn 12U
#define I2C3_ISR     IRQ12_Handler
#else

#define I2C0_ISR USIC0_0_IRQHandler
#define I2C1_ISR USIC0_1_IRQHandler
#define I2C2_ISR USIC1_0_IRQHandler
#define I2C3_ISR USIC1_1_IRQHandler
#define I2C4_ISR USIC2_0_IRQHandler
#define I2C5_ISR USIC2_1_IRQHandler

#endif

// I2C Transfer Information (Run-Time)
typedef struct I2C_TRANSFER_INFO 
{
  uint32_t                rx_num;        // Total number of rx data
  uint32_t                tx_num;        // Total number of tx data
  uint8_t                 *rx_buf;       // Pointer to in data buffer
  uint8_t                 *tx_buf;       // Pointer to out data buffer
  uint32_t                rx_cnt;        // Number of data received
  uint32_t                tx_cnt;        // Number of data sent
} I2C_TRANSFER_INFO_t ;


//I2C Status
typedef struct I2C_STATUS 
{
  uint32_t busy;             // Busy flag
  uint32_t mode;             // Mode: 0=Slave, 1=Master
  uint32_t direction;        // Direction: 0=Transmitter, 1=Receiver
  uint32_t general_call;     // General Call indication (cleared on start of next Slave operation)
  uint32_t arbitration_lost; // Master lost arbitration (cleared on start of next Master operation)
  uint32_t bus_error;        // Bus error detected (cleared on start of next Master/Slave operation)
} I2C_STATUS_t;


// I2C Information (Run-Time)
typedef struct 
{
  ARM_I2C_SignalEvent_t cb_event;          // Event callback
  I2C_STATUS_t          status;            // Status flags
  uint8_t               flags;             // Control and state flags
  uint8_t               sla;               // Slave address 
  bool                  pending;           // Transfer pending (no STOP)
  uint32_t              rx_fifo_pointer;   // FIFO rx pointer
  uint32_t              tx_fifo_pointer;   // FIFO tx pointer
  I2C_TRANSFER_INFO_t   xfer;              // Transfer Info
} I2C_INFO;

// GPIO
typedef struct XMC_GPIO 
{
  XMC_GPIO_PORT_t *const port;
  const uint8_t pin;
} XMC_GPIO_t;

// I2C Resources definitions
typedef struct 
{
  XMC_GPIO_t              sda_tx_port;        // SDA Tx Pin identifier
  uint32_t                sda_pin_af_output;  // SDA Tx Pin alternate function
  XMC_GPIO_t              sda_rx_port;        // SDA Rx Pin identifier
  XMC_GPIO_CONFIG_t       *pin_sda_config;    // SDA  Pin configuration
  uint32_t                sda_pin_input;      // SDA Rx input
  XMC_GPIO_t              scl_output_port;    // SCL Pin identifier
  uint32_t                scl_pin_af_output;  // SCL Pin alternate function
  XMC_GPIO_t              scl_input_port;     // SCL Pin identifier
  XMC_GPIO_CONFIG_t       *pin_scl_config;    // SCL  Pin configuration
  uint32_t                scl_pin_input;      // SCL  Pin input
  XMC_USIC_CH_t           *i2c;               // Pointer to the i2c peripheral
  IRQn_Type               irq_num;            // I2C MASTER IRQ Number
  uint32_t                irq_priority;       // I2C MASTER IRQ priority
  uint32_t                hdel;               // I2C MASTER hold delay
  uint32_t                tx_fifo_size_num;   // FIFO tx size register num
  uint32_t                tx_fifo_size_reg;   // FIFO tx size register
  uint32_t                rx_fifo_size_num;   // FIFO rx size register num
  uint32_t                rx_fifo_size_reg;   // FIFO rx size register
  I2C_INFO                *info;              // Run-Time Information
} const I2C_RESOURCES;
