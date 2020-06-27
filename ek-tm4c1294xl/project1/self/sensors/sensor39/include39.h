/*------------------------------------------------------------------------------
include39*h


------------------------------------------------------------------------------*/

#ifndef __INCLUDE39
#define __INCLUDE39


typedef struct
{
  bool          fExists;
  time          tiTime;
  uint64_t      ddwValue;
} profile39;



#define MONITOR_39          1
#define MONITOR_39_NAMES    1
#define MONITOR_39_MONITOR  1
//#define MONITOR_39_CRC      1
//#define ARRAY_39            1


#ifndef MONITOR_39
#undef MONITOR_39_NAMES
#undef MONITOR_39_MONITOR
#undef MONITOR_39_CRC
#undef ARRAY_39
#endif


#endif
