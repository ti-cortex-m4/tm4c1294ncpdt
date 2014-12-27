/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

#include        "main.h"



time                    tiAlt;
ulong                   dwBuffC;

static const uchar      mpbDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };



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
