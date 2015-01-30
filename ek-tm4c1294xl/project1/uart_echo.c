//*****************************************************************************
//
//*****************************************************************************

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
#include "src/display/lcd.h"
#include "src/rtc.h"
#include "src/keyboard.h"
#include "src/flash/at45.h"
#include "src/display.h"
#include "src/slide.h"
#include "src/timer0.h"
#include "src/timer1.h"
#include "src/uarts.h"
#include "src/groups.h"
#include "src/output/response_crc.h"

// The error routine that is called if the driver library encounters an error.
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
}
#endif

int main(void) {
	uint32_t ui32SysClock;

    // Set the clocking to run directly from the crystal at 120MHz.
	ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);

	InitLCD();
	InitFlash();
	InitRTC();
	InitKeyboard();
	InitSlide();
	InitDisplay();

	InitGroups();

    InitUARTs(ui32SysClock);
    InitTimer0(ui32SysClock);
    InitTimer1(ui32SysClock);

    IntMasterEnable();

    while(1) {
    	Keyboard();
    	ResponseCRC_Full();
    }
}
