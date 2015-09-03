/*------------------------------------------------------------------------------
EXTENDED_3.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_extended_3.h"
#include "../../memory/mem_digitals.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
//#include "../../sensors/automatic_a.h"
//#include "../../sensors/automatic_b.h"
//#include "../../include/flash.h"
//#include "../../flash/flash.h"
//#include "../../flash/records.h"
//#include "../../time/timedate.h"
#include "extended_3_a.h"
#include "extended_3_b.h"
#include "extended_3.h"



//                                         0123456789ABCDEF
static char const       szEventsAll[]  =  "—обыти€         ";



void    ResetExtended3(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpboEventFirst[c] = true;
    mpdwEventDevice[c] = 0;
    mpdwEventPhase1[c] = 0;
    mpdwEventPhase2[c] = 0;
    mpdwEventPhase3[c] = 0;
  }

  boExt3Flag = false;

  for (c=0; c<sizeof(mpboEventA); c++)
    mpboEventA[c] = false;

  for (c=0; c<sizeof(mpboEventB); c++)
    mpboEventB[c] = false;
}


void    ResetExtended3_Full(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpboEventFirst[c] = true;
    mpdwEventDevice[c] = 0;
    mpdwEventPhase1[c] = 0;
    mpdwEventPhase2[c] = 0;
    mpdwEventPhase3[c] = 0;
  }

  uint wPageOut;
  for (wPageOut=IMP_RECORD; wPageOut<IMP_RECORD+bRECORD_PAGES; wPageOut++)
  {
    SafePageErase(wPageOut);
    wPageOut++;
  }
}



ulong   DateToEventIndex(time  ti)
{
  ulong dw = 0;

  if ((ti.bYear   == 0) &&
      (ti.bMonth  == 0) &&
      (ti.bDay    == 0) &&
      (ti.bHour   == 0) &&
      (ti.bMinute == 0) &&
      (ti.bSecond == 0)) return dw; // обрабатывать и неправильный форматы даты ?

  uchar y;
  for (y=0; y<ti.bYear; y++)
    dw += GetDaysInYearY(y);

  uchar m;
  for (m=1; m<ti.bMonth; m++)
    dw += GetDaysInMonthYM(ti.bYear,m);

  dw += ti.bDay-1;
  dw *= 24;
  dw += ti.bHour;
  dw *= 60;
  dw += ti.bMinute;
  dw *= 60;
  dw += ti.bSecond;

  return dw;
}


time    EventIndexToDate(ulong  dw)
{
  time ti;

  ti.bYear = 0;
  while (dw >= (ulong)24*60*60*GetDaysInYearY(ti.bYear))
  {
    dw -= (ulong)24*60*60*GetDaysInYearY(ti.bYear);
    ti.bYear++;
  }
  
  ti.bMonth = 1;
  while (dw >= (ulong)24*60*60*GetDaysInMonthYM(ti.bYear,ti.bMonth))
  {
    dw -= (ulong)24*60*60*GetDaysInMonthYM(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }
  
  ti.bDay = dw/86400;
  dw -= (ulong)86400*ti.bDay;
  ti.bDay++;

  ti.bHour = dw/3600;
  dw -= (ulong)3600*ti.bHour;

  ti.bMinute = dw/60;
  ti.bSecond = dw%60;

  return ti;
}



void    MakeExtended3(void)
{
  if (boExt3Flag == true)
  {
    ShowHi(szEventsAll); Clear();
    sprintf(szLo+14,"%2u",ibDig+1); DelayInf();

    switch (diCurr.bDevice)
    {
      case 1:  ReadEventsAllA();  break;
      case 2:  ReadEventsAllB();  break;
    }
    
    mpboEventFirst[ibDig] = false;
  }
}
