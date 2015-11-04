/*------------------------------------------------------------------------------
TIMER1!C

TODO volatile
------------------------------------------------------------------------------*/
/*
#include "../main.h"
#include "inc/hw_memmap.h"
*/
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_memmap.h"
#include "self/main.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

volatile ulong dwTimer;

/*
#include "../display/slides.h"
#include "../impulses/impulses.h"
#include "../digitals/wait_answer.h"
#include "../digitals/wait_query.h"
#include "../output/unified/uni.h"
#include "../serial/flow.h"
#include "../serial/monitor.h"
#include "../serial/slave_modem.h"



extern  volatile bool           fOnSecond;


*/
void InitTimer1(uint32_t ui32SysClock) {
    // Enable the peripherals.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    // Configure the 32-bit periodic timer.
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, ui32SysClock / 1000);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // Enable the timer.
    TimerEnable(TIMER1_BASE, TIMER_A);
}



void Timer1IntHandler(void)
{
  HWREG(TIMER1_BASE + TIMER_O_ICR) = TIMER_TIMA_TIMEOUT;

  dwTimer++;
//  fOnSecond = 1;
//
//  Slides_1Hz();
//  Impulses_1Hz();
//
//  WaitAnswer_1Hz();
//  WaitQuery_1Hz();
//  DelayUni_1Hz();
//  DelayFlow_1Hz();
//  DelayMonitor_1Hz();
//  SlaveModem_1Hz();
}

