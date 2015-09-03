/*------------------------------------------------------------------------------
EXTENDED_3.C


------------------------------------------------------------------------------*/

#include "../../main.h"



//                                         0123456789ABCDEF
static char const       szEventsAll[]  =  "События         ";



void    ResetExtended3(void) {
uchar i;

  for (i=0; i<bCANALS; i++) {
    mpboEventFirst[i] = boTrue;
    mpdwEventDevice[i] = 0;
    mpdwEventPhase1[i] = 0;
    mpdwEventPhase2[i] = 0;
    mpdwEventPhase3[i] = 0;
  }

  boExt3Flag = boFalse;

  for (i=0; i<sizeof(mpboEventA); i++) 
    mpboEventA[i] = boFalse;

  for (i=0; i<sizeof(mpboEventB); i++) 
    mpboEventB[i] = boFalse;
}


void    ResetExtended3_Full(void) {
uchar i;

  for (i=0; i<bCANALS; i++) {
    mpboEventFirst[i] = boTrue;
    mpdwEventDevice[i] = 0;
    mpdwEventPhase1[i] = 0;
    mpdwEventPhase2[i] = 0;
    mpdwEventPhase3[i] = 0;
  }

  wPageOut=wFLA_IMPRECORD;
  for (i=0; i<bRECORD_SIZE; i++) {
    SafePageErase();
    wPageOut++;
  }
}



ulong   DateToEveIndex(void)
{
uchar   i;

  dwBuffC = 0;

  if ((tiAlt.bYear   == 0) &&
      (tiAlt.bMonth  == 0) &&
      (tiAlt.bDay    == 0) &&
      (tiAlt.bHour   == 0) &&
      (tiAlt.bMinute == 0) &&
      (tiAlt.bSecond == 0)) return dwBuffC;   // обрабатывать и неправильный форматы даты ?

  for (i=0; i<tiAlt.bYear; i++)
    dwBuffC += DaysInYearSpec(i);

  for (i=1; i<tiAlt.bMonth; i++)
    dwBuffC += DaysInMonthSpec(tiAlt.bYear,i);

  dwBuffC += tiAlt.bDay-1;
  dwBuffC *= 24;
  dwBuffC += tiAlt.bHour;
  dwBuffC *= 60;
  dwBuffC += tiAlt.bMinute;
  dwBuffC *= 60;
  dwBuffC += tiAlt.bSecond;

  return(dwBuffC);
}


#ifndef MODBUS

void    EveIndexToDate(ulong  dwT)
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
  
  tiAlt.bDay = dwT/86400; 
  dwT -= (ulong)86400*tiAlt.bDay;
  tiAlt.bDay++;

  tiAlt.bHour = dwT/3600; 
  dwT -= (ulong)3600*tiAlt.bHour;  

  tiAlt.bMinute = dwT/60; 
  tiAlt.bSecond = dwT%60;
}

#endif


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
  InitPush();

  PushChar(diCurr.bAddress);           
  PushChar(4);                       

  PushChar((ibEvent << 4) | j);

  QueryIO(1+14+2, 2+1+2);
}


bit     QueryEventA_Full(uchar  ibEvent, uchar  j, uchar  bPercent)
{
uchar   i;

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


void    ReadEventA(void)
{
  tiAlt.bSecond = FromBCD( PopChar() );
  tiAlt.bMinute = FromBCD( PopChar() );
  tiAlt.bHour   = FromBCD( PopChar() );
  PopChar();
  tiAlt.bDay    = FromBCD( PopChar() );
  tiAlt.bMonth  = FromBCD( PopChar() );
  tiAlt.bYear   = FromBCD( PopChar() );
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
uchar i,j,k;
 
  ShowEventsA(ibEvent);

  if (QueryOpenA_Full(25) == 0) { bEventCode = 0; AddImpRecord(EVE_EVENTS_BADLINK); return; }

  for (i=0; i<10; i++)
  {
    if (QueryEventA_Full(ibEvent,i,50) == 0) {  bEventCode = i+1; AddImpRecord(EVE_EVENTS_BADLINK); return; }

    InitPop(1);
    ReadEventA(); mptiEventAB1[i] = tiAlt;
    ReadEventA(); mptiEventAB2[i] = tiAlt;
  } 

  switch (ibEvent) {
    case 1: dwPrev = mpdwEventDevice[ibDig]; break;
    case 7: dwPrev = mpdwEventPhase1[ibDig]; break;
    case 8: dwPrev = mpdwEventPhase2[ibDig]; break;
    case 9: dwPrev = mpdwEventPhase3[ibDig]; break;
  }

  dwCurr = 0;
  boAlt = boFalse;
  for (i=0; i<10; i++)
  {
    tiAlt = mptiEventAB1[i];
    if (dwPrev == DateToEveIndex()) boAlt = boTrue;
    if (dwCurr < DateToEveIndex()) {
      dwCurr = DateToEveIndex();
      j = i;
    }

    tiAlt = mptiEventAB2[i];
    if (dwPrev == DateToEveIndex()) boAlt = boTrue;
    if (dwCurr < DateToEveIndex()) {
      dwCurr = DateToEveIndex();
      j = i;
    }
  }

  if (dwCurr == 0) AddImpRecord(EVE_EVENTS_BADDATA);
  if ((boAlt == boFalse) && (mpboEventFirst[ibDig] == boTrue)) { bEventCode = GetEventCodeA(ibEvent); AddImpRecord(EVE_EVENTS_OMISSION); }

  for (i=0; i<10; i++) {
    k = (10 + j + i + 1) % 10;
    tiAlt = mptiEventAB1[k];
    if (dwPrev < DateToEveIndex()) {
      bEventCode = GetEventCodeA(ibEvent) | 0x80;   // внимание !
      AddImpRecord(EVE_EVENTS_A);
    }
    tiAlt = mptiEventAB2[k];
    if (dwPrev < DateToEveIndex()) {
      bEventCode = GetEventCodeA(ibEvent);
      AddImpRecord(EVE_EVENTS_A);
    }
  }   

  switch (ibEvent) {
    case 1: mpdwEventDevice[ibDig] = dwCurr; break;
    case 7: mpdwEventPhase1[ibDig] = dwCurr; break;
    case 8: mpdwEventPhase2[ibDig] = dwCurr; break;
    case 9: mpdwEventPhase3[ibDig] = dwCurr; break;
  }
}


void    ReadEventsAllA(void)
{
  if (mpboEventA[0] == boTrue) {
    ReadEventsA(1);
  }
  if (mpboEventA[1] == boTrue) {
    ReadEventsA(7);
  }
  if (mpboEventA[2] == boTrue) {
    ReadEventsA(8);
  }
  if (mpboEventA[3] == boTrue) {
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
  InitPush();

  PushChar(diCurr.bAddress);           
  PushChar(4);                       

  PushChar(ibEvent);
  PushChar(j);

  QueryIO(1+12+2, 2+2+2);
}


bit     QueryEventB_Full(uchar  ibEvent, uchar  j, uchar  bPercent)
{
uchar   i;

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


void    ReadEventB(void)
{
  tiAlt.bSecond = FromBCD( PopChar() );
  tiAlt.bMinute = FromBCD( PopChar() );
  tiAlt.bHour   = FromBCD( PopChar() );
  tiAlt.bDay    = FromBCD( PopChar() );
  tiAlt.bMonth  = FromBCD( PopChar() );
  tiAlt.bYear   = FromBCD( PopChar() );
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
uchar i,j,k;
 
  ShowEventsB(ibEvent);

  if (QueryOpenB_Full(25) == 0) { bEventCode = 0; AddImpRecord(EVE_EVENTS_BADLINK); return; }

  for (i=0; i<10; i++)
  {
    if (QueryEventB_Full(ibEvent,i,50) == 0) {  bEventCode = i+1; AddImpRecord(EVE_EVENTS_BADLINK); return; }

    InitPop(1);
    ReadEventB(); mptiEventAB1[i] = tiAlt;
    ReadEventB(); mptiEventAB2[i] = tiAlt;
  } 

  switch (ibEvent) {
    case 1: dwPrev = mpdwEventDevice[ibDig]; break;
    case 3: dwPrev = mpdwEventPhase1[ibDig]; break;
    case 4: dwPrev = mpdwEventPhase2[ibDig]; break;
    case 5: dwPrev = mpdwEventPhase3[ibDig]; break;
  }

  dwCurr = 0;
  boAlt = boFalse;
  for (i=0; i<10; i++)
  {
    tiAlt = mptiEventAB1[i];
    if (dwPrev == DateToEveIndex()) boAlt = boTrue;
    if (dwCurr < DateToEveIndex()) {
      dwCurr = DateToEveIndex();
      j = i;
    }

    tiAlt = mptiEventAB2[i];
    if (dwPrev == DateToEveIndex()) boAlt = boTrue;
    if (dwCurr < DateToEveIndex()) {
      dwCurr = DateToEveIndex();
      j = i;
    }
  }

  if (dwCurr == 0) AddImpRecord(EVE_EVENTS_BADDATA);
  if ((boAlt == boFalse) && (mpboEventFirst[ibDig] == boTrue)) { bEventCode = GetEventCodeB(ibEvent); AddImpRecord(EVE_EVENTS_OMISSION); }

  for (i=0; i<10; i++) {
    k = (10 + j + i + 1) % 10;
    tiAlt = mptiEventAB1[k];
    if (dwPrev < DateToEveIndex()) {
      bEventCode = GetEventCodeB(ibEvent);
      AddImpRecord(EVE_EVENTS_B);
    }
    tiAlt = mptiEventAB2[k];
    if (dwPrev < DateToEveIndex()) {
      bEventCode = GetEventCodeB(ibEvent) | 0x80;   // внимание !
      AddImpRecord(EVE_EVENTS_B);
    }
  }   

  switch (ibEvent) {
    case 1: mpdwEventDevice[ibDig] = dwCurr; break;
    case 3: mpdwEventPhase1[ibDig] = dwCurr; break;
    case 4: mpdwEventPhase2[ibDig] = dwCurr; break;
    case 5: mpdwEventPhase3[ibDig] = dwCurr; break;
  }
}


void    ReadEventsAllB(void)
{
  if (mpboEventB[0] == boTrue) {
    ReadEventsB(1);
  }
  if (mpboEventB[1] == boTrue) {
    ReadEventsB(3);
  }
  if (mpboEventB[2] == boTrue) {
    ReadEventsB(4);
  }
  if (mpboEventB[3] == boTrue) {
    ReadEventsB(5);
  }
}



void    MakeExtended3(void)
{
  if (boExt3Flag == boTrue)
  {
    ShowHi(szEventsAll); Clear();
    sprintf(szLo+14,"%2bu",ibDig+1); DelayInf();

    switch (diCurr.bDevice)
    {
      case 1:  ReadEventsAllA();  break;
      case 2:  ReadEventsAllB();  break;
    }
    
    mpboEventFirst[ibDig] = boFalse;
  }
}



void    OutExtended30(void)
{
  InitPushCRC();
  PushChar(boExt3Flag);
  Push(&mpboEventFirst, sizeof(mpboEventFirst));
  Push(&mpboEventA, sizeof(mpboEventA));
  Push(&mpboEventB, sizeof(mpboEventB));
  Output(1+64+32+32);
}


void    OutExtended31(void)
{
uchar   i,j;

  j = bInBuff6;
  if (j > 3) 
    Result(bRES_BADADDRESS);
  else {  
    InitPushPtr();
    wBuffD = 0;

    for (i=0; i<bCANALS; i++) {
      switch (j) {
        case 0: dwBuffC = mpdwEventDevice[i]; break;
        case 1: dwBuffC = mpdwEventPhase1[i]; break;
        case 2: dwBuffC = mpdwEventPhase2[i]; break;
        case 3: dwBuffC = mpdwEventPhase3[i]; break;
      }

      Push(&dwBuffC, sizeof(ulong));
      EveIndexToDate(dwBuffC);
      Push(&tiAlt, sizeof(time));

      wBuffD += 10;
    }

    OutptrOutBuff(wBuffD);
  }
}

