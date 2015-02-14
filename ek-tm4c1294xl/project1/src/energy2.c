/*------------------------------------------------------------------------------
ENERGY2.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_realtime.h"
#include        "energy.h"
#include        "realtime/realtime.h"
#include        "flash/files.h"



#ifdef  DAYS100

bool    SaveImpHou(bool fCurr, uint  iwHouTo, uint  iwHouFrom)
{
  if ((fCurr == 1) && (iwHouTo == iwHardHou))
  {
    memcpy(mpwImpHouCan[ ibSoftHou ], mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
    return(1);
  }
  else
  {
    OpenOut(wFLA_IMPHOUCAN + iwHouTo/4);

    memcpy(mpbPageOut, mpbPageIn, wFREEPAGE_SIZE);
    memcpy(mpbPageOut + (iwHouTo%4)*wPROFILE_LENGTH, mpwImpHouCan[ iwHouFrom ], wPROFILE_LENGTH);

    return( CloseOut() );
  }
}


bool    LoadImpHou(uint  iwHouFrom)
{
uchar   i;

  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
  }
  else
  {
    OpenIn(wFLA_IMPHOUCAN + iwHouFrom/4);
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpbPageIn + (iwHouFrom%4)*wPROFILE_LENGTH, wPROFILE_LENGTH);
  }

  for (i=0; i<bCANALS; i++)
  {
    if (*PGetCanInt(mpwImpHouCan[ PrevSoftHou() ], i) == 0xFFFF)
      SetCanInt(mpwImpHouCan[ PrevSoftHou() ], i, 0);
  }

  return(1);
}


bool    LoadImpHouFree(uint  iwHouFrom)
{
  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_IMPHOUCAN + iwHouFrom/4);
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpbPageIn + (iwHouFrom%4)*wPROFILE_LENGTH, wPROFILE_LENGTH);
    return(1);
  }
}

#else

bool    SaveImpHou(bool fCurr, uint  iwHouTo, uint  iwHouFrom)
{
  if ((fCurr == 1) && (iwHouTo == iwHardHou))
  {
    memcpy(mpwImpHouCan[ ibSoftHou ], mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
    return(1);
  }
  else
  {
    OpenOut(wFLA_IMPHOUCAN + iwHouTo*bUINT);

    if (Save(mpwImpHouCan[ iwHouFrom ], sizeof(uint)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpHou(uint  iwHouFrom)
{
uchar   i;
bool    fAlt;

  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    fAlt = 1;
  }
  else
  {
    OpenIn(wFLA_IMPHOUCAN + iwHouFrom*bUINT);
    fAlt = Load(mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
  }

  for (i=0; i<bCANALS; i++)
  {
    if (*PGetCanInt(mpwImpHouCan[ PrevSoftHou() ], i) == 0xFFFF)
      SetCanInt(mpwImpHouCan[ PrevSoftHou() ], i, 0);
  }

  return(fAlt);
}


bool    LoadImpHouFree(uint  iwHouFrom)
{
  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_IMPHOUCAN + iwHouFrom*bUINT);
    return(Load(mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS));
  }
}

#endif


bool    SaveImpDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mpimDayCan[ ibSoftDay ], mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenOut(wFLA_IMPDAYCAN + ibDayTo*bIMPULSE);

    if (Save(mpimDayCan[ ibDayFrom ], sizeof(impulse)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpimDayCan[ PrevSoftDay() ], mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_IMPDAYCAN + ibDayFrom*bIMPULSE);
    return( Load(mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS) );
  }
}



bool    SaveImpMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpimMonCan[ ibSoftMon ], mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenOut(wFLA_IMPMONCAN + ibMonTo*bIMPULSE);

    if (Save(mpimMonCan[ ibMonFrom ], sizeof(impulse)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadImpMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpimMonCan[ PrevSoftMon() ], mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_IMPMONCAN + ibMonFrom*bIMPULSE);
    return( Load(mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS) );
  }
}



bool    SavePowDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenOut(wFLA_POWDAYGRP + ibDayTo*bPOWER);

    if (Save(mppoDayGrp[ ibDayFrom ], sizeof(power)*bGROUPS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadPowDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mppoDayGrp[ PrevSoftDay() ], mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_POWDAYGRP + ibDayFrom*bPOWER);
    return( Load(mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS) );
  }
}



bool    SavePowMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mppoMonGrp[ ibSoftMon ], mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenOut(wFLA_POWMONGRP + ibMonTo*bPOWER);

    if (Save(mppoMonGrp[ ibMonFrom ], sizeof(power)*bGROUPS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadPowMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mppoMonGrp[ PrevSoftMon() ], mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_POWMONGRP + ibMonFrom*bPOWER);
    return( Load(mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS) );
  }
}



bool    SaveCntMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpreCntMonCan[ ibSoftMon ], mpreCntMonCan[ PrevSoftMon() ], sizeof(real)*bCANALS);
    return(1);
  }
  else
  {
    OpenOut(wFLA_CNTMONCAN + ibMonTo*bREAL);

    if (Save(mpreCntMonCan[ ibMonFrom ], sizeof(real)*bCANALS) == 0)
      return(0);

    return( CloseOut() );
  }
}


bool    LoadCntMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpreCntMonCan[ PrevSoftMon() ], mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS);
    return(1);
  }
  else
  {
    OpenIn(wFLA_CNTMONCAN + ibMonFrom*bREAL);
    return( Load(mpreCntMonCan[ PrevSoftMon() ], sizeof(real)*bCANALS) );
  }
}
