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
#include "src/rtc.h"
#include "src/timers.h"
#include "src/uarts.h"
#include "src/postinput_crc.h"

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

	InitRTC();
    InitUARTs(ui32SysClock);
    InitTimers(ui32SysClock);
    IntMasterEnable();

    while(1) {
    	PostinputCRC_Full();
    }
}
