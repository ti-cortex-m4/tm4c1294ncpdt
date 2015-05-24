/*------------------------------------------------------------------------------
TIMER2.C

------------------------------------------------------------------------------*/

#include "../main.h"
#include "timer2.h"



void InitTimer2(uint32_t ui32SysClock)
{
  // Enable the peripherals.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

  // Configure the 32-bit periodic timer.
  TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER2_BASE, TIMER_A, ui32SysClock / F_INTERRUPTS);

  // Setup the interrupts for the timer timeouts.
  IntEnable(INT_TIMER2A);
  TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

  // Enable the timer.
  TimerEnable(TIMER2_BASE, TIMER_A);
}



void Timer2IntHandler(void)
{
  TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}
