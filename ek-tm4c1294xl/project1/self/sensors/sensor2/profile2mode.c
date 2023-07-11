/*------------------------------------------------------------------------------
profile2mode.h


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "profile2mode.h"



bool    UseProfile2x17(void) {
  return (enProfile2Mode == P2M_AUTOMATIC && TestVersionB710())
         || (enProfile2Mode == P2M_SIZE17);
}


bool    UseProfile2x1(void) {
  return (enProfile2Mode == P2M_SIZE1);
}



bool    UseProfile2Top(void) {
}


bool    UseProfile2Top17(void) {
}
