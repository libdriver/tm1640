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
 * @file      main.c
 * @brief     main source file
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

#include "driver_tm1640_write_test.h"
#include "driver_tm1640_basic.h"
#include "shell.h"
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                              /**< uart buffer */
volatile uint16_t g_len;                         /**< uart buffer length */
static int gs_listen_fd;                         /**< network handle */
static int gs_conn_fd;                           /**< network handle */
static struct sockaddr_in gs_server_addr;        /**< server address */

/**
 * @brief     tm1640 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t tm1640(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    char short_options[] = "hipe:t:";
    struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"num", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint8_t addr = 0;
    uint8_t num = 0;
    uint8_t number[] = {TM1640_NUMBER_0, TM1640_NUMBER_1, TM1640_NUMBER_2,
                        TM1640_NUMBER_3, TM1640_NUMBER_4, TM1640_NUMBER_5,
                        TM1640_NUMBER_6, TM1640_NUMBER_7, TM1640_NUMBER_8, TM1640_NUMBER_9};

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* addr */
            case 1 :
            {
                /* set the address */
                addr = atol(optarg);
                if (addr > 7)
                {
                    return 1;
                }

                break;
            }

            /* num */
            case 2 :
            {
                /* set the number */
                num = atol(optarg);
                if (num > 9)
                {
                    return 1;
                }

                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_write", type) == 0)
    {
        /* run the write test */
        if (tm1640_write_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_init", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = tm1640_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1640_interface_debug_print("tm1640: init.\n");
        
        return 0;
    }
    else if (strcmp("e_deinit", type) == 0)
    {
        uint8_t res;
        
        /* deinit */
        res = tm1640_basic_deinit();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1640_interface_debug_print("tm1640: deinit.\n");
        
        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;
        
        /* write */
        res = tm1640_basic_write(addr, &number[num], 1);
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1640_interface_debug_print("tm1640: write address %d number %d.\n", addr, num);
        
        return 0;
    }
    else if (strcmp("e_on", type) == 0)
    {
        uint8_t res;
        
        /* on */
        res = tm1640_basic_display_on();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1640_interface_debug_print("tm1640: display on.\n");
        
        return 0;
    }
    else if (strcmp("e_off", type) == 0)
    {
        uint8_t res;
        
        /* off */
        res = tm1640_basic_display_off();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1640_interface_debug_print("tm1640: display off.\n");
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        tm1640_interface_debug_print("Usage:\n");
        tm1640_interface_debug_print("  tm1640 (-i | --information)\n");
        tm1640_interface_debug_print("  tm1640 (-h | --help)\n");
        tm1640_interface_debug_print("  tm1640 (-p | --port)\n");
        tm1640_interface_debug_print("  tm1640 (-t write | --test=write)\n");
        tm1640_interface_debug_print("  tm1640 (-e init | --example=init)\n");
        tm1640_interface_debug_print("  tm1640 (-e deinit | --example=deinit)\n");
        tm1640_interface_debug_print("  tm1640 (-e on | --example=on)\n");
        tm1640_interface_debug_print("  tm1640 (-e off | --example=off)\n");
        tm1640_interface_debug_print("  tm1640 (-e write | --example=write) [--addr=<address>]\n");
        tm1640_interface_debug_print("         [--num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>]\n");
        tm1640_interface_debug_print("\n");
        tm1640_interface_debug_print("Options:\n");
        tm1640_interface_debug_print("      --addr=<address>                   Set the start address and the range is 0-7.([default: 0])\n");
        tm1640_interface_debug_print("  -e <init | deinit | write | on | off>, --example=<init | deinit | write | on | off>\n");
        tm1640_interface_debug_print("                                         Run the driver example.\n");
        tm1640_interface_debug_print("  -h, --help                             Show the help.\n");
        tm1640_interface_debug_print("  -i, --information                      Show the chip information.\n");
        tm1640_interface_debug_print("  -p, --port                             Display the pin connections of the current board.\n");
        tm1640_interface_debug_print("      --num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>([default: 0])\n");
        tm1640_interface_debug_print("                                         Set display number.\n");
        tm1640_interface_debug_print("  -t <write>, --test=<write>             Run the driver test.\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        tm1640_info_t info;

        /* print tm1640 info */
        tm1640_info(&info);
        tm1640_interface_debug_print("tm1640: chip is %s.\n", info.chip_name);
        tm1640_interface_debug_print("tm1640: manufacturer is %s.\n", info.manufacturer_name);
        tm1640_interface_debug_print("tm1640: interface is %s.\n", info.interface);
        tm1640_interface_debug_print("tm1640: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tm1640_interface_debug_print("tm1640: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tm1640_interface_debug_print("tm1640: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tm1640_interface_debug_print("tm1640: max current is %0.2fmA.\n", info.max_current_ma);
        tm1640_interface_debug_print("tm1640: max temperature is %0.1fC.\n", info.temperature_max);
        tm1640_interface_debug_print("tm1640: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        tm1640_interface_debug_print("tm1640: GPIO interface SCLK connected to GPIO27(BCM).\n");
        tm1640_interface_debug_print("tm1640: GPIO interface DIN connected to GPIO17(BCM).\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief  socket init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
static uint8_t a_socket_init(void)
{
    int optval;
    
    /* creat a socket */
    gs_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (gs_listen_fd < 0) 
    {
        tm1640_interface_debug_print("tm1640: create socket failed.\n");
        
        return 1;
    }
    
    /* set the server port */
    memset(&gs_server_addr, 0, sizeof(gs_server_addr));
    gs_server_addr.sin_family = AF_INET;
    gs_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    gs_server_addr.sin_port = htons(6666);
    
    /* enable same port binding */
    optval = 1;
    if (setsockopt(gs_listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) < 0)
    {
        tm1640_interface_debug_print("tm1640: create socket failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    }
    
    /* bind the port */
    if (bind(gs_listen_fd, (struct sockaddr*)&gs_server_addr, sizeof(gs_server_addr)) < 0) 
    {
        tm1640_interface_debug_print("tm1640: bind failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    }
    
    /* listen the port */
    if (listen(gs_listen_fd, 10) < 0) 
    {
        tm1640_interface_debug_print("tm1640: listen failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    } 
    
    return 0;
}

/**
 * @brief     socket read
 * @param[in] *buf pointer to a buffer address
 * @param[in] len buffer length
 * @return    status code
 *             - 0 success
 *             - 1 read failed
 * @note      none
 */
static uint16_t a_socket_read(uint8_t *buf, uint16_t len)
{
    int n;
    
    /* wait data */
    gs_conn_fd = accept(gs_listen_fd, (struct sockaddr *)NULL, NULL);
    if (gs_conn_fd < 0) 
    {
        tm1640_interface_debug_print("tm1640: accept failed.\n");
        (void)close(gs_conn_fd);

        return 1;
    }
    
    /* read data */
    n = recv(gs_conn_fd, buf, len, 0);
    
    /* close the socket */
    (void)close(gs_conn_fd);
    
    return n;
}

/**
 * @brief     signal handler
 * @param[in] signum signal number
 * @note      none
 */
static void a_sig_handler(int signum)
{
    if (SIGINT == signum)
    {
        tm1640_interface_debug_print("tm1640: close the server.\n");
        (void)close(gs_listen_fd);
        exit(0);
    }
    
    return;
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* socket init*/
    res = a_socket_init();
    if (res != 0)
    {
        tm1640_interface_debug_print("tm1640: socket init failed.\n");
        
        return 1;
    }
    
    /* shell init && register tm1640 function */
    shell_init();
    shell_register("tm1640", tm1640);
    tm1640_interface_debug_print("tm1640: welcome to libdriver tm1640.\n");
    
    /* set the signal */
    signal(SIGINT, a_sig_handler);
    
    while (1)
    {
        /* read uart */
        g_len = a_socket_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                tm1640_interface_debug_print("tm1640: run failed.\n");
            }
            else if (res == 2)
            {
                tm1640_interface_debug_print("tm1640: unknown command.\n");
            }
            else if (res == 3)
            {
                tm1640_interface_debug_print("tm1640: length is too long.\n");
            }
            else if (res == 4)
            {
                tm1640_interface_debug_print("tm1640: pretreat failed.\n");
            }
            else if (res == 5)
            {
                tm1640_interface_debug_print("tm1640: param is invalid.\n");
            }
            else
            {
                tm1640_interface_debug_print("tm1640: unknown status code.\n");
            }
        }
    }
}
