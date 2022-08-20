/*------------------------------------------------------------------------------
log40_include.h


------------------------------------------------------------------------------*/

#ifndef __LOG40_INCLUDE
#define __LOG40_INCLUDE


typedef struct
{
  time          tiNow;
  uchar         bError;
  uint          wData;
} log40;


typedef struct
{
  time          tiNow;
  uint          wCounter;
} counter40;



#define LOG40_SIZE      100
#define COUNTER40_SIZE  0x100


#endif
