/*------------------------------------------------------------------------------
profile2mode.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "profile2mode.h"



bool    UseProfile2x1(void) {
  return (enProfile2Mode == BLOCK_1);
}


bool    UseProfile2x16(void) {
  return (enProfile2Mode == AUTOMATIC && !TestVersionB710())
         || (enProfile2Mode == BLOCK_16);
}


bool    UseProfile2x17(void) {
  return (enProfile2Mode == AUTOMATIC && TestVersionB710())
         || (enProfile2Mode == BLOCK_17);
}



bool    UseProfile2Top(void) {
}


bool    UseProfile2Top17(void) {
}
