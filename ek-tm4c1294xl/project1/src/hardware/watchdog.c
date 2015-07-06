/*------------------------------------------------------------------------------
WATCHDOG.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/watchdog.h"
#include "../memory/mem_program.h"
#include "watchdog.h"



#define WATCHDOG_LOAD   (ulong)(0x20000000)



void    InitWDT(void)
{
  if (boEnblWDT == true)
    EnableWDT();
}


void    EnableWDT(void)
{
#ifdef ENABLE_WATCHDOG

  HWREG(SYSCTL_RCGCWD) |= SYSCTL_RCGCWD_R0;

  WatchdogReloadSet(WATCHDOG0_BASE, WATCHDOG_LOAD);

  WatchdogEnable(WATCHDOG0_BASE);
  WatchdogResetEnable(WATCHDOG0_BASE);
  WatchdogStallEnable(WATCHDOG0_BASE);

#endif
}


void    DisableWDT(void)
{
#ifdef ENABLE_WATCHDOG

  HWREG(SYSCTL_RCGCWD) |= SYSCTL_RCGCWD_R0;

  WatchdogReloadSet(WATCHDOG0_BASE, WATCHDOG_LOAD);

//  WatchdogDisable(WATCHDOG0_BASE);
  WatchdogResetDisable(WATCHDOG0_BASE);
//  WatchdogStallEnable(WATCHDOG0_BASE);

#endif
}


void    ResetWDT(void)
{
#ifdef ENABLE_WATCHDOG

  WatchdogReloadSet(WATCHDOG0_BASE, WATCHDOG_LOAD);

#endif
}


bool    IsResetWDT(void)
{
  return false;
}
