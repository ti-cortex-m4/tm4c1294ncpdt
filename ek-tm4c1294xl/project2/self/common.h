/*------------------------------------------------------------------------------
COMMON,H


------------------------------------------------------------------------------*/

#ifndef __COMMON_H__
#define __COMMON_H__


typedef uint8_t         uchar;
typedef uint16_t        uint;
typedef uint32_t        ulong;


typedef union
{
  uchar         mpbBuff[4];
  ulong         dwBuff;
} combo32;


#define NAME_SIZE       (8+1)


#endif
