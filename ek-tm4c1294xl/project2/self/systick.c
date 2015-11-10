/*------------------------------------------------------------------------------
SYSTICK.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "driverlib/systick.h"
#include "utils/lwiplib_patched.h"
#include "systick.h"



//
// Defines for setting up the system clock.
//
#define SYSTICKHZ               100
#define SYSTICKMS               (1000 / SYSTICKHZ)



//
// The interrupt handler for the SysTick interrupt.
//
void    SysTickIntHandler(void)
{
  lwIPTimer(SYSTICKMS);
}



void    InitSysTick(ulong dwSysClockFreq)
{
  //
  // Configure SysTick for a periodic interrupt.
  //
  SysTickPeriodSet(dwSysClockFreq / SYSTICKHZ);
  SysTickEnable();
  SysTickIntEnable();
}
