/*------------------------------------------------------------------------------
profile2mode.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../devices/devices_init.h"
#include "device2.h"
#include "profile2mode.h"



bool    UseProfile2x17(void) { // TODO or by canals
  return (enProfile2Mode == P2M_AUTOMATIC && TestVersionB710())
         || (enProfile2Mode == P2M_SIZE_17);
}


bool    UseProfile2x1(void) { // TODO or by canals
  return (enProfile2Mode == P2M_SIZE_1);
}
