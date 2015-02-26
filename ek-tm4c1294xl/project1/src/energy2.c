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
    OpenOut(DF_IMPHOUCAN + iwHouTo/4);

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
    OpenIn(DF_IMPHOUCAN + iwHouFrom/4);
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
    OpenIn(DF_IMPHOUCAN + iwHouFrom/4);
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
    OpenOut(DF_IMPHOUCAN + iwHouTo*bUINT_CAN);

    if (Save(mpwImpHouCan[ iwHouFrom ], sizeof(uint)*bCANALS, FOR_IMPULSE) == FALSE)
      return FALSE;

    return( CloseOut(FOR_IMPULSE) );
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
    OpenIn(DF_IMPHOUCAN + iwHouFrom*bUINT_CAN);
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
    OpenIn(DF_IMPHOUCAN + iwHouFrom*bUINT_CAN);
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
    return SaveBuff(DF_IMPDAYCAN + ibDayTo*bIMPULSE_CAN, mpimDayCan[ ibDayFrom ], sizeof(impulse)*bCANALS, FOR_IMPULSE);
}


boolean LoadImpDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpimDayCan[ PrevSoftDay() ], mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
    return TRUE;
  }
  else
    return LoadBuff(DF_IMPDAYCAN + ibDayFrom*bIMPULSE_CAN, mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS);
}



boolean SaveImpMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpimMonCan[ ibSoftMon ], mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
    return TRUE;
  }
  else
  	return SaveBuff(DF_IMPMONCAN + ibMonTo*bIMPULSE_CAN, mpimMonCan[ ibMonFrom ], sizeof(impulse)*bCANALS, FOR_IMPULSE);
}


boolean LoadImpMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpimMonCan[ PrevSoftMon() ], mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
    return TRUE;
  }
  else
    return LoadBuff(DF_IMPMONCAN + ibMonFrom*bIMPULSE_CAN, mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
}



boolean SavePowDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
    return TRUE;
  }
  else
    return SaveBuff(DF_POWDAYGRP + ibDayTo*bPOWER_GRP, mppoDayGrp[ ibDayFrom ], sizeof(power)*bGROUPS, FOR_MAX_POWER);
}


boolean LoadPowDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mppoDayGrp[ PrevSoftDay() ], mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
    return TRUE;
  }
  else
    return LoadBuff(DF_POWDAYGRP + ibDayFrom*bPOWER_GRP, mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
}



boolean SavePowMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mppoMonGrp[ ibSoftMon ], mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
    return TRUE;
  }
  else
  	return SaveBuff(DF_POWMONGRP + ibMonTo*bPOWER_GRP, mppoMonGrp[ ibMonFrom ], sizeof(power)*bGROUPS, FOR_MAX_POWER);
}


boolean LoadPowMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mppoMonGrp[ PrevSoftMon() ], mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
    return TRUE;
  }
  else
    return LoadBuff(DF_POWMONGRP + ibMonFrom*bPOWER_GRP, mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
}



boolean SaveCntMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpreCntMonCan[ ibSoftMon ], mpreCntMonCan[ PrevSoftMon() ], sizeof(real)*bCANALS);
    return TRUE;
  }
  else
    return SaveBuff(DF_CNTMONCAN + ibMonTo*bREAL_CAN, mpreCntMonCan[ ibMonFrom ], sizeof(real)*bCANALS, FOR_REAL);
}


boolean LoadCntMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpreCntMonCan[ PrevSoftMon() ], mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS);
    return TRUE;
  }
  else
    return LoadBuff(DF_CNTMONCAN + ibMonFrom*bREAL_CAN, mpreCntMonCan[ PrevSoftMon() ], sizeof(real)*bCANALS);
}
