/*------------------------------------------------------------------------------
REALTIME_START.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_energy.h"
#include        "../rtc.h"
#include        "../impulses/impulses.h"
#include        "../energy.h"
#include        "../digitals/digitals.h"
#include        "../digitals/profile.h"



void    StartRealtime(void)
{
uchar    c;
real     re;

  ibSoftMnt = 0;

  ibSoftHou = 0;
  iwHardHou = 0;

  ibSoftDay = 0;
  ibHardDay = 0;

  ibSoftMon = 0;
  ibHardMon = (GetCurrTimeDate()->bMonth) - 1;

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
