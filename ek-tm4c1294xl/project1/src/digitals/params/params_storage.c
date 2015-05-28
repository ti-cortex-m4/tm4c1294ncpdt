/*------------------------------------------------------------------------------
PARAMS_STORAGE,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../realtime/realtime.h"
#include "../../flash/files.h"
#include "params_storage.h"



bool SaveParamsTim(uint  iwTimTo, uint  iwTimFrom)
{
  return SaveBuff(PARAMS_VALUES + iwTimTo*PARAMS_PAGES, mpreParamsBuff[ iwTimFrom ], sizeof(float)*wPARAMS);
}


bool LoadParamsTim(uint  iwTimFrom)
{
  if (iwTimFrom == iwHardTim)
  { 
    memcpy(mpreParamsBuff[ PrevSoftTim() ], mpreParamsBuff[ ibSoftTim ], sizeof(float)*wPARAMS);
    return true;
  }
  else
  {
    return LoadBuff(PARAMS_VALUES + iwTimFrom*PARAMS_PAGES, mpreParamsBuff[ PrevSoftTim() ], sizeof(float)*wPARAMS);
  }
}
