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
#include "src/beep.h"
#include "src/display/lcd.h"
#include "src/time/rtc.h"
#include "src/keyboard/key.h"
#include "src/keyboard/keyboard.h"
#include "src/flash/at45.h"
#include "src/display/display.h"
#include "src/timer0.h"
#include "src/timer1.h"
#include "src/uarts.h"
#include "src/serial/print.h"
#include "src/settings.h"
#include "src/impulses/impulses.h"
#include "src/factors.h"
#include "src/groups.h"
#include "src/tariffs/zones.h"
#include "src/tariffs/tariffs.h"
#include "src/tariffs/relaxs.h"
#include "src/tariffs/gaps.h"
#include "src/digitals/digitals.h"
#include "src/storage/storage.h"
#include "src/time/decret.h"
#include "src/realtime/realtime.h"
#include "src/realtime/realtime_init.h"
#include "src/output/response_crc.h"


 void InitSerial0();

int main(void) {
	uint32_t ui32SysClock;

    // Set the clocking to run directly from the crystal at 120MHz.
	ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);
  InitUARTs(ui32SysClock);

	InitBeep();
	InitLCD();
	InitFlash();
	InitRTC();

	InitSettings();
	InitKey();
	InitKeyboard();
	InitImpulses();
	InitFactors();
	InitGroups();
	InitZones();
	InitTariffs();
	InitRelaxs();
	InitGaps();
	InitDecret();
	InitDigitals();

	InitSlide();
	InitStorage();

  PrintStart();
	InitRealtime();
  PrintStop();

	InitDisplay();

    InitSerial0();

    // Enable the UART interrupt.
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);

    InitTimer0(ui32SysClock);
    InitTimer1(ui32SysClock);

    IntMasterEnable();

    while (1) {
    	ASSERT((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_WORK) || (enGlobal == GLB_REPROGRAM))

    	Realtime();
    	Keyboard();
    	ResponseCRC_Full();
    }
}
