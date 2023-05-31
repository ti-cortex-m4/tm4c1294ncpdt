/*------------------------------------------------------------------------------
realtime_indices.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
#include "realtime_indices.h"



typedef struct
{
  time      tiCurr;

  uchar     ibSoftHou;
  uint      iwHardHou;

  uchar     ibSoftDay;
  uchar     ibHardDay;

  uchar     ibSoftMon;
  uchar     ibHardMon;
} realtime_indices;



#define REALTIME_INDICES_SIZE   (uint)(48*14)



static uint             cwRealtimeIndices;
static realtime_indices mbRealtimeIndices[REALTIME_INDICES_SIZE];



void    InitRealtimeIndices(void)
{
  cwRealtimeIndices = 0;
  memset(&mbRealtimeIndices, 0, sizeof(mbRealtimeIndices));
}


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


void    OutRealtimeIndices(void)
{
  InitPushCRC();

  PushIntLtl(cwRealtimeIndices);
  Push(&mbRealtimeIndices, sizeof(mbRealtimeIndices));

  Output(2+sizeof(mbRealtimeIndices));
}
