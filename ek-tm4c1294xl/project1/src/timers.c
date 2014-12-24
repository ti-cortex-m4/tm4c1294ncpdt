#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

extern uint32_t g_ui32SysClock;

void InitTimers(void)
{
    // Enable the peripherals.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Configure the 32-bit periodic timer.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock / 1);

    // Enable processor interrupts.
    IntMasterEnable();

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Enable the timer.
    TimerEnable(TIMER0_BASE, TIMER_A);
}
