/*------------------------------------------------------------------------------
NEXT_MINUTE30.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_params.h"
#include "../impulses/max_power.h"
#include "../digitals/profile/profile.h"
#include "../digitals/limits.h"
#include "../energy2.h"
#include "../energy3.h"
#include "next_params_time.h"
#include "realtime_storage.h"



void    NextMinute30(void)
{
  cdwMinutes30++;

  MakeMaxPowAll();

  SavePowDayBuff();
  SavePowMonBuff();

  SaveImpHou(0,iwHardHou,ibSoftHou);

  if (++iwHardHou >= wHOURS) iwHardHou = 0;
  if (++ibSoftHou >= 2)      ibSoftHou = 0;
  SavePointersHou();

  memset(&mpwImpHouCan[ibSoftHou], 0, sizeof(uint)*bCANALS);
  MakeCurrHouCan();
  SaveImpHouBuff();

  MakeLimits();
  NextHouLimitsAux();

  if (boMntParams == false) NextParamsTime();
}
