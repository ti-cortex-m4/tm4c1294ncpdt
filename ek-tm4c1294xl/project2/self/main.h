/*------------------------------------------------------------------------------
main.h


------------------------------------------------------------------------------*/

#ifndef __MAIN_H__
#define __MAIN_H__


#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "driverlib/debug.h"
#include "common.h"


#define MAJOR_VERSION   0
#define MINOR_VERSION   11


#define UART_COUNT      5


extern uint32_t g_ulSystemTimeMS;


#endif
