/*------------------------------------------------------------------------------
ENERGY3.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_energy.h"
#include "memory/mem_realtime.h"
#include "energy.h"
#include "realtime/realtime.h"
#include "flash/files.h"



boolean SaveImpHouBuff(void) {
  return SaveBuff(IMPHOUCAN_BUFF, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
}

boolean CleanImpHouBuff(void) {
  return CleanBuff(IMPHOUCAN_BUFF, sizeof(uint)*bCANALS);
}

boolean LoadImpHouBuff(void) {
  return LoadBuff(IMPHOUCAN_BUFF, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
}



boolean SaveImpDayBuff(void) {
  return SaveBuff(IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}

boolean CleanImpDayBuff(void) {
  return CleanBuff(IMPDAYCAN_BUFF, sizeof(impulse)*bCANALS);
}

boolean LoadImpDayBuff(void) {
  return LoadBuff(IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}



boolean SaveImpMonBuff(void) {
  return SaveBuff(IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}

boolean CleanImpMonBuff(void) {
  return CleanBuff(IMPMONCAN_BUFF, sizeof(impulse)*bCANALS);
}

boolean LoadImpMonBuff(void) {
  return LoadBuff(IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}



boolean SaveImpAbsBuff(void) {
  return SaveBuff(IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS);
}

boolean CleanImpAbsBuff(void) {
  return CleanBuff(IMPABSCAN_BUFF, sizeof(impulse)*bCANALS);
}

boolean LoadImpAbsBuff(void) {
  return LoadBuff(IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS);
}



boolean SavePowDayBuff(void) {
  return SaveBuff(POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}

boolean CleanPowDayBuff(void) {
  return CleanBuff(POWDAYGRP_BUFF, sizeof(power)*bGROUPS);
}

boolean LoadPowDayBuff(void) {
  return LoadBuff(POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}



boolean SavePowMonBuff(void) {
  return SaveBuff(POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}

boolean CleanPowMonBuff(void) {
  return CleanBuff(POWMONGRP_BUFF, sizeof(power)*bGROUPS);
}

boolean LoadPowMonBuff(void) {
  return LoadBuff(POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}



boolean SaveCntMonBuff(void) {
  return SaveBuff(CNTMONCAN_BUFF, mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS);
}

boolean CleanCntMonBuff(void) {
  return CleanBuff(CNTMONCAN_BUFF, sizeof(real)*bCANALS);
}

boolean LoadCntMonBuff(void) {
  return LoadBuff(CNTMONCAN_BUFF, mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS);
}
