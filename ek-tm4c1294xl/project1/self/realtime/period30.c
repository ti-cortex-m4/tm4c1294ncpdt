/*------------------------------------------------------------------------------
PERIOD30.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "realtime.h"
#include "period30.h"


#define VALUE1_IDX      0
#define VALUE1_VALUES   0



static ulong            dwPeriod30Idx;
static uint             wPeriod30Seconds;
static period30         mpPeriod30;


cache const             chPeriod30Idx = {VALUE1_IDX, &dwPeriod30Idx, sizeof(ulong)};



bool    SavePeriod30(uint  i)
{
  return SaveArrayX(VALUE1_VALUES, sizeof(mpPeriod30), i, &mpPeriod30);
}


bool    LoadPeriod30(uint  i)
{
  return LoadArrayX(VALUE1_VALUES, sizeof(mpPeriod30), i, &mpPeriod30);
}



void    InitPeriod30(void)
{
  LoadCache(&chPeriod30Idx);
  wPeriod30Seconds = 0;
}


void    ResetPeriod30(void)
{
  dwPeriod30Idx = 0;
  SaveCache(&chPeriod30Idx);


  memset(&mpPeriod30, 0, sizeof(mpPeriod30));

  uchar i;
  for (i=0; i<PERIOD30_SIZE; i++)
  {
    SavePeriod30(i);
  }
}



void    NextSecPeriod30(void)
{
  if (fActive == true)
  {
    wPeriod30Seconds = 0;
  }
}


void    NextHhrPeriod30(void)
{
  if ((fActive == true) && (wPeriod30Seconds != 30*60))
  {
    dwPeriod30Idx++;
    SaveCache(&chPeriod30Idx);


    memset(&mpPeriod30, 0, sizeof(mpPeriod30));
    mpPeriod30.iwIdx = dwPeriod30Idx;
    mpPeriod30.tiCurr = tiCurr;
    mpPeriod30.tiPrev = tiPrev;
    mpPeriod30.cwSecond = wPeriod30Seconds;

    SavePeriod30(dwPeriod30Idx);

    wPeriod30Seconds = 0;
  }
}
