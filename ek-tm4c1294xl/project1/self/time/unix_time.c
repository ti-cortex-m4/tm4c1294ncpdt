/*------------------------------------------------------------------------------
UNIX_TIME.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "unix_time.h"



time        UnixTimeToTime(uint32_t  t)
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
  uint32_t e;
  uint32_t f;

  time tm;

  // negative Unix time values are not supported
  if (t < 1)
    t = 0;

  // retrieve hours, minutes and seconds
  tm.bSecond = t % 60;
  t /= 60;
  tm.bMinute = t % 60;
  t /= 60;
  tm.bHour = t % 24;
  t /= 24;

  // convert Unix time to date
  a = (uint32_t) ((4 * t + 102032) / 146097 + 15);
  b = (uint32_t) (t + 2442113 + a - (a / 4));
  c = (20 * b - 2442) / 7305;
  d = b - 365 * c - (c / 4);
  e = d * 1000 / 30601;
  f = d - e * 30 - e * 601 / 1000;

  // January and February are counted as months 13 and 14 of the previous year
  if (e <= 13)
  {
    c -= 4716;
    e -= 1;
  }
  else
  {
    c -= 4715;
    e -= 13;
  }

  // retrieve year, month and day
  tm.bYear = c % 2000;
  tm.bMonth = e;
  tm.bDay = f;

  return tm;
}


uint32_t    TimeToUnixTime(time  tm)
{
  uint16_t y;
  uint16_t m;
  uint16_t d;

  uint32_t t;

  y = tm.bYear + 2000;
  m = tm.bMonth;
  d = tm.bDay;

  // January and February are counted as months 13 and 14 of the previous year
  if (m <= 2)
  {
    m += 12;
    y -= 1;
  }

  // convert years to days
  t = (365 * y) + (y / 4) - (y / 100) + (y / 400);
  // convert months to days
  t += (30 * m) + (3 * (m + 1) / 5) + d;
  // Unix time starts on January 1st, 1970
  t -= 719561;
  // convert days to seconds
  t *= 86400;
  // add hours, minutes and seconds
  t += (3600 * tm.bHour) + (60 * tm.bMinute) + tm.bSecond;

  return t;
}
