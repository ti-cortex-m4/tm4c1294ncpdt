/*------------------------------------------------------------------------------
NEXT_DAY.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_tariffs.h"
#include "../memory/mem_energy.h"
#include "../tariffs/tariffs.h"
#include "../energy.h"
#include "../energy2.h"
#include "../kernel/arrays_buff.h"
#include "../digitals/answer.h"
#include "../digitals/extended/extended_4.h"
#include "../digitals/extended/extended_5.h"
#include "../digitals/extended/extended_6.h"
#include "../digitals/extended/extended_7.h"
#include "../special/defects.h"
#include "../special/recalc_def.h"
#include "realtime_storage.h"



void    NextDay(void)
{
  cwDays++;

  NextDayExtended4();
  NextDayExtended5();
  NextDayExtended6();

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

  NextDayExtended7();

  // обработка брака по суткам
  MakeDefectDay(0, tiCurr);

  // обработка достоверности по суткам
  NextDayDef();

  EnableAnswer();
}
