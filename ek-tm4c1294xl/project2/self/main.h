/*------------------------------------------------------------------------------
MAIN.H


------------------------------------------------------------------------------*/

#ifndef __MAIN
#define __MAIN


#include <stdbool.h>
#include <stdint.h>


typedef uint8_t         uchar;
typedef uint16_t        uint;
typedef uint32_t        ulong;


typedef union
{
  uchar         mpbBuff[4];
  ulong         dwBuff;
} combo32;


#endif
