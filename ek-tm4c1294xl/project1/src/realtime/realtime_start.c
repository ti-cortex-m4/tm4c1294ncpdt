/*------------------------------------------------------------------------------
REALTIME_START.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_energy.h"
#include        "../time/rtc.h"
#include        "../impulses/impulses.h"
#include        "../energy.h"
#include        "../digitals/digitals.h"
#include        "../digitals/profile/profile.h"
#include        "realtime_storage.h"



void    StartRealtime(void)
{
uchar    c;
real     re;

  ibSoftMnt = 0;
  ibHardMnt = 0;
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

  tiCurr = *GetCurrTimeDate();
  tiPrev = tiCurr;
  SaveTimeCurr();

  cbSummer = 0;
  cbWinter = 0;

  DisableImpulses();
  memset(&mpwImpMntCan[ibSoftMnt], 0, sizeof(uint)*bCANALS);
  EnableImpulses(); // TODO EnableImpulses

  MakeCurrHouCan();

  for (c=0; c<bCANALS; c++)
  {
    if (GetDigitalDevice(c) == 0)
    {
      re = GetCanReal(mpreCount,c);
      SetCanReal(mpreCntMonCan[ ibSoftMon ], c, &re);
    }
  }
}
