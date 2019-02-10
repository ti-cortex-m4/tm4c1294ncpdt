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

/*
 void convertUnixTimeToDate(time_t t, DateTime *date)
 {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;

    //Negative Unix time values are not supported
    if(t < 1)
       t = 0;

    //Clear milliseconds
    date->milliseconds = 0;

    //Retrieve hours, minutes and seconds
    date->seconds = t % 60;
    t /= 60;
    date->minutes = t % 60;
    t /= 60;
    date->hours = t % 24;
    t /= 24;

    //Convert Unix time to date
    a = (uint32_t) ((4 * t + 102032) / 146097 + 15);
    b = (uint32_t) (t + 2442113 + a - (a / 4));
    c = (20 * b - 2442) / 7305;
    d = b - 365 * c - (c / 4);
    e = d * 1000 / 30601;
    f = d - e * 30 - e * 601 / 1000;

    //January and February are counted as months 13 and 14 of the previous year
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

    //Retrieve year, month and day
    date->year = c;
    date->month = e;
    date->day = f;

    //Calculate day of week
    date->dayOfWeek = computeDayOfWeek(c, e, f);
 }



 time_t convertDateToUnixTime(const DateTime *date)
 {
    uint_t y;
    uint_t m;
    uint_t d;
    uint32_t t;

    //Year
    y = date->year;
    //Month of year
    m = date->month;
    //Day of month
    d = date->day;

    //January and February are counted as months 13 and 14 of the previous year
    if(m <= 2)
    {
       m += 12;
       y -= 1;
    }

    //Convert years to days
    t = (365 * y) + (y / 4) - (y / 100) + (y / 400);
    //Convert months to days
    t += (30 * m) + (3 * (m + 1) / 5) + d;
    //Unix time starts on January 1st, 1970
    t -= 719561;
    //Convert days to seconds
    t *= 86400;
    //Add hours, minutes and seconds
    t += (3600 * date->hours) + (60 * date->minutes) + date->seconds;

    //Return Unix time
    return t;
 }
 */
