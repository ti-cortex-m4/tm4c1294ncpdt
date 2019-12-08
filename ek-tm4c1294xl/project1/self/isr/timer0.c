/*------------------------------------------------------------------------------
TIMER0!C

TODO volatile
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
#include "../keyboard/key.h"
#include "../display/lcd.h"
#include "../impulses/impulses.h"
#include "../digitals/digitals_pause.h"
#include "../hardware/pulse_generator.h"
#include "serial0.h"
#include "serial1.h"
#include "serial2.h"
#include "serial3.h"
#include "serial_flow.h"



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



void Timer0IntHandler(void)
{
  HWREG(TIMER0_BASE + TIMER_O_ICR) = TIMER_TIMA_TIMEOUT;

  InDelay0_Timer0();
  InDelay1_Timer0();
  InDelay2_Timer0();
  InDelay3_Timer0();
  InDelay_SerialFlow_Timer0();

  Pause();

  Impulses_Timer0();
#ifndef NO_DISPLAY
  LCD_Timer0();
  Key_Timer0();
#endif
  PulseGenerator_350Hz();
}
