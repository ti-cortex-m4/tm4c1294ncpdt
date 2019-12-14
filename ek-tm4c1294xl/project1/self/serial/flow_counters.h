/*------------------------------------------------------------------------------
flow_counters.h


------------------------------------------------------------------------------*/

#ifndef __FLOW_COUNTERS
#define __FLOW_COUNTERS


typedef struct
{
  uint      wInPackets;
  ulong     dwInBytes;
  uint      wOutPackets;
  ulong     dwOutBytes;
} flow_counter;


#endif


void    InitFlowCounters(void);
void    NextDayResetFlowCounters(void);

void    Timeout35(uint  wTimeout);

uchar   GetTimeoutDelta35(void);

void    OutTimeoutHistogramAll35(void);
void    OutResetTimeoutHistogramAll35(void);
void    OutResetTimeoutHistogramDay35(void);
