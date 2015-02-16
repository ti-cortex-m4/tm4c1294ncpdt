/*------------------------------------------------------------------------------
TIMER1.C


------------------------------------------------------------------------------*/

#include 		"main.h"
#include 		"inc/hw_memmap.h"
#include 		"inc/hw_ints.h"
#include 		"driverlib/gpio.h"
#include 		"driverlib/interrupt.h"
#include 		"driverlib/sysctl.h"
#include 		"driverlib/timer.h"
#include 		"realtime/impulses.h"
#include 		"rtc.h"



void InitTimer1(uint32_t ui32SysClock) {
    // Enable the peripherals.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    // Configure the 32-bit periodic timer.
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, ui32SysClock / wFREQUENCY_T1);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // Enable the timer.
    TimerEnable(TIMER1_BASE, TIMER_A);
}



void Timer1IntHandler(void) {
	TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

	RTC_Timer1();
	Impulses_Timer1();
}
