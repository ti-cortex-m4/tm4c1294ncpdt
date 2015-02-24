/*------------------------------------------------------------------------------
ENERGY3.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_realtime.h"
#include        "energy.h"
#include        "realtime/realtime.h"
#include        "flash/files.h"



bool    SaveImpDayBuff(void) {
  return SaveBuff(DF_IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}

bool    LoadImpDayBuff(void) {
  return LoadBuff(DF_IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}


bool    SaveImpMonBuff(void) {
	return SaveBuff(DF_IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}

bool    LoadImpMonBuff(void) {
  return LoadBuff(DF_IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}


bool    SaveImpAbsBuff(void) {
	return SaveBuff(DF_IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS);
}

bool    LoadImpAbsBuff(void) {
  return LoadBuff(DF_IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS);
}


bool    SavePowDayBuff(bool fCurr, uchar  ibDayTo, uchar  ibDayFrom)
{
  if ((fCurr == 1) && (ibDayTo == ibHardDay))
  {
    memcpy(mppoDayGrp[ ibSoftDay ], mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
    return SaveBuff(DF_POWDAYGRP + ibDayTo*bPOWER_GRP, mppoDayGrp[ ibDayFrom ], sizeof(power)*bGROUPS);
}


bool    LoadPowDayBuff(uchar  ibDayFrom)
{
  if (ibDayFrom == ibHardDay)
  {
    memcpy(mppoDayGrp[ PrevSoftDay() ], mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
    return LoadBuff(DF_POWDAYGRP + ibDayFrom*bPOWER_GRP, mppoDayGrp[ PrevSoftDay() ], sizeof(power)*bGROUPS);
}



bool    SavePowMonBuff(bool fCurr, uchar  ibMonTo, uchar  ibMonFrom)
{
  if ((fCurr == 1) && (ibMonTo == ibHardMon))
  {
    memcpy(mppoMonGrp[ ibSoftMon ], mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
  	return SaveBuff(DF_POWMONGRP + ibMonTo*bPOWER_GRP, mppoMonGrp[ ibMonFrom ], sizeof(power)*bGROUPS);
}


bool    LoadPowMonBuff(uchar  ibMonFrom)
{
  if (ibMonFrom == ibHardMon)
  {
    memcpy(mppoMonGrp[ PrevSoftMon() ], mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
    return(1);
  }
  else
    return LoadBuff(DF_POWMONGRP + ibMonFrom*bPOWER_GRP, mppoMonGrp[ PrevSoftMon() ], sizeof(power)*bGROUPS);
}
