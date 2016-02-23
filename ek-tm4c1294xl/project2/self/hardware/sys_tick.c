/*------------------------------------------------------------------------------
sys_tick.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/systick.h"
#include "utils/lwiplib_patched.h"
#include "sys_tick.h"



#define SYS_TICK_FREQ   100
#define SYS_TICK_PERIOD (1000 / SYS_TICK_FREQ) // milliseconds



//*****************************************************************************
//! Handles the SysTick interrupt.
//!
//! This function is called when the SysTick timer expires.  It increments the
//! lwIP timers and sets a flag indicating that the timeout functions need to
//! be called if necessary.
//!
//! \return None.
//*****************************************************************************
void SysTickIntHandler(void)
{
  // Increment a local system time.
  g_ulSystemTimeMS += SYS_TICK_PERIOD;

  // Call the lwIP timer handler.
  lwIPTimer(SYS_TICK_PERIOD);
}



void InitSysTick(ulong dwClockFreq)
{
  SysTickPeriodSet(dwClockFreq / SYS_TICK_FREQ);
  SysTickEnable();
  SysTickIntEnable();
}
