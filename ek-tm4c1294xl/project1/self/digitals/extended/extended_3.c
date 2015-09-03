/*------------------------------------------------------------------------------
EXTENDED_3.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_extended_3.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../sensors/automatic_a.h"
#include "../../sensors/automatic_b.h"
#include "../../include/flash.h"
#include "../../flash/flash.h"
#include "../../flash/records.h"
#include "../../time/timedate.h"
#include "extended_3.h"



//                                         0123456789ABCDEF
static char const       szEventsAll[]  =  "События         ";



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



void    ShowEventsA(uchar  ibEvent)
{
  ShowHi(szClear); ShowHi("Событие:");
  Clear();
  switch (ibEvent) 
  {
    case 1: sprintf(szHi+9,"прибор"); break;
    case 7: sprintf(szHi+9,"фаза 1"); break;
    case 8: sprintf(szHi+9,"фаза 2"); break;
    case 9: sprintf(szHi+9,"фаза 3"); break;
    default: Error(); break;
  }
}


void    QueryEventA(uchar  ibEvent, uchar  j)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(4);                       

  PushChar((ibEvent << 4) | j);

  QueryIO(1+14+2, 2+1+2);
}


bool    QueryEventA_Full(uchar  ibEvent, uchar  j, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEventA(ibEvent,j);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent+j);

  return(1);
}


time    ReadEventA(void)
{
  time ti;
  ti.bSecond = FromBCD( PopChar() );
  ti.bMinute = FromBCD( PopChar() );
  ti.bHour   = FromBCD( PopChar() );
  PopChar();
  ti.bDay    = FromBCD( PopChar() );
  ti.bMonth  = FromBCD( PopChar() );
  ti.bYear   = FromBCD( PopChar() );

  return ti;
}


uchar   GetEventCodeA(uchar  ibEvent)
{
  switch (ibEvent)
  {
    case 1: return INC_DEVICE;
    case 7: return INC_PHASE1;
    case 8: return INC_PHASE2;
    case 9: return INC_PHASE3;
    default: return INC_ERROR;
  }
}


void    ReadEventsA(uchar  ibEvent)
{
uchar i,j;
 
  ShowEventsA(ibEvent);

  if (QueryOpenA_Full(25) == 0) { bEventCode = 0; AddImpRecord(EVE_EVENTS_BADLINK); return; }

  for (i=0; i<10; i++)
  {
    if (QueryEventA_Full(ibEvent,i,50) == 0) {  bEventCode = i+1; AddImpRecord(EVE_EVENTS_BADLINK); return; }

    InitPop(1);
    mptiEventAB1[i] = ReadEventA();
    mptiEventAB2[i] = ReadEventA();
  } 

  switch (ibEvent) {
    case 1: dwEventIndexPrev = mpdwEventDevice[ibDig]; break;
    case 7: dwEventIndexPrev = mpdwEventPhase1[ibDig]; break;
    case 8: dwEventIndexPrev = mpdwEventPhase2[ibDig]; break;
    case 9: dwEventIndexPrev = mpdwEventPhase3[ibDig]; break;
  }

  dwEventIndexCurr = 0;
  bool f = false;

  for (i=0; i<10; i++)
  {
    time ti = mptiEventAB1[i];
    if (dwEventIndexPrev == DateToEventIndex(ti)) f = true;
    if (dwEventIndexCurr < DateToEventIndex(ti))
    {
      dwEventIndexCurr = DateToEventIndex(ti);
      j = i;
    }

    ti = mptiEventAB2[i];
    if (dwEventIndexPrev == DateToEventIndex(ti)) f = true;
    if (dwEventIndexCurr < DateToEventIndex(ti))
    {
      dwEventIndexCurr = DateToEventIndex(ti);
      j = i;
    }
  }

  if (dwEventIndexCurr == 0) AddImpRecord(EVE_EVENTS_BADDATA);
  if ((f == false) && (mpboEventFirst[ibDig] == true)) { bEventCode = GetEventCodeA(ibEvent); AddImpRecord(EVE_EVENTS_OMISSION); }

  for (i=0; i<10; i++)
  {
    uchar k = (10 + j + i + 1) % 10;

    time ti = mptiEventAB1[k];
    if (dwEventIndexPrev < DateToEventIndex(ti))
    {
      bEventCode = GetEventCodeA(ibEvent) | 0x80; // внимание !
      AddImpRecord(EVE_EVENTS_A);
    }

    ti = mptiEventAB2[k];
    if (dwEventIndexPrev < DateToEventIndex(ti))
    {
      bEventCode = GetEventCodeA(ibEvent);
      AddImpRecord(EVE_EVENTS_A);
    }
  }   

  switch (ibEvent) {
    case 1: mpdwEventDevice[ibDig] = dwEventIndexCurr; break;
    case 7: mpdwEventPhase1[ibDig] = dwEventIndexCurr; break;
    case 8: mpdwEventPhase2[ibDig] = dwEventIndexCurr; break;
    case 9: mpdwEventPhase3[ibDig] = dwEventIndexCurr; break;
  }
}


void    ReadEventsAllA(void)
{
  if (mpboEventA[0] == true) {
    ReadEventsA(1);
  }
  if (mpboEventA[1] == true) {
    ReadEventsA(7);
  }
  if (mpboEventA[2] == true) {
    ReadEventsA(8);
  }
  if (mpboEventA[3] == true) {
    ReadEventsA(9);
  }
}



void    ShowEventsB(uchar  ibEvent)
{
  ShowHi(szClear); ShowHi("Событие:");
  Clear();
  switch (ibEvent) 
  {
    case 1: sprintf(szHi+9,"прибор"); break;
    case 3: sprintf(szHi+9,"фаза 1"); break;
    case 4: sprintf(szHi+9,"фаза 2"); break;
    case 5: sprintf(szHi+9,"фаза 3"); break;
    default: Error(); break;
  }
}


void    QueryEventB(uchar  ibEvent, uchar  j)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(4);                       

  PushChar(ibEvent);
  PushChar(j);

  QueryIO(1+12+2, 2+2+2);
}


bool    QueryEventB_Full(uchar  ibEvent, uchar  j, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEventB(ibEvent,j);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent+j);

  return(1);
}


time    ReadEventB(void)
{
  time ti;
  ti.bSecond = FromBCD( PopChar() );
  ti.bMinute = FromBCD( PopChar() );
  ti.bHour   = FromBCD( PopChar() );
  ti.bDay    = FromBCD( PopChar() );
  ti.bMonth  = FromBCD( PopChar() );
  ti.bYear   = FromBCD( PopChar() );

  return ti;
}


uchar   GetEventCodeB(uchar  ibEvent)
{
  switch (ibEvent)
  {
    case 1: return INC_DEVICE;
    case 3: return INC_PHASE1;
    case 4: return INC_PHASE2;
    case 5: return INC_PHASE3;
    default: return INC_ERROR;
  }
}


void    ReadEventsB(uchar  ibEvent)
{
uchar j;
 
  ShowEventsB(ibEvent);

  if (QueryOpenB_Full(25) == 0) { bEventCode = 0; AddImpRecord(EVE_EVENTS_BADLINK); return; }

  uchar i;
  for (i=0; i<10; i++)
  {
    if (QueryEventB_Full(ibEvent,i,50) == 0) {  bEventCode = i+1; AddImpRecord(EVE_EVENTS_BADLINK); return; }

    InitPop(1);
    mptiEventAB1[i] = ReadEventB();
    mptiEventAB2[i] = ReadEventB();
  } 

  switch (ibEvent) {
    case 1: dwEventIndexPrev = mpdwEventDevice[ibDig]; break;
    case 3: dwEventIndexPrev = mpdwEventPhase1[ibDig]; break;
    case 4: dwEventIndexPrev = mpdwEventPhase2[ibDig]; break;
    case 5: dwEventIndexPrev = mpdwEventPhase3[ibDig]; break;
  }

  dwEventIndexCurr = 0;
  bool f = false;

  for (i=0; i<10; i++)
  {
    time ti = mptiEventAB1[i];
    if (dwEventIndexPrev == DateToEventIndex(ti)) f = true;
    if (dwEventIndexCurr < DateToEventIndex(ti))
    {
      dwEventIndexCurr = DateToEventIndex(ti);
      j = i;
    }

    ti = mptiEventAB2[i];
    if (dwEventIndexPrev == DateToEventIndex(ti)) f = true;
    if (dwEventIndexCurr < DateToEventIndex(ti))
    {
      dwEventIndexCurr = DateToEventIndex(ti);
      j = i;
    }
  }

  if (dwEventIndexCurr == 0) AddImpRecord(EVE_EVENTS_BADDATA);
  if ((f == false) && (mpboEventFirst[ibDig] == true)) { bEventCode = GetEventCodeB(ibEvent); AddImpRecord(EVE_EVENTS_OMISSION); }

  for (i=0; i<10; i++)
  {
    uchar k = (10 + j + i + 1) % 10;

    time ti = mptiEventAB1[k];
    if (dwEventIndexPrev < DateToEventIndex(ti))
    {
      bEventCode = GetEventCodeB(ibEvent);
      AddImpRecord(EVE_EVENTS_B);
    }

    ti = mptiEventAB2[k];
    if (dwEventIndexPrev < DateToEventIndex(ti))
    {
      bEventCode = GetEventCodeB(ibEvent) | 0x80; // внимание !
      AddImpRecord(EVE_EVENTS_B);
    }
  }   

  switch (ibEvent) {
    case 1: mpdwEventDevice[ibDig] = dwEventIndexCurr; break;
    case 3: mpdwEventPhase1[ibDig] = dwEventIndexCurr; break;
    case 4: mpdwEventPhase2[ibDig] = dwEventIndexCurr; break;
    case 5: mpdwEventPhase3[ibDig] = dwEventIndexCurr; break;
  }
}


void    ReadEventsAllB(void)
{
  if (mpboEventB[0] == true) {
    ReadEventsB(1);
  }
  if (mpboEventB[1] == true) {
    ReadEventsB(3);
  }
  if (mpboEventB[2] == true) {
    ReadEventsB(4);
  }
  if (mpboEventB[3] == true) {
    ReadEventsB(5);
  }
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
