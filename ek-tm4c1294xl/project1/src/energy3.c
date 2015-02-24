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



bool    SavePowDayBuff(void) {
  return SaveBuff(DF_POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}


bool    LoadPowDayBuff(void) {
  return LoadBuff(DF_POWDAYGRP_BUFF, mppoDayGrp[ ibSoftDay ], sizeof(power)*bGROUPS);
}



bool    SavePowMonBuff(void) {
  return SaveBuff(DF_POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}


bool    LoadPowMonBuff(void) {
  return LoadBuff(DF_POWMONGRP_BUFF, mppoMonGrp[ ibSoftMon ], sizeof(power)*bGROUPS);
}
