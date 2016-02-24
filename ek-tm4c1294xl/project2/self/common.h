/*------------------------------------------------------------------------------
common.h


------------------------------------------------------------------------------*/

#ifndef __COMMON_H__
#define __COMMON_H__


#define MAX_CHAR        0xFF
#define MAX_INT         0xFFFF
#define MAX_LONG        0xFFFFFFFF


#define MAJOR_VERSION   0
#define MINOR_VERSION   3


typedef uint8_t         uchar;
typedef uint16_t        uint;
typedef uint32_t        ulong;


typedef union
{
  uchar         mpbBuff[4];
  ulong         dwBuff;
} combo32;


typedef struct
{
  uchar         bSecond;
  uchar         bMinute;
  uchar         bHour;
  uchar         bDay;
  uchar         bMonth;
  uchar         bYear;
} timedate;


#define NAME_SIZE       (8+1)


#endif
