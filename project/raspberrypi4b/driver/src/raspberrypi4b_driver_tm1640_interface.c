/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
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
 * SOFTWARE. 
 *
 * @file      raspberrypi4b_driver_tm1640_interface.c
 * @brief     raspberrypi4b driver tm1640 interface source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-10-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/10/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_tm1640_interface.h"
#include "wire.h"
#include <stdarg.h>

/**
 * @brief  interface sclk gpio init
 * @return status code
 *         - 0 success
 *         - 1 sclk gpio init failed
 * @note   none
 */
uint8_t tm1640_interface_sclk_gpio_init(void)
{
    return wire_clock_init();
}

/**
 * @brief  interface sclk gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 sclk gpio deinit failed
 * @note   none
 */
uint8_t tm1640_interface_sclk_gpio_deinit(void)
{
    return wire_clock_deinit();
}

/**
 * @brief     interface sclk gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 sclk gpio write failed
 * @note      none
 */
uint8_t tm1640_interface_sclk_gpio_write(uint8_t level)
{
    return wire_clock_write(level);
}

/**
 * @brief  interface din gpio init
 * @return status code
 *         - 0 success
 *         - 1 din gpio init failed
 * @note   none
 */
uint8_t tm1640_interface_din_gpio_init(void)
{
    return wire_init();
}

/**
 * @brief  interface din gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 din gpio deinit failed
 * @note   none
 */
uint8_t tm1640_interface_din_gpio_deinit(void)
{
    return wire_deinit();
}

/**
 * @brief     interface din gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 din gpio write failed
 * @note      none
 */
uint8_t tm1640_interface_din_gpio_write(uint8_t level)
{
    return wire_write(level);
}

/**
 * @brief     interface delay us
 * @param[in] us time
 * @note      none
 */
void tm1640_interface_delay_us(uint32_t us)
{
    usleep(us);
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void tm1640_interface_delay_ms(uint32_t ms)
{
    usleep(ms * 1000);
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void tm1640_interface_debug_print(const char *const fmt, ...)
{
    char str[256];
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);
    
    (void)printf((uint8_t *)str);
}
