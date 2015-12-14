/*------------------------------------------------------------------------------
PERIOD30.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../serial/ports.h"
#include "../time/rtc.h"
#include "realtime.h"
#include "period30.h"



period30                vPeriod30;
static uint             iwPeriod30Idx;
static uint             cwSeconds;


static cache const      chPeriod30Idx = {PERIOD30_IDX, &iwPeriod30Idx, sizeof(uint)};



static bool SavePeriod30(uint  wIdx)
{
  return SaveArrayX(PERIOD30_VALUES, sizeof(vPeriod30), wIdx, &vPeriod30);
}


static bool LoadPeriod30(uint  wIdx)
{
  return LoadArrayX(PERIOD30_VALUES, sizeof(vPeriod30), wIdx, &vPeriod30);
}



void    InitPeriod30(void)
{
  LoadCache(&chPeriod30Idx);

  cwSeconds = 0;
}


void    ResetPeriod30(void)
{
  iwPeriod30Idx = 0;
  SaveCache(&chPeriod30Idx);


  memset(&vPeriod30, 0, sizeof(vPeriod30));

  uint i;
  for (i=0; i<PERIOD30_SIZE; i++)
  {
    SavePeriod30(i);
  }
}



void    NextSecPeriod30(void)
{
  if (fActive == true)
  {
    cwSeconds++;
  }
}


void    NextHhrPeriod30(void)
{
  if (fActive == true)
  {
    if (cwSeconds != 30*60)
    {
      iwPeriod30Idx++;
      SaveCache(&chPeriod30Idx);


      vPeriod30.iwIdx = iwPeriod30Idx;
      vPeriod30.tiPrev = tiPrev;
      vPeriod30.tiCurr = tiCurr;
      vPeriod30.tiRTC = *GetCurrTimeDate();
      vPeriod30.cwSeconds = cwSeconds;

      SavePeriod30(iwPeriod30Idx);
    }

    cwSeconds = 0;
  }
}



uint    PushPeriod30()
{
  uchar bSize = 0;

  bSize += PushIntBig(vPeriod30.iwIdx);
  bSize += PushTime(vPeriod30.tiPrev);
  bSize += PushTime(vPeriod30.tiCurr);
  bSize += PushTime(vPeriod30.tiRTC);
  bSize += PushIntBig(vPeriod30.cwSeconds);

  return bSize;
}


void    OutPeriod30(void)
{
  InitPushCRC();
  uint wSize = 0;

  uint i;
  for (i=0; i<PERIOD30_SIZE; i++)
  {
    LoadPeriod30(i);
    wSize += PushPeriod30();
  }

  Output(wSize);
}
