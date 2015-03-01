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



void    NextMinute3(void)
{
  cdwMinutes3++;

  memset(&mpwImpMntCan[(ibSoftMnt+1) % bMINUTES], 0, sizeof(uint)*bCANALS); // TODO Init/Reset mpwImpMntCan

  DisableImpulses();
  memcpy(&mpwImpMntCanCurr, &mpwImpMntCan1[ibSoftMnt], sizeof(uint)*bCANALS);
  if (++ibHardMnt >= bMINUTES) ibHardMnt = 0;
  if (++ibSoftMnt >= 2)        ibSoftMnt = 0;
  SavePointersMnt();
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

  memset(&mpwImpMntCan[(ibSoftMnt+1) % bMINUTES], 0, sizeof(uint)*bCANALS); // TODO Init/Reset mpwImpMntCan

  DisableImpulses();
  memcpy(&mpwImpMntCanCurr, &mpwImpMntCan1[ibSoftMnt], sizeof(uint)*bCANALS);
  if (++ibHardMnt >= bMINUTES) ibHardMnt = 0;
  if (++ibSoftMnt >= 2)        ibSoftMnt = 0;

  EnableImpulses();

  MakeImpulseSpec();
}
