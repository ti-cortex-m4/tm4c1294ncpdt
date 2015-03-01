/*------------------------------------------------------------------------------
NEXT_MINUTE3.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../energy.h"
#include        "../energy3.h"
#include        "../impulses/impulses.h"
#include        "realtime_storage.h"
#include        "../energy2.h"



static void PrepareImpulses(void)
{
  memcpy(&mpwImpMntCanCurr, &mpwImpMntCan[ibSoftMnt], sizeof(uint)*bCANALS);
  SaveImpMnt(0,ibHardMnt,ibSoftMnt);

  if (++ibHardMnt >= bMINUTES) ibHardMnt = 0;
  if (++ibSoftMnt >= 2)        ibSoftMnt = 0;

  memset(&mpwImpMntCan[ibSoftMnt], 0, sizeof(uint)*bCANALS);

  SavePointersMnt();
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
}


void    NextMinute3Spec(void)
{
  cdwMinutes3++;

  DisableImpulses();
  PrepareImpulses();
  EnableImpulses();

  MakeImpulseSpec();
}
