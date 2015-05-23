/*------------------------------------------------------------------------------
ENERGY_SPEC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_energy_spec.h"
#include "../realtime/realtime.h"
#include "../flash/files.h"
#include "../energy.h"



#ifdef  DAYS100

bool    SaveImpHouSpec(bool  fCurr, uint  iwHouTo)
{
  if ((fCurr == 1) && (iwHouTo == iwHardHou))          
  {
    memcpy(mpwImpHouCan[ ibSoftHou ], mpwImpHouCanSpec, sizeof(uint)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(IMPHOUCAN + iwHouTo/4);
    OpenOut(IMPHOUCAN + iwHouTo/4);

    memcpy(mpbPageOut, mpbPageIn, wFREEPAGE_SIZE);
    memcpy(mpbPageOut + (iwHouTo%4)*wPROFILE_LENGTH, mpwImpHouCanSpec, wPROFILE_LENGTH);

    return( CloseOut() );
  }
}


bool    LoadImpHouSpec(uint  iwHouFrom, bool  fFree) // TODO return boolean
{
uchar   i;
   
  if (iwHouFrom == iwHardHou)          
  {
    memcpy(mpwImpHouCanSpec, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
  }
  else                              
  {
    OpenIn(IMPHOUCAN + iwHouFrom/4);
    memcpy(mpwImpHouCanSpec, mpbPageIn + (iwHouFrom%4)*wPROFILE_LENGTH, wPROFILE_LENGTH);
  }

  if (fFree == 0)
  {
    memcpy(mpwImpHouCanDef, mpwImpHouCanSpec, sizeof(uint)*bCANALS);
    for (i=0; i<bCANALS; i++)
    {
      if (mpwImpHouCanSpec[i] == 0xFFFF)
        mpwImpHouCanSpec, i, 0);  
    }
  }

  return(1);
}

#else

bool    SaveImpHouSpec(bool  fCurr, uint  iwHouTo)
{
  if ((fCurr == 1) && (iwHouTo == iwHardHou))          
  {
    memcpy(mpwImpHouCan[ ibSoftHou ], mpwImpHouCanSpec, sizeof(uint)*bCANALS);
    return(1);
  }
  else
  {
    OpenOut(IMPHOUCAN + iwHouTo*UINTCAN_PAGES);

    if (Save(mpwImpHouCanSpec, sizeof(uint)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpHouSpec(uint  iwHouFrom, bool  fFree) // TODO return boolean
{
bool    fAlt;

  if (iwHouFrom == iwHardHou)          
  {
    memcpy(mpwImpHouCanSpec, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    fAlt = 1;
  }
  else                              
  {
    OpenIn(IMPHOUCAN + iwHouFrom*UINTCAN_PAGES);
    fAlt = Load(mpwImpHouCanSpec, sizeof(uint)*bCANALS);
  }

  if (fFree == 0)
  {
    memcpy(mpwImpHouCanDef, mpwImpHouCanSpec, sizeof(uint)*bCANALS);
    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if (mpwImpHouCanSpec[c] == 0xFFFF)
        mpwImpHouCanSpec[c] = 0;
    }
  }

  return(fAlt);
}

#endif



bool    SaveImpDaySpec(bool  fCurr, uchar  ibDayTo)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mpimDayCan[ ibSoftDay ], mpimDayCanSpec, sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenOut(IMPDAYCAN + ibDayTo*bIMPULSE_CAN);

    if (Save(mpimDayCanSpec, sizeof(impulse)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpDaySpec(uchar  ibDayFrom) // TODO return boolean
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpimDayCanSpec, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(IMPDAYCAN + ibDayFrom*bIMPULSE_CAN);
    return( Load(mpimDayCanSpec, sizeof(impulse)*bCANALS) );
  }
}



bool    SaveImpMonSpec(bool  fCurr, uchar  ibMonTo)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpimMonCan[ ibSoftMon ], mpimMonCanSpec, sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenOut(IMPMONCAN + ibMonTo*bIMPULSE_CAN);

    if (Save(mpimMonCanSpec, sizeof(impulse)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpMonSpec(uchar  ibMonFrom) // TODO return boolean
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpimMonCanSpec, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(IMPMONCAN + ibMonFrom*bIMPULSE_CAN);
    return( Load(mpimMonCanSpec, sizeof(impulse)*bCANALS) );
  }
}



bool    SavePowDaySpec(bool  fCurr, uchar  ibDayTo)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrpSpec, sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenOut(POWDAYGRP + ibDayTo*bPOWER_GRP);

    if (Save(mppoDayGrpSpec, sizeof(power)*bGROUPS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadPowDaySpec(uchar  ibDayFrom) // TODO return boolean
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mppoDayGrpSpec, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenIn(POWDAYGRP + ibDayFrom*bPOWER_GRP);
    return( Load(mppoDayGrpSpec, sizeof(power)*bGROUPS) );
  }
}



bool    SavePowMonSpec(bool  fCurr, uchar  ibMonTo)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mppoMonGrp[ ibSoftMon ], mppoMonGrpSpec, sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenOut(POWMONGRP + ibMonTo*bPOWER_GRP);

    if (Save(mppoMonGrpSpec, sizeof(power)*bGROUPS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadPowMonSpec(uchar  ibMonFrom) // TODO return boolean
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mppoMonGrpSpec, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenIn(POWMONGRP + ibMonFrom*bPOWER_GRP);
    return( Load(mppoMonGrpSpec, sizeof(power)*bGROUPS) );
  }
}




