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



boolean SavePorts(void) {
  return SaveFile(&flPorts);
}

boolean LoadPorts(void) {
  return LoadFile(&flPorts);
}


boolean SaveLocalDisable(void) {
  return SaveFile(&flLocalDisable);
}

boolean LoadLocalDisable(void) {
  return LoadFile(&flLocalDisable);
}


boolean SaveMajorInDelay(void) {
  return SaveFile(&flMajorInDelay);
}

boolean LoadMajorInDelay(void) {
  return LoadFile(&flMajorInDelay);
}


boolean SaveMinorInDelay(void) {
  return SaveFile(&flMinorInDelay);
}

boolean LoadMinorInDelay(void) {
  return LoadFile(&flMinorInDelay);
}
