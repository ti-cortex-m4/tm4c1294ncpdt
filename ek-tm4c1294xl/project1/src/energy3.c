/*------------------------------------------------------------------------------
ENERGY3.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_energy.h"
#include "memory/mem_realtime.h"
#include "energy.h"
#include "realtime/realtime.h"
#include "flash/files.h"



bool SaveImpHouBuff(void) {
  return SaveBuff(IMPHOUCAN_BUFF, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
}

bool CleanImpHouBuff(void) {
  return CleanBuff(IMPHOUCAN_BUFF, sizeof(uint)*bCANALS);
}

bool LoadImpHouBuff(void) {
  return LoadBuff(IMPHOUCAN_BUFF, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
}



bool SaveImpDayBuff(void) {
  return SaveBuff(IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}

bool CleanImpDayBuff(void) {
  return CleanBuff(IMPDAYCAN_BUFF, sizeof(impulse)*bCANALS);
}

bool LoadImpDayBuff(void) {
  return LoadBuff(IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}



bool SaveImpMonBuff(void) {
  return SaveBuff(IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}

bool CleanImpMonBuff(void) {
  return CleanBuff(IMPMONCAN_BUFF, sizeof(impulse)*bCANALS);
}

bool LoadImpMonBuff(void) {
  return LoadBuff(IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}



bool SaveImpAbsBuff(void) {
  return SaveBuff(IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS);
}

bool CleanImpAbsBuff(void) {
  return CleanBuff(IMPABSCAN_BUFF, sizeof(impulse)*bCANALS);
}

bool LoadImpAbsBuff(void) {
  return LoadBuff(IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS);
}



bool SavePowDayBuff(void) {
  return SaveBuff(POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}

bool CleanPowDayBuff(void) {
  return CleanBuff(POWDAYGRP_BUFF, sizeof(power)*bGROUPS);
}

bool LoadPowDayBuff(void) {
  return LoadBuff(POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}



bool SavePowMonBuff(void) {
  return SaveBuff(POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}

bool CleanPowMonBuff(void) {
  return CleanBuff(POWMONGRP_BUFF, sizeof(power)*bGROUPS);
}

bool LoadPowMonBuff(void) {
  return LoadBuff(POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}



bool SaveCntMonBuff(void) {
  return SaveBuff(CNTMONCAN_BUFF, mpdbCntMonCan[ ibSoftMon ], sizeof(double)*bCANALS);
}

bool CleanCntMonBuff(void) {
  return CleanBuff(CNTMONCAN_BUFF, sizeof(double)*bCANALS);
}

bool LoadCntMonBuff(void) {
  return LoadBuff(CNTMONCAN_BUFF, mpdbCntMonCan[ ibSoftMon ], sizeof(double)*bCANALS);
}
