/*------------------------------------------------------------------------------
PERIOD30.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../serial/ports.h"
#include "../time/rtc.h"
#include "realtime.h"
#include "period30.h"



static uint             iwPeriod30Idx;
static uint             cwSeconds;


static cache const      chPeriod30Idx = {PERIOD30_IDX, &iwPeriod30Idx, sizeof(uint)};



static bool SavePeriod30(uint  wIdx, period30  *pv)
{
  ASSERT(wIdx < PERIOD30_SIZE);
  return SaveArrayX(PERIOD30_VALUES, sizeof(period30), wIdx, pv);
}


static bool LoadPeriod30(uint  wIdx, period30  *pv)
{
  ASSERT(wIdx < PERIOD30_SIZE);
  return LoadArrayX(PERIOD30_VALUES, sizeof(period30), wIdx, pv);
}



void    InitPeriod30(void)
{
  LoadCache(&chPeriod30Idx);

  cwSeconds = 0;
}


void    ResetPeriod30(void)
{
  SaveCacheInt(&chPeriod30Idx, 0);


  period30 v;
  memset(&v, 0, sizeof(v));

  uint i;
  for (i=0; i<PERIOD30_SIZE; i++)
  {
    SavePeriod30(i, &v);
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
      static period30 v;
      v.iwIdx = iwPeriod30Idx;
      v.tiPrev = tiPrev;
      v.tiCurr = tiCurr;
      v.tiRTC = *GetCurrTimeDate();
      v.cwSeconds = cwSeconds;

      SavePeriod30(iwPeriod30Idx % PERIOD30_SIZE, &v);


      iwPeriod30Idx++;
      SaveCache(&chPeriod30Idx);
    }

    cwSeconds = 0;
  }
}



static uint PushPeriod30(period30  *pv)
{
  uchar bSize = 0;

  bSize += PushIntBig(pv->iwIdx);
  bSize += PushTime(pv->tiPrev);
  bSize += PushTime(pv->tiCurr);
  bSize += PushTime(pv->tiRTC);
  bSize += PushIntBig(pv->cwSeconds);

  return bSize;
}


void    OutPeriod30(void)
{
  InitPushCRC();
  uint wSize = 0;

  wSize += PushIntBig(iwPeriod30Idx);

  uint i;
  for (i=0; i<PERIOD30_SIZE; i++)
  {
    static period30 v;
    LoadPeriod30(i, &v);
    wSize += PushPeriod30(&v);
  }

  Output(wSize);
}
