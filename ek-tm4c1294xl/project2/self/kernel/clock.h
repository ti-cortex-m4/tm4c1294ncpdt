/*------------------------------------------------------------------------------
clock.h


------------------------------------------------------------------------------*/

#define SECONDS_IN_DAY      (ulong)(24*60*60)
#define SECONDS_IN_HOUR     (uint)(60*60)
#define SECONDS_IN_MINUTE   (uchar)60



void Clock_1Hz(void);
ulong GetClockSeconds(void);
