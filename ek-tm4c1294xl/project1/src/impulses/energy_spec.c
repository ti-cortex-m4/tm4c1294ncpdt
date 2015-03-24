/*------------------------------------------------------------------------------
ENERGY_SPEC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../realtime/realtime.h"
#include        "../flash/files.h"



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
    OpenIn(wFLA_IMPHOUCAN + iwHouTo/4);
    OpenOut(wFLA_IMPHOUCAN + iwHouTo/4);

    memcpy(mpbPageOut, mpbPageIn, wFREEPAGE_SIZE);
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
    OpenIn(wFLA_IMPHOUCAN + iwHouFrom/4);
    memcpy(mpwImpHouCanSpec, mpbPageIn + (iwHouFrom%4)*wPROFILE_LENGTH, wPROFILE_LENGTH);
  }

  if (fFree == 0)
  {
    memcpy(mpwImpHouCanDef, mpwImpHouCanSpec, sizeof(uint)*bCANALS);
    for (i=0; i<bCANALS; i++)
    {
      if (*PGetCanInt(mpwImpHouCanSpec, i) == 0xFFFF)
        SetCanInt(mpwImpHouCanSpec, i, 0);  
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
    OpenOut(wFLA_IMPHOUCAN + iwHouTo*bUINT);

    if (Save(mpwImpHouCanSpec, sizeof(uint)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpHouSpec(uint  iwHouFrom, bool  fFree)
{
uchar   i;
   
  if (iwHouFrom == iwHardHou)          
  {
    memcpy(mpwImpHouCanSpec, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    fAlt = 1;
  }
  else                              
  {
    OpenIn(wFLA_IMPHOUCAN + iwHouFrom*bUINT);
    fAlt = Load(mpwImpHouCanSpec, sizeof(uint)*bCANALS);
  }

  if (fFree == 0)
  {
    memcpy(mpwImpHouCanDef, mpwImpHouCanSpec, sizeof(uint)*bCANALS);
    for (i=0; i<bCANALS; i++)
    {
      if (*PGetCanInt(mpwImpHouCanSpec, i) == 0xFFFF)
        SetCanInt(mpwImpHouCanSpec, i, 0);  
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
    OpenOut(wFLA_IMPDAYCAN + ibDayTo*bIMPULSE);

    if (Save(mpimDayCanSpec, sizeof(impulse)*bCANALS) == 0)
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
    OpenIn(wFLA_IMPDAYCAN + ibDayFrom*bIMPULSE);
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
    OpenOut(wFLA_IMPMONCAN + ibMonTo*bIMPULSE);

    if (Save(mpimMonCanSpec, sizeof(impulse)*bCANALS) == 0)
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
    OpenIn(wFLA_IMPMONCAN + ibMonFrom*bIMPULSE);
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
    OpenOut(wFLA_POWDAYGRP + ibDayTo*bPOWER);

    if (Save(mppoDayGrpSpec, sizeof(power)*bGROUPS) == 0)
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
    OpenIn(wFLA_POWDAYGRP + ibDayFrom*bPOWER);
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
    OpenOut(wFLA_POWMONGRP + ibMonTo*bPOWER);

    if (Save(mppoMonGrpSpec, sizeof(power)*bGROUPS) == 0)
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
    OpenIn(wFLA_POWMONGRP + ibMonFrom*bPOWER);
    return( Load(mppoMonGrpSpec, sizeof(power)*bGROUPS) );
  }
}




