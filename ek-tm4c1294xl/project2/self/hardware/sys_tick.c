/*------------------------------------------------------------------------------
SYSTICK,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/systick.h"
#include "utils/lwiplib_patched.h"
#include "sys_tick.h"



//
// Defines for setting up the system clock.
//
#define SYSTICKHZ               100
#define SYSTICKMS               (1000 / SYSTICKHZ)


//*****************************************************************************
// External Reference.
//*****************************************************************************
extern uint32_t g_ulSystemTimeMS;



//*****************************************************************************
//! Handles the SysTick interrupt.
//!
//! This function is called when the SysTick timer expires.  It increments the
//! lwIP timers and sets a flag indicating that the timeout functions need to
//! be called if necessary.
//!
//! \return None.
//*****************************************************************************
void    SysTickIntHandler(void)
{
    // Increment a local system time.
    g_ulSystemTimeMS += SYSTICKMS;

    // Call the lwIP timer handler.
    lwIPTimer(SYSTICKMS);
}



void InitSysTick(ulong dwClockFreq)
{
  SysTickPeriodSet(dwClockFreq / SYSTICKHZ);
  SysTickEnable();
  SysTickIntEnable();
}
