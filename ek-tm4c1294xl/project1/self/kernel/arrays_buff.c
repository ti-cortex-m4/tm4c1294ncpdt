/*------------------------------------------------------------------------------
ARRAYS_BUFF,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_realtime.h"
#include "../realtime/realtime.h"
#include "../nvram/23x1024.h"
#include "arrays_buff.h"



bool    SaveImpHouBuff(void) {
  return WriteNvramBuff(IMPHOUCAN_BUFF, (uchar *) &mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
}

bool    CleanImpHouBuff(void) {
  return FreeNvramBuff(IMPHOUCAN_BUFF, sizeof(uint)*bCANALS);
}

bool    LoadImpHouBuff(void) {
  return ReadNvramBuff(IMPHOUCAN_BUFF, (uchar *) &mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
}



bool    SaveImpDayBuff(void) {
  return WriteNvramBuff(IMPDAYCAN_BUFF, (uchar *) &mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}

bool    CleanImpDayBuff(void) {
  return FreeNvramBuff(IMPDAYCAN_BUFF, sizeof(impulse)*bCANALS);
}

bool    LoadImpDayBuff(void) {
  return ReadNvramBuff(IMPDAYCAN_BUFF, (uchar *) &mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}



bool    SaveImpMonBuff(void) {
  return WriteNvramBuff(IMPMONCAN_BUFF, (uchar *) &mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}

bool    CleanImpMonBuff(void) {
  return FreeNvramBuff(IMPMONCAN_BUFF, sizeof(impulse)*bCANALS);
}

bool    LoadImpMonBuff(void) {
  return ReadNvramBuff(IMPMONCAN_BUFF, (uchar *) &mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}



bool    SaveImpAbsBuff(void) {
  return WriteNvramBuff(IMPABSCAN_BUFF, (uchar *) &mpimAbsCan, sizeof(impulse)*bCANALS);
}

bool    CleanImpAbsBuff(void) {
  return FreeNvramBuff(IMPABSCAN_BUFF, sizeof(impulse)*bCANALS);
}

bool    LoadImpAbsBuff(void) {
  return ReadNvramBuff(IMPABSCAN_BUFF, (uchar *) &mpimAbsCan, sizeof(impulse)*bCANALS);
}



bool    SavePowDayBuff(void) {
  return WriteNvramBuff(POWDAYGRP_BUFF, (uchar *) &mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}

bool    CleanPowDayBuff(void) {
  return FreeNvramBuff(POWDAYGRP_BUFF, sizeof(power)*bGROUPS);
}

bool    LoadPowDayBuff(void) {
  return ReadNvramBuff(POWDAYGRP_BUFF, (uchar *) &mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}



bool    SavePowMonBuff(void) {
  return WriteNvramBuff(POWMONGRP_BUFF, (uchar *) &mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}

bool    CleanPowMonBuff(void) {
  return FreeNvramBuff(POWMONGRP_BUFF, sizeof(power)*bGROUPS);
}

bool    LoadPowMonBuff(void) {
  return ReadNvramBuff(POWMONGRP_BUFF, (uchar *) &mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}



bool    SaveCntMonBuff(void) {
  return WriteNvramBuff(CNTMONCAN_BUFF, (uchar *) &mpdbCntMonCan[ ibSoftMon ], sizeof(double)*bCANALS);
}

bool    CleanCntMonBuff(void) {
  return FreeNvramBuff(CNTMONCAN_BUFF, sizeof(double)*bCANALS);
}

bool    LoadCntMonBuff(void) {
  return ReadNvramBuff(CNTMONCAN_BUFF, (uchar *) &mpdbCntMonCan[ ibSoftMon ], sizeof(double)*bCANALS);
}
