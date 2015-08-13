/*------------------------------------------------------------------------------
ERROR.C

 The error routine that is called if the driver library encounters an error.
------------------------------------------------------------------------------*/

#include <stdint.h>
#include "../hardware/beep.h"
#include "asserts.h"



void __error__(char  *pcFilename, uint32_t  ui32Line)
{
  Beep();
  Beep();

  AddAssert(pcFilename, ui32Line);

  while(1)
  {
  }
}
