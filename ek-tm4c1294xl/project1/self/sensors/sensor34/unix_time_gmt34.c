/*------------------------------------------------------------------------------
UNIX_TIME_GMT34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/timedate.h"
#include "../../time/unix_time.h"
#include "unix_time_gmt34.h"



// временная зона счетчиков ESM
uchar                   bTimeZone34;



time        UnixTimeToTimeFromGMT34(uint32_t  t)
{
  if (t == 0)
    return tiZero;
  else
    return UnixTimeToTime(t + (ulong)3600*bTimeZone34);
}


uint32_t    TimeToUnixTimeToGMT34(time  tm)
{
  return TimeToUnixTime(tm) - (ulong)3600*bTimeZone34;
}
