/*------------------------------------------------------------------------------
NEXT_MINUTE3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_params.h"
#include "../energy.h"
#include "../kernel/arrays_buff.h"
#include "../impulses/impulses.h"
#include "../digitals/current/current2.h"
#include "next_params_time.h"
#include "realtime_storage.h"
#include "../nvram/cache.h"
#include "../kernel/array_mnt.h"



static void PrepareImpulses(void)
{
  memcpy(&mpwImpMntCanCurr, &mpwImpMntCan[ibSoftMnt], sizeof(uint)*bCANALS);
  SaveImpMnt(iwHardMnt,ibSoftMnt);

  if (++iwHardMnt >= bMINUTES) iwHardMnt = 0;
  if (++ibSoftMnt >= 2)        ibSoftMnt = 0;
  SavePointersMnt();

  memset(&mpwImpMntCan[ibSoftMnt], 0, sizeof(uint)*bCANALS);
}



void    NextMinute3(void)
{
  Realtime1.cdwMinutes3++;

  DisableImpulses();
  PrepareImpulses();
  EnableImpulses();

  MakeImpulse();

  SaveImpHouBuff();
  SaveImpDayBuff();
  SaveImpMonBuff();
  SaveImpAbsBuff();

  SaveRealtimeTimes(); // TODO another place
  SaveCache(&chRealtimeValues);

  if (boMntParams == true) NextParamsTime();
  NextMntCurrent2();
}


void    NextMinute3Spec(void)
{
  Realtime1.cdwMinutes3++;

  DisableImpulses();
  PrepareImpulses();
  EnableImpulses();

  MakeImpulseSpec();
}
