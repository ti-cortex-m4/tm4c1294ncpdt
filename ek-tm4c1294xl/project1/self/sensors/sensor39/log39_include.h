/*------------------------------------------------------------------------------
log39_include.h


------------------------------------------------------------------------------*/

#ifndef __LOG39_INCLUDE
#define __LOG39_INCLUDE


typedef struct
{
  time          tiNow;
  uchar         bError;
  uint          wData;
} log39;


typedef struct
{
  time          tiNow;
  uint          wCounter;
} counter39;



#define LOG39_SIZE      100
#define COUNTER39_SIZE  0x100


#endif
