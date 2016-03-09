/*------------------------------------------------------------------------------
UNI_UTILS.C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../time/rtc.h"
//#include "response_uni.h"
#include "uni_utils.h"



#if 0
void LongTo_DateTime(time_t j,TimeObj *ttime)
{
 ulong d,m,y;
 ulong date,t;

 date  = j/86400l;
 t = j - (date * 86400l);
 date += 720000;

 y  = (4 * date - 1) / 146097;
 d  = (4 * date - 1 - 146097 * y) / 4l;

 date = (4 * d + 3) / 1461;

 d = (4 * d + 7 - 1461 * date) / 4l;
 m = (5 * d - 3) / 153;

 d = (5 * d + 2 - 153 * m) / 5l;
 y = 100 * y + date;

 if (m < 10)
  m += 3;
 else {
  m -= 9;
  y++;
 }
 ttime->month  = m;
 ttime->year   = y;
 ttime->day    = d;

 ttime->sec    = t % 60l;     t /= 60l;
 ttime->hour   = t / 60l;
 ttime->minute = t % 60l;
}
#endif

#if 1
ulong   DateTime_ToLong(time  *ttime)
{
  uchar month = ttime->bMonth;
  uint year = 2000 + ttime->bYear;

  if (month > 2)
    month -= 3;
  else
  {
    month += 9;
    year--;
  }

  ulong c   = year / 100;
  ulong ya  = year - 100 * c;
  ulong res = (146097 * c)/4 + (1461 * ya)/4 + (153 * month + 2)/5 + ttime->bDay;

  return (res - 720000) * 86400l + (ttime->bHour * 60l + ttime->bMinute) * 60l + ttime->bSecond;
}
#endif
