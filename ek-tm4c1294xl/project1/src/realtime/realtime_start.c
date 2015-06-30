/*------------------------------------------------------------------------------
REALTIME_START.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_params.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_energy.h"
#include "../time/rtc.h"
#include "../impulses/impulses.h"
#include "../energy.h"
#include "../kernel/arrays_buff.h"
#include "../digitals/digitals.h"
#include "../digitals/profile/profile.h"
#include "realtime_storage.h"



void    StartRealtime(void)
{
  ibSoftMnt = 0;
  iwHardMnt = 0;
  SavePointersMnt();

  ibSoftHou = 0;
  iwHardHou = 0;
  SavePointersHou();

  ibSoftDay = 0;
  ibHardDay = 0;
  SavePointersDay();

  ibSoftMon = 0;
  ibHardMon = (GetCurrTimeDate()->bMonth) - 1;
  SavePointersMon();

  ibSoftTim = 0;
  iwHardTim = 0;
  SavePointersTim();

  tiCurr = *GetCurrTimeDate();
  tiPrev = tiCurr;
  SaveTimeCurr();

  cbSummer = 0;
  cbWinter = 0;

  DisableImpulses();
  memset(&mpwImpMntCan[ibSoftMnt], 0, sizeof(uint)*bCANALS);
  EnableImpulses(); // TODO EnableImpulses

  memset(&mpwImpHouCan[ibSoftHou], 0, sizeof(uint)*bCANALS);
  MakeCurrHouCan();
  SaveImpHouBuff();

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (GetDigitalDevice(c) == 0)
    {
      mpdbCntMonCan[ibSoftMon][c] = mpdbCount[c];
    }
  }
}
