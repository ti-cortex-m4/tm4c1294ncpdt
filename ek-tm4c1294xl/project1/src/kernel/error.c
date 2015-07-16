/*------------------------------------------------------------------------------
ERROR.C

 The error routine that is called if the driver library encounters an error.
------------------------------------------------------------------------------*/

#include <stdint.h>
#include "../hardware/beep.h"
#include "error.h"



#ifdef DEBUG

void __error__(char *pcFilename, uint32_t ui32Line)
{
  Beep();
  Beep();

  while(1)
  {
  }
}

#endif
