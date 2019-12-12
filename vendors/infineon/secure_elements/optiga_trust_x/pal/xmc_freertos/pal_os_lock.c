/**
* MIT License
*
* Copyright (c) 2018 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*
*
* \file pal_os_lock.c
*
* \brief   This file implements the platform abstraction layer APIs for os locks (e.g. semaphore).
*
* \ingroup  grPAL
* @{
*/

#include "optiga/pal/pal_os_lock.h"

#include "FreeRTOS.h"
#include "semphr.h"

static SemaphoreHandle_t xSemaphore = NULL;

void pal_os_lock_init(void)
{
  vPortEnterCritical();
  if( xSemaphore == NULL )
  {
    xSemaphore = xSemaphoreCreateRecursiveMutex();
  }
  vPortExitCritical();
}

pal_status_t pal_os_lock_acquire(void)
{
  if (xSemaphoreTakeRecursive(xSemaphore, portMAX_DELAY) == pdTRUE)
  {
	return PAL_STATUS_SUCCESS;
  }

  return PAL_STATUS_FAILURE;
}

void pal_os_lock_release(void)
{
  xSemaphoreGiveRecursive(xSemaphore);
}

/**
* @}
*/
