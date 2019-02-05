/*------------------------------------------------------------------------------
UNIX_TIME.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "unix_time.h"



time    UnixTimeToDate(uint32_t  t)
{
   uint32_t a;
   uint32_t b;
   uint32_t c;
   uint32_t d;
   uint32_t e;
   uint32_t f;

   time ti;

   // negative Unix time values are not supported
   if (t < 1)
      t = 0;

   // retrieve hours, minutes and seconds
   ti.bSecond = t % 60;
   t /= 60;
   ti.bMinute = t % 60;
   t /= 60;
   ti.bHour = t % 24;
   t /= 24;

   // convert Unix time to date
   a = (uint32_t) ((4 * t + 102032) / 146097 + 15);
   b = (uint32_t) (t + 2442113 + a - (a / 4));
   c = (20 * b - 2442) / 7305;
   d = b - 365 * c - (c / 4);
   e = d * 1000 / 30601;
   f = d - e * 30 - e * 601 / 1000;

   // January and February are counted as months 13 and 14 of the previous year
   if(e <= 13)
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
   ti.bYear = c % 2000;
   ti.bMonth = e;
   ti.bDay = f;

   return ti;
}
