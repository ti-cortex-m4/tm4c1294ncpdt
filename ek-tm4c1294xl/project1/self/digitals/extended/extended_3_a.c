/*------------------------------------------------------------------------------
EXTENDED_3_A!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_extended_3.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../sensors/automatic_a.h"
#include "../../flash/records.h"
#include "extended_3.h"
#include "extended_3_a.h"



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
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEventA(ibEvent,j);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
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
uchar j;
ulong dwCurr, dwPrev;
 
  ShowEventsA(ibEvent);

  if (QueryOpenA_Full(25) == 0) { bEventCode = 0; AddImpRecord(EVE_EVENTS_BADLINK); return; }

  uchar i;
  for (i=0; i<10; i++)
  {
    if (QueryEventA_Full(ibEvent,i,50) == 0) {  bEventCode = i+1; AddImpRecord(EVE_EVENTS_BADLINK); return; }

    InitPop(1);
    mptiEventAB1[i] = ReadEventA();
    mptiEventAB2[i] = ReadEventA();
  } 

  switch (ibEvent) {
    case 1: dwPrev = mpdwEventDevice[ibDig]; break;
    case 7: dwPrev = mpdwEventPhase1[ibDig]; break;
    case 8: dwPrev = mpdwEventPhase2[ibDig]; break;
    case 9: dwPrev = mpdwEventPhase3[ibDig]; break;
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
  if ((f == false) && (mpfEventStart[ibDig] == true)) { bEventCode = GetEventCodeA(ibEvent); AddImpRecord(EVE_EVENTS_OMISSION); }

  for (i=0; i<10; i++)
  {
    uchar k = (10 + j + i + 1) % 10;

    time ti = mptiEventAB1[k];
    if (dwPrev < DateToEventIndex(ti))
    {
      tiRecordTime = ti;
      bEventCode = GetEventCodeA(ibEvent) | 0x80; // внимание !
      AddImpRecord(EVE_EVENTS_A);
    }

    ti = mptiEventAB2[k];
    if (dwPrev < DateToEventIndex(ti))
    {
      tiRecordTime = ti;
      bEventCode = GetEventCodeA(ibEvent);
      AddImpRecord(EVE_EVENTS_A);
    }
  }   

  switch (ibEvent) {
    case 1: mpdwEventDevice[ibDig] = dwCurr; SaveCache(&chEventDevice); break;
    case 7: mpdwEventPhase1[ibDig] = dwCurr; SaveCache(&chEventPhase1); break;
    case 8: mpdwEventPhase2[ibDig] = dwCurr; SaveCache(&chEventPhase2); break;
    case 9: mpdwEventPhase3[ibDig] = dwCurr; SaveCache(&chEventPhase3); break;
  }
}


void    ReadEventsAllA(void)
{
  if (mpfEventFlagA[0] == true) {
    ReadEventsA(1);
  }
  if (mpfEventFlagA[1] == true) {
    ReadEventsA(7);
  }
  if (mpfEventFlagA[2] == true) {
    ReadEventsA(8);
  }
  if (mpfEventFlagA[3] == true) {
    ReadEventsA(9);
  }
}
