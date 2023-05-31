/*------------------------------------------------------------------------------
realtime_indices.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../serial/ports.h"
#include "realtime_indices.h"


/*
static uint             mwTimeoutHistogramAbs35[0x100],
                        mwTimeoutHistogramDay35[0x100];



#define DELTA_SIZE      10

static uint             cwTimeoutDelta35;
static uchar            mbTimeoutDelta35[DELTA_SIZE];



void    InitRealtimeIndices(void)
{
  memset(&mwTimeoutHistogramAbs35, 0, sizeof(mwTimeoutHistogramAbs35));
  memset(&mwTimeoutHistogramDay35, 0, sizeof(mwTimeoutHistogramDay35));

  cwTimeoutDelta35 = 0;
  memset(&mbTimeoutDelta35, 0, sizeof(mbTimeoutDelta35));
}


void    NextDayResetRealtimeIndices(void)
{
  memset(&mwTimeoutHistogramDay35, 0, sizeof(mwTimeoutHistogramDay35));
}



void    Timeout35(uint  wTimeout)
{
  uchar i = wTimeout < 0x100 ? wTimeout : 0xFF;

  mwTimeoutHistogramAbs35[i]++;
  mwTimeoutHistogramDay35[i]++;

  mbTimeoutDelta35[cwTimeoutDelta35++ % DELTA_SIZE] = i;
}



uchar   GetTimeoutDelta35(void)
{
  uint  w = 0;
  uchar c = 0;

  uchar i;
  for (i=0; i<DELTA_SIZE; i++)
  {
    uchar j = mbTimeoutDelta35[(DELTA_SIZE + cwTimeoutDelta35 - i) % DELTA_SIZE];
    if (j != 0)
    {
      w += j;
      c++;
    }
  }

  return w/c;
}



void    OutTimeoutHistogramAll35(void)
{
  InitPushCRC();

  PushIntLtl(cwTimeoutDelta35);
  Push(&mbTimeoutDelta35, sizeof(mbTimeoutDelta35));
  PushChar(GetTimeoutDelta35());

  Push(&mwTimeoutHistogramAbs35, sizeof(mwTimeoutHistogramAbs35));
  Push(&mwTimeoutHistogramDay35, sizeof(mwTimeoutHistogramDay35));

  Output(2+sizeof(mbTimeoutDelta35)+1+sizeof(mwTimeoutHistogramAbs35)+sizeof(mwTimeoutHistogramDay35));
}


void    OutResetTimeoutHistogramAll35(void)
{
  if (enGlobal == GLB_REPROGRAM)
  {
    InitRealtimeIndices();
    Result(bRES_OK);
  }
  else
    Result(bRES_NEEDREPROGRAM);
}


void    OutResetTimeoutHistogramDay35(void)
{
  if (enGlobal == GLB_REPROGRAM)
  {
    NextDayResetRealtimeIndices();
    Result(bRES_OK);
  }
  else
    Result(bRES_NEEDREPROGRAM);
}
*/
