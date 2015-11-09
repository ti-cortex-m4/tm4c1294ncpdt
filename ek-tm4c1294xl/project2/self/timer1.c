/*------------------------------------------------------------------------------
TIMER.C

------------------------------------------------------------------------------*/

#include "main.h"
#include "serial/log.h"
//#include "serial/serial4.h"
#include "inc/hw_memmap.h"
//#include "inc/hw_memmap.h"
//#include "self/main.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
//#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "serial/serial.h"
#include "serial/serial4.h"
#include "timer1.h"



#define TIMER1_FREQ     1000



void    InitTimer1(ulong dwSysClockFreq)
{
  // Enable the peripherals.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

  // Configure the 32-bit periodic timer.
  TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER1_BASE, TIMER_A, dwSysClockFreq / TIMER1_FREQ);

  // Setup the interrupts for the timer timeouts.
  IntEnable(INT_TIMER1A);
  TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

  // Enable the timer.
  TimerEnable(TIMER1_BASE, TIMER_A);
}


void Timer1IntHandler(void)
{
  HWREG(TIMER1_BASE + TIMER_O_ICR) = TIMER_TIMA_TIMEOUT;

  LogTimer_1000Hz();
  uart_timer();
}
