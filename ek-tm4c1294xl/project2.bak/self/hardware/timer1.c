/*------------------------------------------------------------------------------
timer1.c

------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "timer1.h"



#define TIMER1_FREQ     1000



void InitTimer1(ulong dwClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

  TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER1_BASE, TIMER_A, dwClockFreq / TIMER1_FREQ);

  IntEnable(INT_TIMER1A);
  TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

  TimerEnable(TIMER1_BASE, TIMER_A);
}



void Timer1IntHandler(void)
{
  HWREG(TIMER1_BASE + TIMER_O_ICR) = TIMER_TIMA_TIMEOUT;
}
