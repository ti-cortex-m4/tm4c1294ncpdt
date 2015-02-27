/*------------------------------------------------------------------------------
ENERGY3.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_realtime.h"
#include        "energy.h"
#include        "realtime/realtime.h"
#include        "flash/files.h"



boolean SaveImpHouBuff(void) {
  return SaveBuff(FLS_IMPHOUCAN_BUFF, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS, FRM_UINT);
}


boolean LoadImpHouBuff(void) {
  return LoadBuff(FLS_IMPHOUCAN_BUFF, mpwImpHouCan[ ibSoftHou ], sizeof(uint)*bCANALS);
}



boolean SaveImpDayBuff(void) {
  return SaveBuff(FLS_IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS, FRM_IMPULSE);
}


boolean LoadImpDayBuff(void) {
  return LoadBuff(FLS_IMPDAYCAN_BUFF, mpimDayCan[ ibSoftDay ], sizeof(impulse)*bCANALS);
}



boolean SaveImpMonBuff(void) {
  return SaveBuff(FLS_IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS, FRM_IMPULSE);
}


boolean LoadImpMonBuff(void) {
  return LoadBuff(FLS_IMPMONCAN_BUFF, mpimMonCan[ ibSoftMon ], sizeof(impulse)*bCANALS);
}



boolean SaveImpAbsBuff(void) {
  return SaveBuff(FLS_IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS, FRM_REAL);
}


boolean LoadImpAbsBuff(void) {
  return LoadBuff(FLS_IMPABSCAN_BUFF, mpimAbsCan, sizeof(impulse)*bCANALS);
}



boolean SavePowDayBuff(void) {
  return SaveBuff(FLS_POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS, FRM_MAX_POWER);
}


boolean LoadPowDayBuff(void) {
  return LoadBuff(FLS_POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}



boolean SavePowMonBuff(void) {
  return SaveBuff(FLS_POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS, FRM_MAX_POWER);
}


boolean LoadPowMonBuff(void) {
  return LoadBuff(FLS_POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}



boolean SaveCntMonBuff(void) {
  return SaveBuff(FLS_CNTMONCAN_BUFF, mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS, FRM_REAL);
}


boolean LoadCntMonBuff(void) {
  return LoadBuff(FLS_CNTMONCAN_BUFF, mpreCntMonCan[ ibSoftMon ], sizeof(real)*bCANALS);
}

reset all
