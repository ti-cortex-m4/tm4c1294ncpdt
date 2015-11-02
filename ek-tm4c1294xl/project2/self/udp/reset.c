/*------------------------------------------------------------------------------
RESET.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../delay.h"
#include "driverlib/sysctl.h"
#include "reset.h"



void Reset(void)
{
  Delay(100);
  SysCtlReset();
}
