/*
FreeRTOS+TCP V2.0.11
Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 http://aws.amazon.com/freertos
 http://www.FreeRTOS.org
*/

 /**********************************************************************************************************************
 * Copyright (c) 2019, Infineon Technologies AG
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
 **********************************************************************************************************************/

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_DNS.h"
#include "NetworkBufferManagement.h"
#include "NetworkInterface.h"

#include "xmc_gpio.h"
#include "xmc_eth_mac.h"
#include "xmc_eth_phy.h"

#define ETH_PHY_ADDR     0
#define ETH_PHY_AUTONEG  1
#define ETH_RXD0_PIN     P2_2
#define ETH_RXD0_SEL     XMC_ETH_MAC_PORT_CTRL_RXD0_P2_2
#define ETH_RXD1_PIN     P2_3
#define ETH_RXD1_SEL     XMC_ETH_MAC_PORT_CTRL_RXD1_P2_3
#define ETH_RXER_PIN     P2_4
#define ETH_RXER_SEL     XMC_ETH_MAC_PORT_CTRL_RXER_P2_4
#define ETH_TX_EN_PIN    P0_4
#define ETH_TX_EN_PIN_AF P0_4_AF_ETH0_TX_EN
#define ETH_TXD0_PIN     P2_8
#define ETH_TXD0_PIN_AF  P2_8_AF_ETH0_TXD0
#define ETH_TXD1_PIN     P2_9
#define ETH_TXD1_PIN_AF  P2_9_AF_ETH0_TXD1
#define ETH_CLK_RMII_PIN P15_8
#define ETH_CLK_RMII_SEL XMC_ETH_MAC_PORT_CTRL_CLK_RMII_P15_8
#define ETH_CRS_DV_PIN   P15_9
#define ETH_CRS_DV_SEL   XMC_ETH_MAC_PORT_CTRL_CRS_DV_P15_9
#define ETH_MDIO_PIN     P2_0
#define ETH_MDIO_SEL     XMC_ETH_MAC_PORT_CTRL_MDIO_P2_0
#define ETH_MDC_PIN      P2_7
#define ETH_MDC_PIN_AF   P2_7_AF_ETH0_MDC
#define ETH_IRQ_PRIO     62

#ifndef configETH_MAC_NUM_RX_BUF
#define configETH_MAC_NUM_RX_BUF (4)
#endif

#ifndef configETH_MAC_NUM_TX_BUF
#define configETH_MAC_NUM_TX_BUF (4)
#endif

#define ETH_LWIP_PHY_MAX_RETRIES  0xfffffU

/* Default the size of the stack used by the EMAC deferred handler task to twice
the size of the stack used by the idle task - but allow this to be overridden in
FreeRTOSConfig.h as configMINIMAL_STACK_SIZE is a user definable constant. */
#ifndef configEMAC_TASK_STACK_SIZE
	#define configEMAC_TASK_STACK_SIZE ( 4 * configMINIMAL_STACK_SIZE )
#endif

#if defined(__ICCARM__)
#pragma data_alignment=4
static XMC_ETH_MAC_DMA_DESC_t rx_desc[configETH_MAC_NUM_RX_BUF] @ ".dram";
#pragma data_alignment=4
static XMC_ETH_MAC_DMA_DESC_t tx_desc[configETH_MAC_NUM_TX_BUF] @ ".dram";
#pragma data_alignment=4
static uint8_t rx_buf[configETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] @ ".dram";
#pragma data_alignment=4
static uint8_t tx_buf[configETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] @ ".dram";
#elif defined(__CC_ARM) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
static __ALIGNED(4) XMC_ETH_MAC_DMA_DESC_t rx_desc[configETH_MAC_NUM_RX_BUF] __attribute__((section ("RW_IRAM1")));
static __ALIGNED(4) XMC_ETH_MAC_DMA_DESC_t tx_desc[configETH_MAC_NUM_TX_BUF] __attribute__((section ("RW_IRAM1")));
static __ALIGNED(4) uint8_t rx_buf[configETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("RW_IRAM1")));
static __ALIGNED(4) uint8_t tx_buf[configETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("RW_IRAM1")));
#elif defined(__GNUC__)
static __ALIGNED(4) XMC_ETH_MAC_DMA_DESC_t rx_desc[configETH_MAC_NUM_RX_BUF] __attribute__((section ("ETH_RAM")));
static __ALIGNED(4) XMC_ETH_MAC_DMA_DESC_t tx_desc[configETH_MAC_NUM_TX_BUF] __attribute__((section ("ETH_RAM")));
static __ALIGNED(4) uint8_t rx_buf[configETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("ETH_RAM")));
static __ALIGNED(4) uint8_t tx_buf[configETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("ETH_RAM")));
#endif

static XMC_ETH_PHY_CONFIG_t eth_phy_config =
{
#if defined(XMC_ETH_PHY_KSZ8081RNB) || defined(XMC_ETH_PHY_KSZ8031RNL)
  .interface = XMC_ETH_LINK_INTERFACE_RMII,
#endif
#if defined(XMC_ETH_PHY_DP83848C)
  .interface = XMC_ETH_LINK_INTERFACE_MII,
#endif

#if ETH_PHY_AUTONEG
  .enable_auto_negotiate = true,
#else
  .duplex = ETH_PHY_DUPLEX,
  .speed = ETH_PHY_SPEED
#endif
};

/* ucMACAddress as it appears in main.c */
extern const uint8_t ucMACAddress[ 6 ];

static XMC_ETH_MAC_t eth_mac =
{
  .regs = ETH0,
  .rx_desc = rx_desc,
  .tx_desc = tx_desc,
  .rx_buf = &rx_buf[0][0],
  .tx_buf = &tx_buf[0][0],
  .num_rx_buf = configETH_MAC_NUM_RX_BUF,
  .num_tx_buf = configETH_MAC_NUM_TX_BUF
};

/* Holds the handle of the task used as a deferred interrupt processor.  The
handle is used so direct notifications can be sent to the task for all EMAC/DMA
related interrupts. */
static TaskHandle_t xEMACTaskHandle = NULL;
static void prvEMACDeferredInterruptHandlerTask(void *pvParameters);

static TimerHandle_t xPhyLinkStatusTimer = NULL;
static void prvPhyLinkStatusTimerCallback(TimerHandle_t xTimer);

static XMC_ETH_LINK_STATUS_t ulPhyLinkStatus = XMC_ETH_LINK_STATUS_DOWN;

/* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1, then the Ethernet
driver will filter incoming packets and only pass the stack those packets it
considers need processing. */
#if( ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES == 0 )
#define ipCONSIDER_FRAME_FOR_PROCESSING( pucEthernetBuffer ) eProcessBuffer
#else
#define ipCONSIDER_FRAME_FOR_PROCESSING( pucEthernetBuffer ) eConsiderFrameForProcessing( ( pucEthernetBuffer ) )
#endif

BaseType_t xNetworkInterfaceInitialise(void)
{
  /* The deferred interrupt handler task is created at the highest
	 possible priority to ensure the interrupt handler can return directly
	 to it.  The task's handle is stored in xEMACTaskHandle so interrupts can
	 notify the task when there is something to process. */
  if( xEMACTaskHandle == NULL )
  {
    XMC_ETH_MAC_PORT_CTRL_t port_control;
	XMC_GPIO_CONFIG_t gpio_config;

	/* Do whatever else is needed to initialize interface. */
	gpio_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
	XMC_GPIO_Init(ETH_RXD0_PIN, &gpio_config);
	XMC_GPIO_Init(ETH_RXD1_PIN, &gpio_config);
	XMC_GPIO_Init(ETH_CLK_RMII_PIN, &gpio_config);
	XMC_GPIO_Init(ETH_CRS_DV_PIN, &gpio_config);
	XMC_GPIO_Init(ETH_RXER_PIN, &gpio_config);
	XMC_GPIO_Init(ETH_MDIO_PIN, &gpio_config);

	port_control.raw = 0;
	port_control.mode = XMC_ETH_MAC_PORT_CTRL_MODE_RMII;
	port_control.rxd0 = ETH_RXD0_SEL;
	port_control.rxd1 = ETH_RXD1_SEL;
	port_control.clk_rmii = ETH_CLK_RMII_SEL;
	port_control.crs_dv = ETH_CRS_DV_SEL;
	port_control.rxer = ETH_RXER_SEL;
	port_control.mdio = ETH_MDIO_SEL;
	XMC_ETH_MAC_SetPortControl(&eth_mac, port_control);

    XMC_ETH_MAC_Enable(&eth_mac);
	XMC_ETH_MAC_SetManagmentClockDivider(&eth_mac);

    gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
    gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | ETH_MDC_PIN_AF);
    XMC_GPIO_Init(ETH_MDC_PIN, &gpio_config);

    XMC_GPIO_SetHardwareControl(ETH_MDIO_PIN, XMC_GPIO_HWCTRL_PERIPHERAL1);

    int32_t status;
	if ((status = XMC_ETH_PHY_Init(&eth_mac, ETH_PHY_ADDR, &eth_phy_config)) != XMC_ETH_PHY_STATUS_OK)
	{
	  return pdFALSE;
	}

    XMC_ETH_MAC_InitEx(&eth_mac);

    XMC_ETH_MAC_SetAddressEx(&eth_mac, (uint8_t *const)ucMACAddress);
    XMC_ETH_MAC_DisableJumboFrame(&eth_mac);
    XMC_ETH_MAC_EnableReceptionBroadcastFrames(&eth_mac);

    gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE;
    gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | ETH_TXD0_PIN_AF);
    XMC_GPIO_Init(ETH_TXD0_PIN, &gpio_config);

    gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | ETH_TXD1_PIN_AF);
    XMC_GPIO_Init(ETH_TXD1_PIN, &gpio_config);

    gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | ETH_TX_EN_PIN_AF);
    XMC_GPIO_Init(ETH_TX_EN_PIN, &gpio_config);

    xTaskCreate(prvEMACDeferredInterruptHandlerTask, "EMAC", configEMAC_TASK_STACK_SIZE * 2, NULL, configMAX_PRIORITIES - 1, &xEMACTaskHandle );
    configASSERT(xEMACTaskHandle);
  }

  if (xPhyLinkStatusTimer == NULL)
  {
	xPhyLinkStatusTimer = xTimerCreate("phy_link_status", pdMS_TO_TICKS(200), pdTRUE, (void *)0, prvPhyLinkStatusTimerCallback);
	configASSERT( xPhyLinkStatusTimer );
	xTimerStart(xPhyLinkStatusTimer, 0);
  }

  return pdTRUE;
}


BaseType_t xNetworkInterfaceOutput( NetworkBufferDescriptor_t * const pxDescriptor,
                                    BaseType_t xReleaseAfterSend )
{
  BaseType_t xReturn = pdFAIL;

  while (XMC_ETH_MAC_IsTxDescriptorOwnedByDma(&eth_mac) == true)
  {
    XMC_ETH_MAC_ResumeTx(&eth_mac);
  }
    uint8_t *buffer = XMC_ETH_MAC_GetTxBuffer(&eth_mac);
    memcpy(buffer, pxDescriptor->pucEthernetBuffer, pxDescriptor->xDataLength);
    XMC_ETH_MAC_SetTxBufferSize(&eth_mac, pxDescriptor->xDataLength);

    XMC_ETH_MAC_ReturnTxDescriptor(&eth_mac);
    XMC_ETH_MAC_ResumeTx(&eth_mac);

    /* Call the standard trace macro to log the send event. */
    iptraceNETWORK_INTERFACE_TRANSMIT();

    if (xReleaseAfterSend != pdFALSE)
    {
      /* It is assumed SendData() copies the data out of the FreeRTOS+TCP Ethernet
         buffer.  The Ethernet buffer is therefore no longer needed, and must be
         freed for re-use. */
      vReleaseNetworkBufferAndDescriptor(pxDescriptor);
    }

    xReturn = pdPASS;

  return xReturn;
}

void vNetworkInterfaceAllocateRAMToBuffers( NetworkBufferDescriptor_t pxNetworkBuffers[ ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS ] )
{
    /* FIX ME. */
}

BaseType_t xGetPhyLinkStatus( void )
{
  return ((XMC_ETH_PHY_GetLinkStatus(&eth_mac, ETH_PHY_ADDR) == XMC_ETH_LINK_STATUS_UP) ? pdTRUE : pdFALSE);
}

static void prvPhyLinkStatusTimerCallback(TimerHandle_t xTimer)
{
  XMC_ETH_LINK_SPEED_t speed;
  XMC_ETH_LINK_DUPLEX_t duplex;

  if (XMC_ETH_PHY_GetLinkStatus(&eth_mac, ETH_PHY_ADDR) == XMC_ETH_LINK_STATUS_DOWN)
  {
	if (ulPhyLinkStatus == XMC_ETH_LINK_STATUS_UP)
	{
      /* Enable ethernet interrupts */
      XMC_ETH_MAC_DisableEvent(&eth_mac, (uint32_t)XMC_ETH_MAC_EVENT_RECEIVE);
      NVIC_DisableIRQ((IRQn_Type)108);

      XMC_ETH_MAC_DisableTx(&eth_mac);
      XMC_ETH_MAC_DisableRx(&eth_mac);

      FreeRTOS_NetworkDown();

      ulPhyLinkStatus = XMC_ETH_LINK_STATUS_DOWN;
	}
  }
  else
  {
	if (ulPhyLinkStatus == XMC_ETH_LINK_STATUS_DOWN)
	{
      if (eth_phy_config.enable_auto_negotiate)
      {
        if (XMC_ETH_PHY_IsAutonegotiationCompleted(&eth_mac, ETH_PHY_ADDR) == false)
        {
    	  // Check autonegotiation status next time
    	  return;
        }
      }

      speed = XMC_ETH_PHY_GetLinkSpeed(&eth_mac, ETH_PHY_ADDR);
      duplex = XMC_ETH_PHY_GetLinkDuplex(&eth_mac, ETH_PHY_ADDR);

      XMC_ETH_MAC_SetLink(&eth_mac, speed, duplex);

      /* Enable ethernet interrupts */
      XMC_ETH_MAC_EnableEvent(&eth_mac, (uint32_t)XMC_ETH_MAC_EVENT_RECEIVE);

      NVIC_SetPriority(ETH0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), ETH_IRQ_PRIO, 0U));
      NVIC_ClearPendingIRQ(ETH0_0_IRQn);
      NVIC_EnableIRQ(ETH0_0_IRQn);

      XMC_ETH_MAC_EnableTx(&eth_mac);
      XMC_ETH_MAC_EnableRx(&eth_mac);

      ulPhyLinkStatus = XMC_ETH_LINK_STATUS_UP;
    }
  }
}

/* The deferred interrupt handler is a standard RTOS task.  FreeRTOS's centralised
deferred interrupt handling capabilities can also be used. */
static void prvEMACDeferredInterruptHandlerTask( void *pvParameters )
{
  NetworkBufferDescriptor_t *pxBufferDescriptor;
  size_t xBytesReceived;
  /* Used to indicate that xSendEventStructToIPTask() is being called because
     of an Ethernet receive event. */
  IPStackEvent_t xRxEvent;

  for (;;)
  {
    /* Wait for the Ethernet MAC interrupt to indicate that another packet
       has been received.  The task notification is used in a similar way to a
       counting semaphore to count Rx events, but is a lot more efficient than
       a semaphore. */
    ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

    /* See how much data was received.  Here it is assumed ReceiveSize() is
       a peripheral driver function that returns the number of bytes in the
       received Ethernet frame. */
    xBytesReceived = XMC_ETH_MAC_GetRxFrameSize(&eth_mac);

    if ((xBytesReceived > 0) && (xBytesReceived < XMC_ETH_MAC_BUF_SIZE))
    {
      /* Allocate a network buffer descriptor that points to a buffer
         large enough to hold the received frame.  As this is the simple
         rather than efficient example the received data will just be copied
         into this buffer. */
      pxBufferDescriptor = pxGetNetworkBufferWithDescriptor(xBytesReceived, 0);

      if (pxBufferDescriptor != NULL)
      {
        /* pxBufferDescriptor->pucEthernetBuffer now points to an Ethernet
           buffer large enough to hold the received data.  Copy the
           received data into pcNetworkBuffer->pucEthernetBuffer.  Here it
           is assumed ReceiveData() is a peripheral driver function that
           copies the received data into a buffer passed in as the function's
           parameter.  Remember! While is is a simple robust technique -
           it is not efficient.  An example that uses a zero copy technique
           is provided further down this page. */
    	uint8_t *buffer = XMC_ETH_MAC_GetRxBuffer(&eth_mac);
    	memcpy(pxBufferDescriptor->pucEthernetBuffer, buffer, xBytesReceived);

        pxBufferDescriptor->xDataLength = xBytesReceived;

        /* See if the data contained in the received Ethernet frame needs
           to be processed.  NOTE! It is preferable to do this in
           the interrupt service routine itself, which would remove the need
           to unblock this task for packets that don't need processing. */
        if (ipCONSIDER_FRAME_FOR_PROCESSING(pxBufferDescriptor->pucEthernetBuffer) == eProcessBuffer)
        {
          /* The event about to be sent to the TCP/IP is an Rx event. */
          xRxEvent.eEventType = eNetworkRxEvent;

          /* pvData is used to point to the network buffer descriptor that
             now references the received data. */
          xRxEvent.pvData = ( void * ) pxBufferDescriptor;

          /* Send the data to the TCP/IP stack. */
          if (xSendEventStructToIPTask(&xRxEvent, 0) == pdFALSE)
          {
            /* The buffer could not be sent to the IP task so the buffer
               must be released. */
            vReleaseNetworkBufferAndDescriptor(pxBufferDescriptor);

            /* Make a call to the standard trace macro to log the
               occurrence. */
            iptraceETHERNET_RX_EVENT_LOST();
          }
          else
          {
            /* The message was successfully sent to the TCP/IP stack.
               Call the standard trace macro to log the occurrence. */
            iptraceNETWORK_INTERFACE_RECEIVE();
          }
        }
        else
        {
          /* The Ethernet frame can be dropped, but the Ethernet buffer
             must be released. */
          vReleaseNetworkBufferAndDescriptor(pxBufferDescriptor);
        }
        XMC_ETH_MAC_ReturnRxDescriptor(&eth_mac);
      }
      else
      {
        /* The event was lost because a network buffer was not available.
           Call the standard trace macro to log the occurrence. */
        iptraceETHERNET_RX_EVENT_LOST();
        XMC_ETH_MAC_ReturnRxDescriptor(&eth_mac);
      }
    }
    XMC_ETH_MAC_ResumeRx(&eth_mac);
  }
}

void ETH0_0_IRQHandler(void)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  XMC_ETH_MAC_ClearEventStatus(&eth_mac, XMC_ETH_MAC_EVENT_RECEIVE);
  vTaskNotifyGiveFromISR(xEMACTaskHandle, &xHigherPriorityTaskWoken);

  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
