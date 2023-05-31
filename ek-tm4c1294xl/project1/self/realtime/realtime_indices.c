/*------------------------------------------------------------------------------
realtime_indices.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
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
*/


void    SaveRealtimeIndices(void)
{
  realtime_indices ri;

  ri.tiCurr = tiCurr;

  ri.ibSoftHou = ibSoftHou;
  ri.iwHardHou = iwHardHou;

  ri.ibSoftDay = ibSoftDay;
  ri.ibHardDay = ibHardDay;

  ri.ibSoftMon = ibSoftMon;
  ri.ibHardMon = ibHardMon;

  mbRealtimeIndices[cwRealtimeIndices++ % REALTIME_INDICES_SIZE] = ri;
}
/*


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

  PushIntLtl(cwRealtimeIndices);
  Push(&mbRealtimeIndices, sizeof(mbRealtimeIndices));
//  PushChar(GetRealtimeIndices());
//
//  Push(&mwTimeoutHistogramAbs35, sizeof(mwTimeoutHistogramAbs35));
//  Push(&mwTimeoutHistogramDay35, sizeof(mwTimeoutHistogramDay35));

  Output(2+sizeof(mbRealtimeIndices));
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
