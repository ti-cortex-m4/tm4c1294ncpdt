/*------------------------------------------------------------------------------
include39.h


------------------------------------------------------------------------------*/

#ifndef __INCLUDE39
#define __INCLUDE39



typedef uchar           obis_t[6];


typedef struct
{
  uchar         bNS;
  uchar         bNR;
  uchar         bInvokeId;
} runner39;


typedef struct
{
  bool          fExists;
  time          tiTime;
  uint64_t      ddwValue;
} profile39;



#define MONITOR_39  1



#endif
