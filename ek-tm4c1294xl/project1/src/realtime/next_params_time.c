/*------------------------------------------------------------------------------
NEXT_PARAMS_TIME.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_params.h"
#include "realtime.h"
#include "../keyboard/key_timedate.h"
#include "../digitals/params/params_storage.h"
#include "realtime_storage.h"



void    NextParamsTime(void)
{
  SavePrmTim(iwHardTim,ibSoftTim);

  if (++iwHardTim >= wTIMES) iwHardTim = 0;
  if (++ibSoftTim >= 2)      ibSoftTim = 0;
  SavePointersTim();

  memset(&mpreParBuff[ibSoftTim], 0xFF, sizeof(real)*wPARAMS);

  if (cwParamTim < wTIMES-1) cwParamTim++;
}

