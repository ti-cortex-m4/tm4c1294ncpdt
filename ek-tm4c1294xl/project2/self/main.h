/*------------------------------------------------------------------------------
MAIN,H


------------------------------------------------------------------------------*/

#ifndef __MAIN_H__
#define __MAIN_H__


#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "lwip/tcp.h"
#include "driverlib/debug.h"
#include "common.h"


// The number of serial to Ethernet ports supported by this module.
#define UART_COUNT              5


extern uint32_t g_ulSystemTimeMS;


#endif
