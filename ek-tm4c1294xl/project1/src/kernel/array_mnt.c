/*------------------------------------------------------------------------------
ARRAY_MNT,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_realtime.h"
#include "../realtime/realtime.h"
#include "../nvram/cache.h"
#include "array_mnt.h"



bool    SaveImpMnt(uint  iwMntTo, uchar  ibMntFrom)
{
  return SaveArrayX(IMPMNTCAN, sizeof(uint)*bCANALS, iwMntTo, &mpwImpMntCan[ ibMntFrom ]);
}


bool    FreeImpMnt(uint  iwMntTo)
{
  return FreeArrayX(IMPMNTCAN, sizeof(uint)*bCANALS, iwMntTo);
}


bool    LoadImpMnt(uint  iwMntFrom)
{
  if (iwMntFrom == iwHardMnt)
  {
    memcpy(mpwImpMntCan[ PrevSoftMnt() ], mpwImpMntCan[ ibSoftMnt ], sizeof(uint)*bCANALS);
    return true;
  }
  else
  {
    return LoadArrayX(IMPMNTCAN, sizeof(uint)*bCANALS, iwMntFrom, &mpwImpMntCan[ PrevSoftMnt() ]);
  }
}
