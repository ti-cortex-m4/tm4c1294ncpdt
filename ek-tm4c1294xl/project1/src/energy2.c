/*------------------------------------------------------------------------------
ENERGY2.C

 TODO SaveBuff&LoadBuff
------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_energy.h"
#include "memory/mem_realtime.h"
#include "energy.h"
#include "realtime/realtime.h"
#include "flash/files.h"
#include "energy2.h"



bool SaveImpMnt(bool fCurr, uint  iwMntTo, uint  iwMntFrom)
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


bool LoadImpMnt(uint  iwMntFrom)
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



#ifdef  DAYS100

bool SaveImpHou(bool fCurr, uint  iwHouTo, uint  iwHouFrom)
{
  if ((fCurr == 1) && (iwHouTo == iwHardHou))
  {
    memcpy(mpwImpHouCan[ ibSoftHou ], mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
    return true;
  }
  else
  {
    OpenOut(IMPHOUCAN + iwHouTo/4);

    memcpy(mpbPageOut, mpbPageIn, wFREEPAGE_SIZE);
    memcpy(mpbPageOut + (iwHouTo%4)*wPROFILE_LENGTH, mpwImpHouCan[ iwHouFrom ], wPROFILE_LENGTH);

    return( CloseOut() );
  }
}


bool LoadImpHou(uint  iwHouFrom)
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
    if (*mpwImpHouCan[ PrevSoftHou() ], i) == 0xFFFF)
      mpwImpHouCan[ PrevSoftHou() ], i, 0);
  }

  return true;
}


bool LoadImpHouFree(uint  iwHouFrom)
{
  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    return true;
  }
  else
  {
    OpenIn(IMPHOUCAN + iwHouFrom/4);
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpbPageIn + (iwHouFrom%4)*wPROFILE_LENGTH, wPROFILE_LENGTH);
    return true;
  }
}

#else

bool SaveImpHou(bool fCurr, uint  iwHouTo, uint  iwHouFrom)
{
  if ((fCurr == 1) && (iwHouTo == iwHardHou))
  {
    memcpy(mpwImpHouCan[ ibSoftHou ], mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
    return true;
  }
  else
  {
    OpenOut(IMPHOUCAN + iwHouTo*UINTCAN_PAGES);

    if (Save(mpwImpHouCan[ iwHouFrom ], sizeof(uint)*bCANALS) == false)
      return false;

    return( CloseOut() );
  }
}


bool LoadImpHou(uint  iwHouFrom)
{
bool bo;

  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    bo = true;
  }
  else
  {
    OpenIn(IMPHOUCAN + iwHouFrom*UINTCAN_PAGES);
    bo = Load(mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
  }

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (mpwImpHouCan[ PrevSoftHou() ][c] == 0xFFFF)
      mpwImpHouCan[ PrevSoftHou() ][c] = 0;
  }

  return bo;
}


bool LoadImpHouFree(uint  iwHouFrom)
{
  if (iwHouFrom == iwHardHou)
  {
    memcpy(mpwImpHouCan[ PrevSoftHou() ], mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
    return true;
  }
  else
  {
    OpenIn(IMPHOUCAN + iwHouFrom*UINTCAN_PAGES);
    return(Load(mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS));
  }
}

#endif


bool SaveImpDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mpimDayCan[ ibSoftDay ], mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS);
    return true;
  }
  else
    return SaveBuff(IMPDAYCAN + ibDayTo*bIMPULSE_CAN, mpimDayCan[ ibDayFrom ], sizeof(impulse)*bCANALS);
}


bool LoadImpDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpimDayCan[ PrevSoftDay() ], mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
    return true;
  }
  else
    return LoadBuff(IMPDAYCAN + ibDayFrom*bIMPULSE_CAN, mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS);
}



bool SaveImpMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpimMonCan[ ibSoftMon ], mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
    return true;
  }
  else
  	return SaveBuff(IMPMONCAN + ibMonTo*bIMPULSE_CAN, mpimMonCan[ ibMonFrom ], sizeof(impulse)*bCANALS);
}


bool LoadImpMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpimMonCan[ PrevSoftMon() ], mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
    return true;
  }
  else
    return LoadBuff(IMPMONCAN + ibMonFrom*bIMPULSE_CAN, mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
}



bool SavePowDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
    return true;
  }
  else
    return SaveBuff(POWDAYGRP + ibDayTo*bPOWER_GRP, mppoDayGrp[ ibDayFrom ], sizeof(power)*bGROUPS);
}


bool LoadPowDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mppoDayGrp[ PrevSoftDay() ], mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
    return true;
  }
  else
    return LoadBuff(POWDAYGRP + ibDayFrom*bPOWER_GRP, mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
}



bool SavePowMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mppoMonGrp[ ibSoftMon ], mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
    return true;
  }
  else
  	return SaveBuff(POWMONGRP + ibMonTo*bPOWER_GRP, mppoMonGrp[ ibMonFrom ], sizeof(power)*bGROUPS);
}


bool LoadPowMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mppoMonGrp[ PrevSoftMon() ], mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
    return true;
  }
  else
    return LoadBuff(POWMONGRP + ibMonFrom*bPOWER_GRP, mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
}



bool SaveCntMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpdbCntMonCan[ ibSoftMon ], mpdbCntMonCan[ PrevSoftMon() ], sizeof(double)*bCANALS);
    return true;
  }
  else
    return SaveBuff(CNTMONCAN + ibMonTo*DOUBLE_CAN_PAGES, mpdbCntMonCan[ ibMonFrom ], sizeof(double)*bCANALS);
}


bool LoadCntMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpdbCntMonCan[ PrevSoftMon() ], mpdbCntMonCan[ ibSoftMon ], sizeof(double)*bCANALS);
    return true;
  }
  else
    return LoadBuff(CNTMONCAN + ibMonFrom*DOUBLE_CAN_PAGES, mpdbCntMonCan[ PrevSoftMon() ], sizeof(double)*bCANALS);
}
