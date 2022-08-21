/*------------------------------------------------------------------------------
include40.h


------------------------------------------------------------------------------*/

#ifndef __INCLUDE40
#define __INCLUDE40


#define MONITOR_40          1 // TODO
#define MONITOR_40_NAMES    1
//#define MONITOR_40_MONITOR  1
//#define MONITOR_40_CRC      1
//#define BUFFER_ARRAY_40     1
#define BUFFER_RECORD_40    1
#define PROFILE_40_NAMES    1


#ifndef MONITOR_40
#undef MONITOR_40_NAMES
#undef MONITOR_40_MONITOR
#undef MONITOR_40_CRC
#undef BUFFER_ARRAY_40
#undef BUFFER_RECORD_40
#undef PROFILE_40_NAMES
#endif


#endif
