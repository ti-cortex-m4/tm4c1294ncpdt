/*------------------------------------------------------------------------------
error39_include*h


------------------------------------------------------------------------------*/

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
