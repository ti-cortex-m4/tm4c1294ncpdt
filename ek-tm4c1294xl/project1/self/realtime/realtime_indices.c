/*------------------------------------------------------------------------------
realtime_indices.c


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../../memory/mem_settings.h"
//#include "../../serial/ports.h"
#include "realtime_indices.h"



static uint             cwRealtimeIndices;
static realtime_indices mbRealtimeIndices[REALTIME_INDICES_SIZE];



void    InitRealtimeIndices(void)
{
//  memset(&mwTimeoutHistogramAbs35, 0, sizeof(mwTimeoutHistogramAbs35));
//  memset(&mwTimeoutHistogramDay35, 0, sizeof(mwTimeoutHistogramDay35));

  cwRealtimeIndices = 0;
  memset(&mbRealtimeIndices, 0, sizeof(mbRealtimeIndices));
}

/*
void    NextDayResetRealtimeIndices(void)
{
  memset(&mwTimeoutHistogramDay35, 0, sizeof(mwTimeoutHistogramDay35));
}



void    Timeout35(uint  wTimeout)
{
  uchar i = wTimeout < 0x100 ? wTimeout : 0xFF;

  mwTimeoutHistogramAbs35[i]++;
  mwTimeoutHistogramDay35[i]++;

  mbRealtimeIndices[cwRealtimeIndices++ % REALTIME_INDICES_SIZE] = i;
}



uchar   GetRealtimeIndices(void)
{
  uint  w = 0;
  uchar c = 0;

  uchar i;
  for (i=0; i<REALTIME_INDICES_SIZE; i++)
  {
    uchar j = mbRealtimeIndices[(REALTIME_INDICES_SIZE + cwRealtimeIndices - i) % REALTIME_INDICES_SIZE];
    if (j != 0)
    {
      w += j;
      c++;
    }
  }

  return w/c;
}
*/


void    OutRealtimeIndices(void)
{
  InitPushCRC();

//  PushIntLtl(cwRealtimeIndices);
//  Push(&mbRealtimeIndices, sizeof(mbRealtimeIndices));
//  PushChar(GetRealtimeIndices());
//
//  Push(&mwTimeoutHistogramAbs35, sizeof(mwTimeoutHistogramAbs35));
//  Push(&mwTimeoutHistogramDay35, sizeof(mwTimeoutHistogramDay35));
//
//  Output(2+sizeof(mbRealtimeIndices)+1+sizeof(mwTimeoutHistogramAbs35)+sizeof(mwTimeoutHistogramDay35));
}

/*
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
