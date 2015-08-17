/*------------------------------------------------------------------------------
ERROR.C

 Функция вызывается из макроса ASSERT в driverlib/debug.h
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
