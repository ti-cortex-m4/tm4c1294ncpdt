/*------------------------------------------------------------------------------
 OUT_REALTIME,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_params.h"
#include "../memory/mem_diagram.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../time/rtc.h"
#include "out_realtime.h"



void    OutRealtime1(void)
{
  InitPushCRC();
  uint wSize = 0;

  wSize += PushTime(*GetCurrTimeDate());
  wSize += PushTime(tiCurr);
  wSize += PushTime(tiPrev);

  wSize += PushBool(fSeason);
  wSize += PushBool(fSummer);
  wSize += PushBool(fWinter);

  wSize += PushBool(fActive);

  wSize += PushIntBig(ibSoftMnt);
  wSize += PushIntBig(iwHardMnt);
  wSize += PushIntBig(ibSoftHou);
  wSize += PushIntBig(iwHardHou);
  wSize += PushIntBig(ibSoftDay);
  wSize += PushIntBig(ibHardDay);
  wSize += PushIntBig(ibSoftMon);
  wSize += PushIntBig(ibHardMon);
  wSize += PushIntBig(ibSoftTim);
  wSize += PushIntBig(iwHardTim);

  wSize += PushLongBig(Realtime1.cdwSeconds);
  wSize += PushLongBig(Realtime1.cdwMinutes1);
  wSize += PushLongBig(Realtime1.cdwMinutes3);
  wSize += PushLongBig(Realtime1.cdwMinutes30);
  wSize += PushIntBig(Realtime1.cwDays);
  wSize += PushIntBig(Realtime1.cwMonths);
  wSize += PushIntBig(Realtime1.cwYears);

  Output(wSize);
}


void    OutRealtime2(void)
{
  const uchar bRevision = 1;
  const uint wSize = 1000;


  InitPushCRC();

  uint i;
  for (i=0; i<wSize; i++)
    PushChar(0xFF);


  InitPushCRC();

  PushChar(bRevision);

  PushTime(*GetCurrTimeDate());
  PushTime(tiCurr);
  PushTime(tiPrev);

  PushBool(fSeason);
  PushBool(fSummer);
  PushBool(fWinter);

  PushBool(fActive);

  PushIntBig(ibSoftMnt);
  PushIntBig(iwHardMnt);
  PushIntBig(ibSoftHou);
  PushIntBig(iwHardHou);
  PushIntBig(ibSoftDay);
  PushIntBig(ibHardDay);
  PushIntBig(ibSoftMon);
  PushIntBig(ibHardMon);
  PushIntBig(ibSoftTim);
  PushIntBig(iwHardTim);

  PushLongBig(Realtime1.cdwSeconds);
  PushLongBig(Realtime1.cdwMinutes1);
  PushLongBig(Realtime1.cdwMinutes3);
  PushLongBig(Realtime1.cdwMinutes30);
  PushIntBig(Realtime1.cwDays);
  PushIntBig(Realtime1.cwMonths);
  PushIntBig(Realtime1.cwYears);

  PushIntBig(ibSoftDgr);
  PushIntBig(iwHardDgr);

  Output(wSize);
}
