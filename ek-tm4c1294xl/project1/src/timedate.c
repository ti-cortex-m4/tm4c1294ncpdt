/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "display.h"
#include        "lines.h"
#include        "engine.h"
#include        "rtc.h"



time                    tiAlt;

time const              tiZero = { 0, 0, 0, 0, 0, 0 };

uchar const             mpbDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };



uchar   DaysInMonth(void)
{
  if ((tiAlt.bYear % 4 == 0) && (tiAlt.bMonth == 2))
    return(29);
  else
    return( mpbDaysInMonth[tiAlt.bMonth - 1] );
}


uchar   DaysInMonthSpec(uchar  bYear, uchar  bMonth)
{
  if ((bYear % 4 == 0) && (bMonth == 2))
    return(29);
  else
    return( mpbDaysInMonth[bMonth-1] );
}


uint    DaysInYearSpec(uchar  bYear)
{
  if (bYear % 4 == 0)
    return(366);
  else
    return(365);
}



// возвращает день недели (0: понедельник, ..., 6: воскресенье)
uchar   Weekday(void)
{
uchar   i;
uint    wT;

  wT = 5 - 1 + tiAlt.bDay;          // 5: суббота - 1 января 2000 года

  for (i=1; i<tiAlt.bMonth; i++)
  {
    if ((tiAlt.bYear % 4 == 0) && (i == 2))
      wT += 29;
    else
      wT += mpbDaysInMonth[i - 1];
  }

  for (i=0; i<tiAlt.bYear; i++)
  {
    if (i % 4 == 0)
      wT += 366;
    else
      wT += 365;
  }

  return(wT % 7);
}


// вычисляет количество дней с начала года
uint    GetDayIndex(void)
{
uchar   i;
uint    wT;

  wT = tiAlt.bDay - 1;

  for (i=1; i<tiAlt.bMonth; i++)
  {
    if ((tiAlt.bYear % 4 == 0) && (i == 2))
      wT += 29;
    else
      wT += mpbDaysInMonth[i - 1];
  }

  return(wT);
}


bool     TrueTimeDate(void)
{
  if (tiAlt.bSecond > 59) return false;
  if (tiAlt.bMinute > 59) return false;
  if (tiAlt.bHour   > 23) return false;

  if ((tiAlt.bDay == 0) || (tiAlt.bDay > DaysInMonth()))
    return false;

  if ((tiAlt.bMonth == 0) || (tiAlt.bMonth > 12 ))
    return false;

  if ((tiAlt.bYear < 2) || (tiAlt.bYear > 99))
    return false;

  return true;
}


// находит последнее воскресенье месяца текущего года
void    DecretDate(void)
{
uchar   i;

  tiAlt.bYear = (*PGetCurrTimeDate()).bYear;

  for (i=DaysInMonth(); i>0; i--)
  {
    tiAlt.bDay = i;
    if (Weekday() == 6) return;         // 6: воскресенье
  }
}



ulong   DateToSecIndex(void)
{
uchar   i;

  dwBuffC = 0;

  for (i=0; i<tiAlt.bYear; i++)
    dwBuffC += DaysInYearSpec(i);

  for (i=1; i<tiAlt.bMonth; i++)
    dwBuffC += DaysInMonthSpec(tiAlt.bYear,i);

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
  while (dwT >= (ulong)24*60*60*DaysInYearSpec(tiAlt.bYear))
  {
    dwT -= (ulong)24*60*60*DaysInYearSpec(tiAlt.bYear);
    tiAlt.bYear++;
  }

  tiAlt.bMonth = 1;
  while (dwT >= (ulong)24*60*60*DaysInMonthSpec(tiAlt.bYear,tiAlt.bMonth))
  {
    dwT -= (ulong)24*60*60*DaysInMonthSpec(tiAlt.bYear,tiAlt.bMonth);
    tiAlt.bMonth++;
  }

  tiAlt.bDay = dwT/((ulong)24*60*60); dwT -= (ulong)24*60*60*tiAlt.bDay;
  tiAlt.bDay++;

  tiAlt.bHour = dwT/((uint)60*60); dwT -= (ulong)60*60*tiAlt.bHour;

  tiAlt.bMinute = dwT/60;  dwT -= (ulong)60*tiAlt.bMinute;
  tiAlt.bSecond = dwT;
}



void    ShowTime(void)
{
  sprintf(szLo+4,"%02u:%02u:%02u",
                 tiAlt.bHour,
                 tiAlt.bMinute,
                 tiAlt.bSecond);
}


void    ShowDate(void)
{
  sprintf(szLo+4,"%02u.%02u.%02u",
                 tiAlt.bDay,
                 tiAlt.bMonth,
                 tiAlt.bYear);

  szLo[14] = szDigits[Weekday() + 1];
}


void    ShowTimeDate(void)
{
  sprintf(szLo+1,"%02u:%02u %02u.%02u.%02u",
                 tiAlt.bHour,
                 tiAlt.bMinute,
                 tiAlt.bDay,
                 tiAlt.bMonth,
                 tiAlt.bYear);
}



void    LoadBetaMonth(uchar  ibMonth)
{
  strcpy(szBeta,szOnMonth);
  sprintf(szBeta+11, "%-2u", ibMonth + 1);
}

