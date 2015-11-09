/*------------------------------------------------------------------------------
RESET.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../delay.h"
#include "driverlib/sysctl.h"
#include "reset.h"



void Reset(void)
{
  DelayMillySecond(100);
  SysCtlReset();
}
