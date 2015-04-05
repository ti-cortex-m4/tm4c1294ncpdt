/*------------------------------------------------------------------------------
PARAMS_STORAGE.C


------------------------------------------------------------------------------*/

#include        "main.h"
//#include        "memory/mem_energy.h"
//#include        "memory/mem_realtime.h"
//#include        "energy.h"
//#include        "realtime/realtime.h"
#include        "flash/files.h"



bool    SaveParams(uint  iwPrmTo, uint  iwPrmFrom)
{
  OpenOut(wFLA_REATIMPAR + iwPrmTo*bPARAM);

  if (Save_Far(mpreParBuff[ iwPrmFrom ], sizeof(real)*wPARAMS) == 0)
    return(0);

  return( CloseOut() );
}


bool    LoadParams(uint  iwPrmFrom)
{
  if (iwPrmFrom == iwHardTim)
  { 
    memcpy(mpreParBuff[ PrevSoftTim() ], mpreParBuff[ ibSoftTim ], sizeof(real)*wPARAMS);
    return(1);
  }
  else
  { 
    OpenIn(wFLA_REATIMPAR + iwPrmFrom*bPARAM);
    return( Load_Far(mpreParBuff[ PrevSoftTim() ], sizeof(real)*wPARAMS) );
  }
}

