/**
 ******************************************************************************
 * @file    BkDriverUart.h
 * @brief   This file provides all the headers of UART operation functions.
 ******************************************************************************
 *
 *  The MIT License
 *  Copyright (c) 2017 BEKEN Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is furnished
 *  to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ******************************************************************************
 */
#include "include.h"
#include "BkDriverUart.h"
#include "drv_model_pub.h"
#include "rtos_error.h"

OSStatus bk_uart_initialize( bk_uart_t uart, const bk_uart_config_t *config, ring_buffer_t *optional_rx_buffer )
{
    UINT32 ret;
    UINT32 status;
    DD_HANDLE uart_hdl;

    ASSERT(uart < BK_UART_MAX);
    if(BK_UART_1 == uart)
        uart_hdl = ddev_open(UART1_DEV_NAME, &status, 0);
    else
        uart_hdl = ddev_open(UART2_DEV_NAME, &status, 0);

    ASSERT(DRV_FAILURE != uart_hdl);

    ret = ddev_control(uart_hdl, CMD_UART_INIT, (void *)config);
    return ret;
}

OSStatus bk_uart_finalize( bk_uart_t uart)
{
    UINT32 status;
    DD_HANDLE uart_hdl;

    if(BK_UART_1 == uart)
        uart_hdl = ddev_open(UART1_DEV_NAME, &status, 0);
    else
        uart_hdl = ddev_open(UART2_DEV_NAME, &status, 0);

    ASSERT(DRV_FAILURE != uart_hdl);

	ddev_close(uart_hdl);

	return kNoErr;
}

OSStatus bk_uart_send( bk_uart_t uart, const void *data, uint32_t size )
{
    bk_send_string(uart, data);

    return kNoErr;
}

OSStatus bk_uart_recv( bk_uart_t uart, void *data, uint32_t size, uint32_t timeout )
{
    UINT32 ret;
    UINT32 status;
    DD_HANDLE uart_hdl;

    if(BK_UART_1 == uart)
        uart_hdl = ddev_open(UART1_DEV_NAME, &status, 0);
    else
        uart_hdl = ddev_open(UART2_DEV_NAME, &status, 0);
	
    ASSERT(DRV_FAILURE != uart_hdl);
    ret = ddev_control(uart_hdl, CMD_RX_COUNT, 0);
    if(ret < size)
    {
        return kGeneralErr;
    }

    ret = ddev_read(uart_hdl, data, size, 0);
    ASSERT(size == ret);

    return kNoErr;
}

OSStatus bk_uart_recv_prefetch( bk_uart_t uart, void *data, uint32_t size, uint32_t timeout )
{
    UINT32 ret;
    UINT32 status;
    DD_HANDLE uart_hdl;
    UART_PEEK_RX_T peek;

    if(BK_UART_1 == uart)
        uart_hdl = ddev_open(UART1_DEV_NAME, &status, 0);
    else
        uart_hdl = ddev_open(UART2_DEV_NAME, &status, 0);
	
    ASSERT(DRV_FAILURE != uart_hdl);

    peek.sig = URX_PEEK_SIG;
    peek.ptr = data;
    peek.len = size;
    ret = ddev_control(uart_hdl, CMD_RX_PEEK, &peek);
    ASSERT(size == ret);

    return kNoErr;
}

uint32_t bk_uart_get_length_in_buffer( bk_uart_t uart )
{
    uint32_t length;
    UINT32 status;
    DD_HANDLE uart_hdl;

    if(BK_UART_1 == uart)
        uart_hdl = ddev_open(UART1_DEV_NAME, &status, 0);
    else
        uart_hdl = ddev_open(UART2_DEV_NAME, &status, 0);

    ASSERT(DRV_FAILURE != uart_hdl);
    length = (uint32_t)ddev_control(uart_hdl, CMD_RX_COUNT, 0);

    return length;
}

OSStatus bk_uart_set_rx_callback(bk_uart_t uart, uart_callback callback, void *param)
{
    UINT32 ret;
    UINT32 status;
    DD_HANDLE uart_hdl;
    UART_CALLBACK_RX_T uart_callback_rx;

    if(BK_UART_1 == uart)
        uart_hdl = ddev_open(UART1_DEV_NAME, &status, 0);
    else
        uart_hdl = ddev_open(UART2_DEV_NAME, &status, 0);

    ASSERT(DRV_FAILURE != uart_hdl);

    uart_callback_rx.callback = callback;
    uart_callback_rx.param = param;
    ret = ddev_control(uart_hdl, CMD_UART_SET_RX_CALLBACK, &uart_callback_rx);
    ASSERT(UART_SUCCESS == ret);

    return kNoErr;
}

OSStatus bk_uart_diable_rx(bk_uart_t uart)
{
    UINT32 ret;
    UINT32 status;
    DD_HANDLE uart_hdl;

    if(BK_UART_1 == uart)
        uart_hdl = ddev_open(UART1_DEV_NAME, &status, 0);
    else
        uart_hdl = ddev_open(UART2_DEV_NAME, &status, 0);

    ASSERT(DRV_FAILURE != uart_hdl);

    ret = ddev_control(uart_hdl, CMD_DISABLE_UART_RX, 0);
    ASSERT(UART_SUCCESS == ret);

    return kNoErr;
}

// eof

