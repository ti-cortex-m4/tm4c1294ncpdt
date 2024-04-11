/*------------------------------------------------------------------------------
timer2.c

------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "../kernel/clock.h"
#include "../kernel/link_status_up.h"
#include "../uart/modem.h"
#include "../uart/server_to_modem.h"
#include "../uart/modem_to_server.h"
#include "timer2.h"



#define TIMER2_FREQUENCY    10



void InitTimer2(ulong dwClockFreq)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

  TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER2_BASE, TIMER_A, dwClockFreq / TIMER2_FREQUENCY);

  IntEnable(INT_TIMER2A);
  TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

  TimerEnable(TIMER2_BASE, TIMER_A);
}



void Timer2IntHandler(void)
{
  HWREG(TIMER2_BASE + TIMER_O_ICR) = TIMER_TIMA_TIMEOUT;

  static uchar i;
  if (++i >= 10)
  {
    i = 0;

    Clock_1Hz();
    ModemToServer_1Hz();
    LinkUpReset_1Hz();
  }

  Modem_10Hz();
  ServerToModem_10Hz();
}
