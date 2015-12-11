/*------------------------------------------------------------------------------
PERIOD30.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "realtime.h"
#include "period30.h"



period30                vPeriod30;
static uint             wPeriod30Idx;
static uint             wSeconds;


static cache const      chPeriod30Idx = {PERIOD30_IDX, &wPeriod30Idx, sizeof(uint)};



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

  wSeconds = 0;
}


void    ResetPeriod30(void)
{
  wPeriod30Idx = 0;
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
    wSeconds++;
  }
}


void    NextHhrPeriod30(void)
{
  if (fActive == true)
  {
    if (wSeconds != 30*60)
    {
      wPeriod30Idx++;
      SaveCache(&chPeriod30Idx);


      vPeriod30.iwIdx = wPeriod30Idx;
      vPeriod30.tiCurr = tiCurr;
      vPeriod30.tiPrev = tiPrev;
      vPeriod30.cwSecond = wSeconds;

      SavePeriod30(wPeriod30Idx);
    }

    wSeconds = 0;
  }
}
