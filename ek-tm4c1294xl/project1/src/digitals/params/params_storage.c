/*------------------------------------------------------------------------------
PARAMS_STORAGE.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_realtime.h"
#include        "../../realtime/realtime.h"
#include        "../../flash/files.h"
#include        "params_storage.h"



boolean SavePrmTim(uint  iwTimTo, uint  iwTimFrom)
{
  return SaveBuff(PARAMS_VALUES + iwTimTo*PARAMS_PAGES, mpreParBuff[ iwTimFrom ], sizeof(real)*wPARAMS);
}


boolean LoadPrmTim(uint  iwTimFrom)
{
  if (iwTimFrom == iwHardTim)
  { 
    memcpy(mpreParBuff[ PrevSoftTim() ], mpreParBuff[ ibSoftTim ], sizeof(real)*wPARAMS);
    return TRUE;
  }
  else
  {
    return LoadBuff(PARAMS_VALUES + iwTimFrom*PARAMS_PAGES, mpreParBuff[ PrevSoftTim() ], sizeof(real)*wPARAMS);
  }
}
