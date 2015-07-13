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

    memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);
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
    OpenOut(IMPHOUCAN + iwHouTo*UINT_CAN_PAGES);

    if (Save((uchar *) &mpwImpHouCan[ iwHouFrom ], sizeof(uint)*bCANALS) == false)
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
    OpenIn(IMPHOUCAN + iwHouFrom*UINT_CAN_PAGES);
    bo = Load((uchar *) &mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS);
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
    OpenIn(IMPHOUCAN + iwHouFrom*UINT_CAN_PAGES);
    return(Load((uchar *) &mpwImpHouCan[ PrevSoftHou() ], sizeof(uint)*bCANALS));
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
    return SaveBuff(IMPDAYCAN + ibDayTo*IMP_CAN_PAGES, mpimDayCan[ ibDayFrom ], sizeof(impulse)*bCANALS);
}


bool LoadImpDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mpimDayCan[ PrevSoftDay() ], mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
    return true;
  }
  else
    return LoadBuff(IMPDAYCAN + ibDayFrom*IMP_CAN_PAGES, mpimDayCan[ PrevSoftDay() ], sizeof(impulse)*bCANALS);
}



bool SaveImpMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mpimMonCan[ ibSoftMon ], mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
    return true;
  }
  else
  	return SaveBuff(IMPMONCAN + ibMonTo*IMP_CAN_PAGES, mpimMonCan[ ibMonFrom ], sizeof(impulse)*bCANALS);
}


bool LoadImpMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mpimMonCan[ PrevSoftMon() ], mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
    return true;
  }
  else
    return LoadBuff(IMPMONCAN + ibMonFrom*IMP_CAN_PAGES, mpimMonCan[ PrevSoftMon() ], sizeof(impulse)*bCANALS);
}



bool SavePowDay(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
    return true;
  }
  else
    return SaveBuff(POWDAYGRP + ibDayTo*MAXPOW_GRP_PAGES, mppoDayGrp[ ibDayFrom ], sizeof(power)*bGROUPS);
}


bool LoadPowDay(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mppoDayGrp[ PrevSoftDay() ], mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
    return true;
  }
  else
    return LoadBuff(POWDAYGRP + ibDayFrom*MAXPOW_GRP_PAGES, mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
}



bool SavePowMon(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mppoMonGrp[ ibSoftMon ], mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
    return true;
  }
  else
  	return SaveBuff(POWMONGRP + ibMonTo*MAXPOW_GRP_PAGES, mppoMonGrp[ ibMonFrom ], sizeof(power)*bGROUPS);
}


bool LoadPowMon(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mppoMonGrp[ PrevSoftMon() ], mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
    return true;
  }
  else
    return LoadBuff(POWMONGRP + ibMonFrom*MAXPOW_GRP_PAGES, mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
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
