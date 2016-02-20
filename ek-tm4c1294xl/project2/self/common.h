/*------------------------------------------------------------------------------
common.h


------------------------------------------------------------------------------*/

#ifndef __COMMON_H__
#define __COMMON_H__


#define MAX_CHAR        0xFF
#define MAX_INT         0xFFFF
#define MAX_LONG        0xFFFFFFFF


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
