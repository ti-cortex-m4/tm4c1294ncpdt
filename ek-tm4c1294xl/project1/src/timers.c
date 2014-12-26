/*------------------------------------------------------------------------------
TIMERS.C


------------------------------------------------------------------------------*/

#include 		"main.h"
#include 		"inc/hw_memmap.h"
#include 		"inc/hw_ints.h"
//#include 		"driverlib/debug.h"
//#include 		"driverlib/fpu.h"
#include 		"driverlib/gpio.h"
#include 		"driverlib/interrupt.h"
//#include 		"driverlib/pin_map.h"
//#include 		"driverlib/rom.h"
//#include 		"driverlib/rom_map.h"
#include 		"driverlib/sysctl.h"
#include 		"driverlib/timer.h"
//#include 		"driverlib/uart.h"
#include 		"serial0.h"



void InitTimers(uint32_t ui32SysClock) {
    // Enable the peripherals.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Configure the 32-bit periodic timer.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock / 1);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Enable the timer.
    TimerEnable(TIMER0_BASE, TIMER_A);
}



void Timer0IntHandler(void) {
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	InDelay0();

    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
    SysCtlDelay(5000);
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
}
