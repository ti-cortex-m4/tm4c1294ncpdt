/*------------------------------------------------------------------------------
SPEEDS_STORAGE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../flash/files.h"
#include "speeds_storage.h"



file const              flPorts = {PORTS, &mppoPorts, sizeof(mppoPorts)};

file const              flLocalDisable = {LOCAL_DISABLE, &mpboLocalDisable, sizeof(mpboLocalDisable)};

file const              flMajorInDelay = {MAJOR_IN_DELAY, &mpwMajorInDelay, sizeof(mpwMajorInDelay)};
file const              flMinorInDelay = {MINOR_IN_DELAY, &mpwMinorInDelay, sizeof(mpwMinorInDelay)};



bool SavePorts(void) {
  return SaveFile(&flPorts);
}

bool LoadPorts(void) {
  return LoadFile(&flPorts);
}


bool SaveLocalDisable(void) {
  return SaveFile(&flLocalDisable);
}

bool LoadLocalDisable(void) {
  return LoadFile(&flLocalDisable);
}


bool SaveMajorInDelay(void) {
  return SaveFile(&flMajorInDelay);
}

bool LoadMajorInDelay(void) {
  return LoadFile(&flMajorInDelay);
}


bool SaveMinorInDelay(void) {
  return SaveFile(&flMinorInDelay);
}

bool LoadMinorInDelay(void) {
  return LoadFile(&flMinorInDelay);
}
