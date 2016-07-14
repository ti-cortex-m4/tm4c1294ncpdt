/*------------------------------------------------------------------------------
restart.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/sysctl.h"
#include "restart.h"



void Restart(void)
{
  SysCtlReset();
}
