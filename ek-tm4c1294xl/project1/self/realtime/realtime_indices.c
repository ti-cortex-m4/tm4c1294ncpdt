/*------------------------------------------------------------------------------
realtime_indices.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
#include "../time/bcd_time.h"
#include "realtime_indices.h"



typedef struct
{
  ulong     dwCurr;
  ulong     dwIndices;
} realtime_indices;



#define REALTIME_INDICES_DAYS   1
#define REALTIME_INDICES_SIZE   (uint)(48*REALTIME_INDICES_DAYS)



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

  ri.dwCurr = TimeToBcdTime(tiCurr);

  ulong dw = 0;

  dw |= (ibSoftHou & 0x03);
  dw |= (iwHardHou & 0xFFF) << 2;

  dw |= (ibSoftDay & 0x03) << (2+12);
  dw |= (ibHardDay & 0x1F) << (2+12+2);

  dw |= (ibSoftMon & 0x03) << (2+12+2+5);
  dw |= (ibHardMon & 0x1F) << (2+12+2+5+2);

  ri.dwIndices = dw;

  mbRealtimeIndices[cwRealtimeIndices++ % REALTIME_INDICES_SIZE] = ri;
}


void    OutRealtimeIndices(void)
{
  InitPushCRC();

  if (bInBuff5 < REALTIME_INDICES_DAYS)
  {
    uint wSize = 0;
    wSize += PushIntLtl(cwRealtimeIndices);

    uint i;
    for (i=0; i<REALTIME_INDICES_SIZE; i++)
    {
      realtime_indices ri = mbRealtimeIndices[i + (uint)(48*bInBuff5)];

      wSize += PushLongLtl(ri.dwCurr);
      wSize += PushLongLtl(ri.dwIndices);
    }

    Output(wSize);
  }
  else Result(bRES_BADADDRESS);
}
