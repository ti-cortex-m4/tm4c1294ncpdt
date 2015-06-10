/*------------------------------------------------------------------------------
NEXT_MINUTE3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_params.h"
#include "../energy.h"
#include "../energy3.h"
#include "../impulses/impulses.h"
#include "next_params_time.h"
#include "realtime_storage.h"
#include "../energy2.h"



static void PrepareImpulses(void)
{
  memcpy(&mpwImpMntCanCurr, &mpwImpMntCan[ibSoftMnt], sizeof(uint)*bCANALS);
  SaveImpMnt(0,iwHardMnt,ibSoftMnt);

  if (++iwHardMnt >= bMINUTES) iwHardMnt = 0;
  if (++ibSoftMnt >= 2)        ibSoftMnt = 0;
  SavePointersMnt();

  memset(&mpwImpMntCan[ibSoftMnt], 0, sizeof(uint)*bCANALS);
}



void    NextMinute3(void)
{
  cdwMinutes3++;

  DisableImpulses();
  PrepareImpulses();
  EnableImpulses();

  MakeImpulse();

  SaveImpHouBuff();
  SaveImpDayBuff();
  SaveImpMonBuff();
  SaveImpAbsBuff();

  SaveTimeCurr(); // TODO another place

  if (boMntParams == true) NextParamsTime();
}


void    NextMinute3Spec(void)
{
  cdwMinutes3++;

  DisableImpulses();
  PrepareImpulses();
  EnableImpulses();

  MakeImpulseSpec();
}
