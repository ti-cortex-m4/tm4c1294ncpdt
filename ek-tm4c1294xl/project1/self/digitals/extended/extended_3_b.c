/*------------------------------------------------------------------------------
EXTENDED_3_B!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_extended_3.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../sensors/sensor2/automatic2.h"
#include "../../flash/records.h"
#include "extended_3.h"
#include "extended_3_b.h"



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
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEventB(ibEvent,j);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
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


void    ReadEventsB(uchar  ibCan, uchar  ibEvent)
{
uchar j;
ulong dwCurr, dwPrev;

  ShowEventsB(ibEvent);

  if (QueryOpenB_Full(ibCan, 25) == 0) { bEventCode = 0; AddImpRecord(EVE_EVENTS_BADLINK); return; }

  uchar i;
  for (i=0; i<10; i++)
  {
    if (QueryEventB_Full(ibEvent,i,50) == 0) {  bEventCode = i+1; AddImpRecord(EVE_EVENTS_BADLINK); return; }

    InitPop(1);
    mptiEventAB1[i] = ReadEventB();
    mptiEventAB2[i] = ReadEventB();
  }

  switch (ibEvent) {
    case 1: dwPrev = mpdwEventDevice[ibDig]; break;
    case 3: dwPrev = mpdwEventPhase1[ibDig]; break;
    case 4: dwPrev = mpdwEventPhase2[ibDig]; break;
    case 5: dwPrev = mpdwEventPhase3[ibDig]; break;
  }

  dwCurr = 0;
  bool f = false;

  for (i=0; i<10; i++)
  {
    time ti = mptiEventAB1[i];
    if (dwPrev == DateToEventIndex(ti)) f = true;
    if (dwCurr < DateToEventIndex(ti))
    {
      dwCurr = DateToEventIndex(ti);
      j = i;
    }

    ti = mptiEventAB2[i];
    if (dwPrev == DateToEventIndex(ti)) f = true;
    if (dwCurr < DateToEventIndex(ti))
    {
      dwCurr = DateToEventIndex(ti);
      j = i;
    }
  }

  if (dwCurr == 0) AddImpRecord(EVE_EVENTS_BADDATA);
  if ((f == false) && (mpfEventStart[ibDig] == true)) { bEventCode = GetEventCodeB(ibEvent); AddImpRecord(EVE_EVENTS_OMISSION); }

  for (i=0; i<10; i++)
  {
    uchar k = (10 + j + i + 1) % 10;

    time ti = mptiEventAB1[k];
    if (dwPrev < DateToEventIndex(ti))
    {
      tiRecordTime = ti;
      bEventCode = GetEventCodeB(ibEvent);
      AddImpRecord(EVE_EVENTS_B);
    }

    ti = mptiEventAB2[k];
    if (dwPrev < DateToEventIndex(ti))
    {
      tiRecordTime = ti;
      bEventCode = GetEventCodeB(ibEvent) | 0x80; // внимание !
      AddImpRecord(EVE_EVENTS_B);
    }
  }

  switch (ibEvent) {
    case 1: mpdwEventDevice[ibDig] = dwCurr; SaveCache(&chEventDevice); break;
    case 3: mpdwEventPhase1[ibDig] = dwCurr; SaveCache(&chEventPhase1); break;
    case 4: mpdwEventPhase2[ibDig] = dwCurr; SaveCache(&chEventPhase2); break;
    case 5: mpdwEventPhase3[ibDig] = dwCurr; SaveCache(&chEventPhase3); break;
  }
}


void    ReadEventsAllB(uchar  ibCan)
{
  if (mpfEventFlagB[0] == true) {
    ReadEventsB(ibCan, 1);
  }
  if (mpfEventFlagB[1] == true) {
    ReadEventsB(ibCan, 3);
  }
  if (mpfEventFlagB[2] == true) {
    ReadEventsB(ibCan, 4);
  }
  if (mpfEventFlagB[3] == true) {
    ReadEventsB(ibCan, 5);
  }
}
