/*------------------------------------------------------------------------------
SPEEDS_STORAGE!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../nvram/cache.h"
#include "speeds_storage.h"



cache const             chPorts = {PORTS, &mppoPorts, sizeof(mppoPorts)};

cache const             chLocalDisable = {LOCAL_DISABLE, &mpboLocalDisable, sizeof(mpboLocalDisable)};

cache const             chMajorInDelay = {MAJOR_IN_DELAY, &mpwMajorInDelay, sizeof(mpwMajorInDelay)};
cache const             chMinorInDelay = {MINOR_IN_DELAY, &mpwMinorInDelay, sizeof(mpwMinorInDelay)};

cache const             chOutputDelay = {OUTPUT_DELAY, &mpwOutputDelay, sizeof(mpwOutputDelay)};
cache const             chTxDelay = {TX_DELAY, &mpwTxDelay, sizeof(mpwTxDelay)};



bool SavePorts(void) {
  return SaveCache(&chPorts);
}

bool LoadPorts(void) {
  return LoadCache(&chPorts);
}


bool SaveLocalDisable(void) {
  return SaveCache(&chLocalDisable);
}

bool LoadLocalDisable(void) {
  return LoadCache(&chLocalDisable);
}


bool SaveMajorInDelay(void) {
  return SaveCache(&chMajorInDelay);
}

bool LoadMajorInDelay(void) {
  return LoadCache(&chMajorInDelay);
}


bool SaveMinorInDelay(void) {
  return SaveCache(&chMinorInDelay);
}

bool LoadMinorInDelay(void) {
  return LoadCache(&chMinorInDelay);
}
