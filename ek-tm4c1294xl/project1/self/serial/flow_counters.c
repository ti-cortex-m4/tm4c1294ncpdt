/*------------------------------------------------------------------------------
flow_counters.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "flow_counters.h"



static flow_counter     mwFlowCountersAbs[48],
                        mwFlowCountersDay[48];



void    InitFlowCounters(void)
{
  memset(&mwFlowCountersAbs, 0, sizeof(mwFlowCountersAbs));
  memset(&mwFlowCountersDay, 0, sizeof(mwFlowCountersDay));
}


void    NextDayResetFlowCounters(void)
{
  memset(&mwFlowCountersDay, 0, sizeof(mwFlowCountersDay));
}



void    Timeout35(uint  wTimeout)
{
  uchar i = wTimeout < 0x100 ? wTimeout : 0xFF;

  mwFlowCountersAbs[i]++;
  mwFlowCountersDay[i]++;

  mbTimeoutDelta35[cwTimeoutDelta35++ % DELTA_SIZE] = i;
}



void    OutTimeoutHistogramAll35(void)
{
  InitPushCRC();

  Push(&mwFlowCountersAbs, sizeof(mwFlowCountersAbs));
  Push(&mwFlowCountersDay, sizeof(mwFlowCountersDay));

  Output(sizeof(mwFlowCountersAbs)+sizeof(mwFlowCountersDay));
}


void    OutResetTimeoutHistogramAll35(void)
{
  if (enGlobal == GLB_REPROGRAM)
  {
    InitFlowCounters();
    Result(bRES_OK);
  }
  else
    Result(bRES_NEEDREPROGRAM);
}


void    OutResetTimeoutHistogramDay35(void)
{
  if (enGlobal == GLB_REPROGRAM)
  {
    NextDayResetFlowCounters();
    Result(bRES_OK);
  }
  else
    Result(bRES_NEEDREPROGRAM);
}
