/*------------------------------------------------------------------------------
NEXT_PARAMS_TIME!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_params.h"
#include "realtime.h"
#include "../keyboard/time/key_timedate.h"
#include "../digitals/params/params_storage.h"
#include "realtime_storage.h"



void    NextParamsTime(void)
{
  SaveParamsTim(iwHardTim,ibSoftTim);

  if (++iwHardTim >= wTIMES) iwHardTim = 0;
  if (++ibSoftTim >= 2)      ibSoftTim = 0;
  SavePointersTim();

  memset(&mpreParamsBuff[ibSoftTim], 0xFF, sizeof(float)*wPARAMS);

  if (cwParamTim < wTIMES-1) cwParamTim++;
}

