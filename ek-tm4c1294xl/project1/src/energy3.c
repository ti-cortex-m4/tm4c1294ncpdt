/*------------------------------------------------------------------------------
ENERGY3.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_realtime.h"
#include        "energy.h"
#include        "realtime/realtime.h"
#include        "flash/files.h"



boolean SaveImpDayBuff(void) {
  return SaveBuff(FLS_IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS, FOR_IMPULSE);
}


boolean LoadImpDayBuff(void) {
  return LoadBuff(FLS_IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}



boolean SaveImpMonBuff(void) {
  return SaveBuff(FLS_IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS, FOR_IMPULSE);
}


boolean LoadImpMonBuff(void) {
  return LoadBuff(FLS_IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}



boolean SaveImpAbsBuff(void) {
  return SaveBuff(FLS_IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS, FOR_REAL);
}


boolean LoadImpAbsBuff(void) {
  return LoadBuff(FLS_IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS);
}



boolean SavePowDayBuff(void) {
  return SaveBuff(FLS_POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS, FOR_MAX_POWER);
}


boolean LoadPowDayBuff(void) {
  return LoadBuff(FLS_POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}



boolean SavePowMonBuff(void) {
  return SaveBuff(FLS_POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS, FOR_MAX_POWER);
}


boolean LoadPowMonBuff(void) {
  return LoadBuff(FLS_POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}



boolean SaveCntMonBuff(void) {
  return SaveBuff(FLS_CNTMONCAN_BUFF, mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS, FOR_REAL);
}


boolean LoadCntMonBuff(void) {
  return LoadBuff(FLS_CNTMONCAN_BUFF, mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS);
}
