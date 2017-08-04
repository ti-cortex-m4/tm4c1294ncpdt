/*------------------------------------------------------------------------------
OUT_DEFECTS1,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../serial/ports.h"
#include "out_defects1.h"



void    OutDefectsDay(void)
{
  InitPushCRC();
  PushChar(ibHardDay);
  Push(&mpdeDay, sizeof(mpdeDay));
  Output(1 + sizeof(mpdeDay));
}


void    OutDefectsMon(void)
{
  InitPushCRC();
  PushChar(ibHardMon);
  Push(&mpdeMon, sizeof(mpdeMon));
  Output(1 + sizeof(mpdeMon));
}
