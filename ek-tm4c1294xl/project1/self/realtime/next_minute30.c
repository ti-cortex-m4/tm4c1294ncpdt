/*------------------------------------------------------------------------------
NEXT_MINUTE30!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_params.h"
#include "../serial/input_mode_reset.h"
#include "../impulses/max_power.h"
#include "../digitals/profile/profile.h"
#include "../digitals/extended/diagram.h"
#include "../digitals/limits.h"
#include "../energy2.h"
#include "../kernel/arrays_buff.h"
#include "next_params_time.h"
#include "period30.h"
#include "realtime_indices.h"
#include "realtime_storage.h"



void    NextMinute30(void)
{
  Realtime1.cdwMinutes30++;

  MakeMaxPowAll();

  SavePowDayBuff();
  SavePowMonBuff();

  SaveImpHou(0,iwHardHou,ibSoftHou);

  if (++iwHardHou >= wHOURS) iwHardHou = 0;
  if (++ibSoftHou >= 2)      ibSoftHou = 0;
  SavePointersHou();
  SaveRealtimeIndices();

  memset(&mpwImpHouCan[ibSoftHou], 0, sizeof(uint)*bCANALS);
  MakeCurrHouCan();
  SaveImpHouBuff();

  MakeLimits();
  NextHouLimitsAux();
  NextHouDiagram();
  NextHhrInputModeReset();
  NextHhrPeriod30();

  if (boMntParams == false) NextParamsTime();
}
