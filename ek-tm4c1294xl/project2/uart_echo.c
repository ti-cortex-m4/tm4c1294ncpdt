/*------------------------------------------------------------------------------
TODO .C


------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "src/hardware/system_clock.h"
#include "src/hardware/beep.h"
#include "src/display/lcd.h"
#include "src/time/rtc.h"
#include "src/keyboard/key.h"
#include "src/keyboard/keyboard.h"
#include "src/display/display.h"
#include "src/isr/timer0.h"
#include "src/isr/timer1.h"
#include "src/hardware/memory.h"
#include "src/uarts.h"
#include "src/serial/print.h"



extern int main2 (void);


int main(void) {
  ui32SysClock = GetSystemClockFrequency();

//  InitUart0(ui32SysClock);
//  InitUart2(ui32SysClock);
//  InitUart3(ui32SysClock);
//  InitUart4(ui32SysClock);

	InitBeep();
	InitLCD();
	InitRTC();
	InitCODE();

	InitKey();
	InitKeyboard();         Delay(100); TestOK();

	InitSlide();

    InitTimer0(ui32SysClock);
    InitTimer1(ui32SysClock);
    PrintStart();

    main2();

    IntMasterEnable();
    LongBeep();

    while (1) {
    	ASSERT((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_WORK) || (enGlobal == GLB_REPROGRAM));
    	RunKeyboard();
    }
}
