/*------------------------------------------------------------------------------
UNIX_TIME_GMT34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/unix_time.h"
#include "unix_time_gmt34.h"



extern  uchar                   bTimeZone34;



time        UnixTimeToTimeFromGMT34(uint32_t  t)
{
  return UnixTimeToTime(t + (ulong)3600*bTimeZone34);
}


uint32_t    TimeToUnixTimeToGMT34(time  tm)
{
  return TimeToUnixTime(tm) - (ulong)3600*bTimeZone34;
}
