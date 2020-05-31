/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "timedate.h"



time const              tiZero = { 0, 0, 0, 0, 0, 0 };

static uchar const      mpbDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };



// количество дней в месяце
uchar   GetDaysInMonthM(uchar  bMonth)
{
  ASSERT((bMonth >= 1) && (bMonth <= 12));

  return mpbDaysInMonth[bMonth-1];
}


// количество дней в месяце
uchar   GetDaysInMonthYM(uchar  bYear, uchar  bMonth)
{
//  ASSERT(bYear <= bMAXYEAR);
//  ASSERT((bMonth >= 1) && (bMonth <= 12));

  if ((bYear % 4 == 0) && (bMonth == 2))
    return 29;
  else
    return GetDaysInMonthM(bMonth);
}


// количество дней в году
uint    GetDaysInYearY(uchar  bYear)
{
//  ASSERT(bYear <= bMAXYEAR);

  if (bYear % 4 == 0)
    return 366;
  else
    return 365;
}


// день недели: 0 - понедельник, ..., 6 - воскресенье (1 января 2000 года: 5 - суббота)
uchar   GetWeekdayYMD(uchar  bYear, uchar  bMonth, uchar  bDay)
{
uchar   i;
uint    j;

  ASSERT(bYear <= bMAXYEAR);
  ASSERT((bMonth >= 1) && (bMonth <= 12));
  ASSERT((bDay >= 1) && (bDay <= 31));

  j = 5 + bDay - 1;

  for (i=1; i<bMonth; i++)
  	j += GetDaysInMonthYM(bYear, i);

  for (i=0; i<bYear; i++)
  	j += GetDaysInYearY(i);

  return j % 7;
}


// последнее воскресенье месяца
time   *GetDecretDateYM(uchar  bYear, uchar  bMonth)
{
static time ti;

  ASSERT(bYear <= bMAXYEAR);
  ASSERT((bMonth >= 1) && (bMonth <= 12));

  ti = tiZero;

  ti.bYear  = bYear;
  ti.bMonth = bMonth;

  for (ti.bDay=GetDaysInMonthYM(ti.bYear, ti.bMonth); ti.bDay>0; ti.bDay--)
    if (GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay) == 6) break;

  return &ti;
}


// количество дней с начала года
uint    GetDayIndexYMD(uchar  bYear, uchar  bMonth, uchar  bDay)
{
uchar   i;
uint    j;

  ASSERT(bYear <= bMAXYEAR);
	ASSERT((bMonth >= 1) && (bMonth <= 12));
	ASSERT((bDay >= 1) && (bDay <= 31));

  j = bDay - 1;

  for (i=1; i<bMonth; i++)
  	 j += GetDaysInMonthYM(bYear, i);

  return j;
}


// количество дней с начала года
uint    GetDayIndexMD(uchar  bMonth, uchar  bDay)
{
uchar   i;
uint    j;

  ASSERT((bMonth >= 1) && (bMonth <= 12));
  ASSERT((bDay >= 1) && (bDay <= 31));

  j = bDay - 1;

  for (i=1; i<bMonth; i++)
    j += GetDaysInMonthM(i);

  return j;
}



bool    ValidTimeDate(time  ti)
{
  if (ti.bSecond > 59) return false;
  if (ti.bMinute > 59) return false;
  if (ti.bHour   > 23) return false;

  if ((ti.bDay == 0) ||
      (ti.bDay > GetDaysInMonthYM(ti.bYear, ti.bMonth)))
    return false;

  if ((ti.bMonth == 0) ||
      (ti.bMonth > 12 ))
    return false;

  if ((ti.bYear < bMINYEAR) ||
      (ti.bYear > bMAXYEAR))
    return false;

  return true;
}



// количество секунд с начала дня
ulong   GetSecondIndex(time  ti)
{
  return( (ulong)ti.bHour*3600 + ti.bMinute*60 + ti.bSecond );
}



bool    DifferentDay(time  ti1, time  ti2)
{
  return ((ti1.bDay   != ti2.bDay)   ||
          (ti1.bMonth != ti2.bMonth) ||
          (ti1.bYear  != ti2.bYear));
}


bool    DifferentDateTime(time  ti1, time  ti2)
{
  if (ti1.bSecond != ti2.bSecond) return true;
  if (ti1.bMinute != ti2.bMinute) return true;
  if (ti1.bHour   != ti2.bHour)   return true;
  if (ti1.bDay    != ti2.bDay)    return true;
  if (ti1.bMonth  != ti2.bMonth)  return true;
  if (ti1.bYear   != ti2.bYear)   return true;
  return false;
}
