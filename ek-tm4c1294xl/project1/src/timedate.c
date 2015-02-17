/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "display/display.h"
#include        "engine.h"



time                    tiAlt;

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
  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));
	ASSERT((bMonth >= 1) && (bMonth <= 12));

  if ((bYear % 4 == 0) && (bMonth == 2))
    return 29;
  else
    return GetDaysInMonthM(bMonth);
}


// количество дней в году
uint    GetDaysInYearY(uchar  bYear)
{
  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));

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

  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));
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

  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));
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

  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));
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



bool     TrueTimeDate(void)
{
  if (tiAlt.bSecond > 59) return false;
  if (tiAlt.bMinute > 59) return false;
  if (tiAlt.bHour   > 23) return false;

  if ((tiAlt.bDay == 0) ||
  		(tiAlt.bDay > GetDaysInMonthYM(tiAlt.bYear, tiAlt.bMonth)))
    return false;

  if ((tiAlt.bMonth == 0) ||
  		(tiAlt.bMonth > 12 ))
    return false;

  if ((tiAlt.bYear < bMINYEAR) ||
  		(tiAlt.bYear > bMAXYEAR))
    return false;

  return true;
}



ulong   DateToSecIndex(void)
{
uchar   i;

  dwBuffC = 0;

  for (i=0; i<tiAlt.bYear; i++)
    dwBuffC += GetDaysInYearY(i);

  for (i=1; i<tiAlt.bMonth; i++)
    dwBuffC += GetDaysInMonthYM(tiAlt.bYear, i);

  dwBuffC += tiAlt.bDay-1;
  dwBuffC *= 1440;
  dwBuffC += tiAlt.bHour*60 + tiAlt.bMinute;
  dwBuffC *= 60;
  dwBuffC += tiAlt.bSecond;

  return(dwBuffC);
}


void    SecIndexToDate(ulong  dwT)
{
  tiAlt.bYear = 0;
  while (dwT >= (ulong)24*60*60*GetDaysInYearY(tiAlt.bYear))
  {
    dwT -= (ulong)24*60*60*GetDaysInYearY(tiAlt.bYear);
    tiAlt.bYear++;
  }

  tiAlt.bMonth = 1;
  while (dwT >= (ulong)24*60*60*GetDaysInMonthYM(tiAlt.bYear,tiAlt.bMonth))
  {
    dwT -= (ulong)24*60*60*GetDaysInMonthYM(tiAlt.bYear,tiAlt.bMonth);
    tiAlt.bMonth++;
  }

  tiAlt.bDay = dwT/((ulong)24*60*60); dwT -= (ulong)24*60*60*tiAlt.bDay;
  tiAlt.bDay++;

  tiAlt.bHour = dwT/((uint)60*60); dwT -= (ulong)60*60*tiAlt.bHour;

  tiAlt.bMinute = dwT/60;  dwT -= (ulong)60*tiAlt.bMinute;
  tiAlt.bSecond = dwT;
}



void    ShowTime(time  ti)
{
  sprintf(szLo+4,"%02u:%02u:%02u",
                 ti.bHour,
                 ti.bMinute,
                 ti.bSecond);
}


void    ShowDate(time  ti)
{
  sprintf(szLo+4,"%02u.%02u.%02u",
                 ti.bDay,
                 ti.bMonth,
                 ti.bYear);

  szLo[14] = szDigits[GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay) + 1];
}


void    ShowTimeDate(time  ti)
{
  sprintf(szLo+1,"%02u:%02u %02u.%02u.%02u",
                 ti.bHour,
                 ti.bMinute,
                 ti.bDay,
                 ti.bMonth,
                 ti.bYear);
}



void    LoadBetaMonth(uchar  ibMonth)
{
  strcpy(szBeta,szOnMonth);
  sprintf(szBeta+11, "%-2u", ibMonth + 1);
}

