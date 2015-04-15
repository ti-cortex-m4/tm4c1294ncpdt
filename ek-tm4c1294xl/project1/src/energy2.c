/*------------------------------------------------------------------------------
ENERGY2.C

 TODO SaveBuff&LoadBuff
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_realtime.h"
#include        "energy.h"
#include        "realtime/realtime.h"
#include        "flash/files.h"
#include        "energy2.h"



boolean SaveImpMnt(bool fCurr, uchar  ibMntTo, uchar  ibMntFrom)
{
  if ((fCurr == 1) && (ibMntTo == ibHardMnt))
  {
    memcpy(mpwImpMntCan[ ibSoftMnt ], mpwImpMntCan[ PrevSoftMnt() ], sizeof(uint)*bCANALS);
    return TRUE;
  }
  else
  {
    OpenOut(IMPMNTCAN + ibMntTo*UINTCAN_PAGES);

    if (Save(mpwImpMntCan[ ibMntFrom ], sizeof(uint)*bCANALS) == FALSE)
      return FALSE;

    return( CloseOut() );
  }
}


boolean LoadImpMnt(uchar  ibMntFrom)
{
uchar   i;
boolean bo;

  if (ibMntFrom == ibHardMnt)
  {
    memcpy(mpwImpMntCan[ PrevSoftMnt() ], mpwImpMntCan[ ibSoftMnt ], sizeof(uint)*bCANALS);
    bo = TRUE;
  }
  else
  {
    OpenIn(IMPMNTCAN + ibMntFrom*UINTCAN_PAGES);
    bo = Load(mpwImpMntCan[ PrevSoftMnt() ], sizeof(uint)*bCANALS);
  }

  for (i=0; i<bCANALS; i++)
  {
    if (GetCanInt(mpwImpMntCan[ PrevSoftMnt() ], i) == 0xFFFF)
      SetCanInt(mpwImpMntCan[ PrevSoftMnt() ], i, 0);
  }

  return bo;
}



#ifdef  DAYS100

boolean SaveImpHou(bool fCurr, uint  iwHouTo, uint  iwHouFrom)
{
  if ((fCurr == 1) && (iwHouTo == iwHardHou))
  {
    memcpy(mpwImpHouCan[ ibSoftHou ], mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
    return TRUE;
  }
  else
  {
    OpenOut(IMPHOUCAN + iwHouTo/4);

    memcpy(mpbPageOut, mpbPageIn, wFREEPAGE_SIZE);
    memcpy(mpbPageOut + (iwHouTo%4)*wPROFILE_LENGTH, mpwImpHouCan[ iwHouFrom ], wPROFILE_LENGTH);

    return( CloseOut() );
  }
}


boolean LoadImpHou(uint  iwHouFrom)
{
uchar   i;

  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
  }
  else
  {
    OpenIn(IMPHOUCAN + iwHouFrom/4);
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpbPageIn + (iwHouFrom%4)*wPROFILE_LENGTH, wPROFILE_LENGTH);
  }

  for (i=0; i<bCANALS; i++)
  {
    if (*GetCanInt(mpwImpHouCan[ PrevSoftHou() ], i) == 0xFFFF)
      SetCanInt(mpwImpHouCan[ PrevSoftHou() ], i, 0);
  }

  return TRUE;
}


boolean LoadImpHouFree(uint  iwHouFrom)
{
  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    return TRUE;
  }
  else
  {
    OpenIn(IMPHOUCAN + iwHouFrom/4);
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpbPageIn + (iwHouFrom%4)*wPROFILE_LENGTH, wPROFILE_LENGTH);
    return TRUE;
  }
}

#else

boolean SaveImpHou(bool fCurr, uint  iwHouTo, uint  iwHouFrom)
{
  if ((fCurr == 1) && (iwHouTo == iwHardHou))
  {
    memcpy(mpwImpHouCan[ ibSoftHou ], mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
    return TRUE;
  }
  else
  {
    OpenOut(IMPHOUCAN + iwHouTo*UINTCAN_PAGES);

    if (Save(mpwImpHouCan[ iwHouFrom ], sizeof(uint)*bCANALS) == FALSE)
      return FALSE;

    return( CloseOut() );
  }
}


boolean LoadImpHou(uint  iwHouFrom)
{
uchar   i;
boolean bo;

  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    bo = TRUE;
  }
  else
  {
    OpenIn(IMPHOUCAN + iwHouFrom*UINTCAN_PAGES);
    bo = Load(mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
  }

  for (i=0; i<bCANALS; i++)
  {
    if (GetCanInt(mpwImpHouCan[ PrevSoftHou() ], i) == 0xFFFF)
      SetCanInt(mpwImpHouCan[ PrevSoftHou() ], i, 0);
  }

  return bo;
}


boolean LoadImpHouFree(uint  iwHouFrom)
{
  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    return TRUE;
  }
  else
  {
    OpenIn(IMPHOUCAN + iwHouFrom*UINTCAN_PAGES);
    return(Load(mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS));
  }
}

#endif


boolean SaveImpDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mpimDayCan[ ibSoftDay ], mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS);
    return TRUE;
  }
  else
    return SaveBuff(IMPDAYCAN + ibDayTo*bIMPULSE_CAN, mpimDayCan[ ibDayFrom ], sizeof(impulse)*bCANALS);
}


boolean LoadImpDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpimDayCan[ PrevSoftDay() ], mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
    return TRUE;
  }
  else
    return LoadBuff(IMPDAYCAN + ibDayFrom*bIMPULSE_CAN, mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS);
}



boolean SaveImpMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpimMonCan[ ibSoftMon ], mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
    return TRUE;
  }
  else
  	return SaveBuff(IMPMONCAN + ibMonTo*bIMPULSE_CAN, mpimMonCan[ ibMonFrom ], sizeof(impulse)*bCANALS);
}


boolean LoadImpMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpimMonCan[ PrevSoftMon() ], mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
    return TRUE;
  }
  else
    return LoadBuff(IMPMONCAN + ibMonFrom*bIMPULSE_CAN, mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
}



boolean SavePowDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
    return TRUE;
  }
  else
    return SaveBuff(POWDAYGRP + ibDayTo*bPOWER_GRP, mppoDayGrp[ ibDayFrom ], sizeof(power)*bGROUPS);
}


boolean LoadPowDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mppoDayGrp[ PrevSoftDay() ], mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
    return TRUE;
  }
  else
    return LoadBuff(POWDAYGRP + ibDayFrom*bPOWER_GRP, mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
}



boolean SavePowMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mppoMonGrp[ ibSoftMon ], mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
    return TRUE;
  }
  else
  	return SaveBuff(POWMONGRP + ibMonTo*bPOWER_GRP, mppoMonGrp[ ibMonFrom ], sizeof(power)*bGROUPS);
}


boolean LoadPowMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mppoMonGrp[ PrevSoftMon() ], mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
    return TRUE;
  }
  else
    return LoadBuff(POWMONGRP + ibMonFrom*bPOWER_GRP, mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
}



boolean SaveCntMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpreCntMonCan[ ibSoftMon ], mpreCntMonCan[ PrevSoftMon() ], sizeof(real)*bCANALS);
    return TRUE;
  }
  else
    return SaveBuff(CNTMONCAN + ibMonTo*REALCAN_PAGES, mpreCntMonCan[ ibMonFrom ], sizeof(real)*bCANALS);
}


boolean LoadCntMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpreCntMonCan[ PrevSoftMon() ], mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS);
    return TRUE;
  }
  else
    return LoadBuff(CNTMONCAN + ibMonFrom*REALCAN_PAGES, mpreCntMonCan[ PrevSoftMon() ], sizeof(real)*bCANALS);
}
