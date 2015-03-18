/*------------------------------------------------------------------------------
NEXT_DAY.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_energy.h"
#include        "../tariffs/tariffs.h"
#include        "../energy.h"
#include        "../energy2.h"
#include        "../energy3.h"
#include        "../serial/answer.h"
#include        "realtime_storage.h"



void    NextDay(void)
{
  cwDays++;

  MakeCntMonCan();
  MakeAllCurrTariffs();

  SaveCntMonBuff();

  SaveImpDay(0,ibHardDay,ibSoftDay);
  SavePowDay(0,ibHardDay,ibSoftDay);

  if (++ibHardDay >= bDAYS) ibHardDay = 0;
  if (++ibSoftDay >= 2)     ibSoftDay = 0;
  SavePointersDay();

  memset(&mpimDayCan[ibSoftDay], 0, sizeof(impulse)*bCANALS);
  memset(&mppoDayGrp[ibSoftDay], 0, sizeof(power)*bGROUPS);

  EnableAnswer();
}
