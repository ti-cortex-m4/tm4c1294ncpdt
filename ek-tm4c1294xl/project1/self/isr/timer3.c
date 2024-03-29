/*------------------------------------------------------------------------------
TIMER3.C

������ ��� ��������� ������������������ (10 Hz)
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "../realtime/throughput.h"
#include "timer3.h"



volatile bool           f10Hz;



void    InitTimer3(uint32_t ui32SysClock)
{
  // Enable the peripherals.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);

  // Configure the 32-bit periodic timer.
  TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER3_BASE, TIMER_A, ui32SysClock / 10);

  // Setup the interrupts for the timer timeouts.
  IntEnable(INT_TIMER3A);
  TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

  // Enable the timer.
  TimerEnable(TIMER3_BASE, TIMER_A);
}



void    Timer3IntHandler(void)
{
  HWREG(TIMER3_BASE + TIMER_O_ICR) = TIMER_TIMA_TIMEOUT;

  f10Hz = true;

  Throughput_10Hz();
}
