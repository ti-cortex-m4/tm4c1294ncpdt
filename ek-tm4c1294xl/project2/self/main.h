/*------------------------------------------------------------------------------
MAIN.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_H__
#define __MAIN_H__


#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "lwip/tcp.h"
#include "driverlib/debug.h"
#include "config.h"


typedef uint8_t         uchar;
typedef uint16_t        uint;
typedef uint32_t        ulong;


typedef union
{
  uchar         mpbBuff[4];
  ulong         dwBuff;
} combo32;


#define NAME_SIZE       (8+1)


#define UART_COUNT      1


#endif
