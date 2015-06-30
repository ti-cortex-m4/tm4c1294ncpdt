/*------------------------------------------------------------------------------
ARRAY_MNT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_realtime.h"
#include "../realtime/realtime.h"
#include "../flash/files.h"
#include "array_mnt.h"



bool    SaveImpMnt(bool fCurr, uint  iwMntTo, uint  iwMntFrom)
{
  if ((fCurr == 1) && (iwMntTo == iwHardMnt))
  {
    memcpy(mpwImpMntCan[ ibSoftMnt ], mpwImpMntCan[ PrevSoftMnt() ], sizeof(uint)*bCANALS);
    return true;
  }
  else
  {
    OpenOut(IMPMNTCAN + iwMntTo*UINTCAN_PAGES);

    if (Save(mpwImpMntCan[ iwMntFrom ], sizeof(uint)*bCANALS) == false)
      return false;

    return( CloseOut() );
  }
}


bool    LoadImpMnt(uint  iwMntFrom)
{
bool bo;

  if (iwMntFrom == iwHardMnt)
  {
    memcpy(mpwImpMntCan[ PrevSoftMnt() ], mpwImpMntCan[ ibSoftMnt ], sizeof(uint)*bCANALS);
    bo = true;
  }
  else
  {
    OpenIn(IMPMNTCAN + iwMntFrom*UINTCAN_PAGES);
    bo = Load(mpwImpMntCan[ PrevSoftMnt() ], sizeof(uint)*bCANALS);
  }

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (mpwImpMntCan[ PrevSoftMnt() ][c] == 0xFFFF)
      mpwImpMntCan[ PrevSoftMnt() ][c] = 0;
  }

  return bo;
}
