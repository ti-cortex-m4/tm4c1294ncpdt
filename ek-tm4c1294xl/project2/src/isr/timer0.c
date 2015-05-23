/*------------------------------------------------------------------------------
TIMER0.C

TODO volatile
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "../keyboard/key.h"
#include "../display/lcd.h"



void InitTimer0(uint32_t ui32SysClock) {
    // Enable the peripherals.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Configure the 32-bit periodic timer.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / wFREQUENCY_T0);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Enable the timer.
    TimerEnable(TIMER0_BASE, TIMER_A);
}



void Timer0IntHandler(void) {
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	LCD_Timer0();
	Key_Timer0();
}
