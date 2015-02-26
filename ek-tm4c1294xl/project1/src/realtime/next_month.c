/*------------------------------------------------------------------------------
NEXT_MONTH.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_energy.h"
#include        "../energy.h"
#include        "../energy2.h"
#include        "realtime_storage.h"



void    NextMonth(void)
{
  cwMonths++;

  SaveImpMon(0,ibHardMon,ibSoftMon);
  SavePowMon(0,ibHardMon,ibSoftMon);
  SaveCntMon(0,ibHardMon,ibSoftMon);

  if (++ibHardMon >= bMONTHS) ibHardMon = 0;
  if (++ibSoftMon >= 2)       ibSoftMon = 0;
  SavePointersMon();

  memset(&mpimMonCan[ibSoftMon],    0, sizeof(impulse)*bCANALS);
  memset(&mppoMonGrp[ibSoftMon],    0, sizeof(power)*bGROUPS);
  memset(&mpreCntMonCan[ibSoftMon], 0, sizeof(real)*bCANALS);

  MakeCntMonCan();
}
