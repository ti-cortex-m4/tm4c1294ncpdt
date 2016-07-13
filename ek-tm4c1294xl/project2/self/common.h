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

typedef const char * const message;


typedef union
{
  uchar         mb4[4];
  ulong         dw;
} combo32;


typedef struct
{
  uchar         bSecond;
  uchar         bMinute;
  uchar         bHour;
  uchar         bDay;
  uchar         bMonth;
  uchar         bYear;
} timedate_t;


typedef struct
{
  uint          wDays;
  uchar         bHours;
  uchar         bMinutes;
  uchar         bSeconds;
} date_t;


typedef struct
{
  uchar        *pbBuff;
  uint          wSize;
} buff;


#define NAME_SIZE       (8+1)


#endif
