/*------------------------------------------------------------------------------
ENERGY_SPEC!C


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

    memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);
    memcpy(mpbPageOut + (iwHouTo%4)*wPROFILE_LENGTH, mpwImpHouCanSpec, wPROFILE_LENGTH);

    return( CloseOut() );
  }
}


bool    LoadImpHouSpec(uint  iwHouFrom, bool  fFree)
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
    OpenOut(IMPHOUCAN + iwHouTo*UINT_CAN_PAGES);

    if (Save((uchar *) &mpwImpHouCanSpec, sizeof(uint)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpHouSpec(uint  iwHouFrom, bool  fFree)
{
bool    fAlt;

  if (iwHouFrom == iwHardHou)          
  {
    memcpy(mpwImpHouCanSpec, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    fAlt = 1;
  }
  else                              
  {
    OpenIn(IMPHOUCAN + iwHouFrom*UINT_CAN_PAGES);
    fAlt = Load((uchar *) &mpwImpHouCanSpec, sizeof(uint)*bCANALS);
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
    OpenOut(IMPDAYCAN + ibDayTo*IMP_CAN_PAGES);

    if (Save((uchar *) &mpimDayCanSpec, sizeof(impulse)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpDaySpec(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpimDayCanSpec, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(IMPDAYCAN + ibDayFrom*IMP_CAN_PAGES);
    return( Load((uchar *) &mpimDayCanSpec, sizeof(impulse)*bCANALS) );
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
    OpenOut(IMPMONCAN + ibMonTo*IMP_CAN_PAGES);

    if (Save((uchar *) &mpimMonCanSpec, sizeof(impulse)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpMonSpec(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpimMonCanSpec, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(IMPMONCAN + ibMonFrom*IMP_CAN_PAGES);
    return( Load((uchar *) &mpimMonCanSpec, sizeof(impulse)*bCANALS) );
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
    OpenOut(POWDAYGRP + ibDayTo*MAXPOW_GRP_PAGES);

    if (Save((uchar *) &mppoDayGrpSpec, sizeof(power)*bGROUPS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadPowDaySpec(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mppoDayGrpSpec, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenIn(POWDAYGRP + ibDayFrom*MAXPOW_GRP_PAGES);
    return( Load((uchar *) &mppoDayGrpSpec, sizeof(power)*bGROUPS) );
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
    OpenOut(POWMONGRP + ibMonTo*MAXPOW_GRP_PAGES);

    if (Save((uchar *) &mppoMonGrpSpec, sizeof(power)*bGROUPS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadPowMonSpec(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mppoMonGrpSpec, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenIn(POWMONGRP + ibMonFrom*MAXPOW_GRP_PAGES);
    return( Load((uchar *) &mppoMonGrpSpec, sizeof(power)*bGROUPS) );
  }
}




