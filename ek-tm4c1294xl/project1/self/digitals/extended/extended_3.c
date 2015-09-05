/*------------------------------------------------------------------------------
EXTENDED_3.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_extended_3.h"
#include "../../memory/mem_digitals.h"
#include "../../devices/devices.h"
#include "../../include/flash.h"
#include "../../flash/flash.h"
#include "../../flash/records.h"
#include "../../time/timedate.h"
#include "extended_3_a.h"
#include "extended_3_b.h"
#include "extended_3.h"



//                                         0123456789ABCDEF
static char const       szExtended3[]  =  "—обыти€         ";


cache const             chExt3Flag = {EXT_3_FLAG, &fExt3Flag, sizeof(bool)};
cache const             chEventFlagA = {EXT_3_EVENT_FLAG_A, &mpfEventFlagA, sizeof(mpfEventFlagA)};
cache const             chEventFlagB = {EXT_3_EVENT_FLAG_B, &mpfEventFlagB, sizeof(mpfEventFlagB)};
cache const             chEventStart = {EXT_3_EVENT_START, &mpfEventStart, sizeof(mpfEventStart)};
cache const             chEventDevice = {EXT_3_EVENT_DEVICE, &mpdwEventDevice, sizeof(mpdwEventDevice)};
cache const             chEventPhase1 = {EXT_3_EVENT_PHASE1, &mpdwEventPhase1, sizeof(mpdwEventPhase1)};
cache const             chEventPhase2 = {EXT_3_EVENT_PHASE2, &mpdwEventPhase2, sizeof(mpdwEventPhase2)};
cache const             chEventPhase3 = {EXT_3_EVENT_PHASE3, &mpdwEventPhase3, sizeof(mpdwEventPhase3)};



void    InitExtended3(void)
{
  LoadCacheBool(&chExt3Flag, false);
  LoadCache(&chEventFlagA);
  LoadCache(&chEventFlagB);
  LoadCache(&chEventStart);
  LoadCache(&chEventDevice);
  LoadCache(&chEventPhase1);
  LoadCache(&chEventPhase2);
  LoadCache(&chEventPhase3);
}


void    ResetExtended3(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpfEventStart[c] = true;
    mpdwEventDevice[c] = 0;
    mpdwEventPhase1[c] = 0;
    mpdwEventPhase2[c] = 0;
    mpdwEventPhase3[c] = 0;
  }

  SaveCache(&chEventStart);
  SaveCache(&chEventDevice);
  SaveCache(&chEventPhase1);
  SaveCache(&chEventPhase2);
  SaveCache(&chEventPhase3);


  fExt3Flag = false;
  SaveCache(&chExt3Flag);


  uchar i;
  for (i=0; i<sizeof(mpfEventFlagA); i++)
    mpfEventFlagA[i] = false;

  SaveCache(&chEventFlagA);


  for (i=0; i<sizeof(mpfEventFlagB); i++)
    mpfEventFlagB[i] = false;

  SaveCache(&chEventFlagB);
}


void    ResetExtended3_Manual(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpfEventStart[c] = true;
    mpdwEventDevice[c] = 0;
    mpdwEventPhase1[c] = 0;
    mpdwEventPhase2[c] = 0;
    mpdwEventPhase3[c] = 0;
  }

  SaveCache(&chEventStart);
  SaveCache(&chEventDevice);
  SaveCache(&chEventPhase1);
  SaveCache(&chEventPhase2);
  SaveCache(&chEventPhase3);


  uint wPageOut;
  for (wPageOut=IMP_RECORD; wPageOut<IMP_RECORD+bRECORD_PAGES; wPageOut++)
  {
    SafePageErase(wPageOut);
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
  if (fExt3Flag == true)
  {
    ShowHi(szExtended3); Clear();
    sprintf(szLo+14,"%2u",ibDig+1); DelayInf();

    switch (diCurr.bDevice)
    {
      case 1:  ReadEventsAllA();  break;
      case 2:  ReadEventsAllB();  break;
    }
    
    mpfEventStart[ibDig] = false;
    SaveCache(&chEventStart);
  }
}
