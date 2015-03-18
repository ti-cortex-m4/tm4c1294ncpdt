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
#include "src/beep.h"
#include "src/display/lcd.h"
#include "src/time/rtc.h"
#include "src/keyboard/key.h"
#include "src/keyboard/keyboard.h"
#include "src/flash/at45.h"
#include "src/display/display.h"
#include "src/isr/timer0.h"
#include "src/isr/timer1.h"
#include "src/isr/serial0.h"
#include "src/isr/serial1.h"
#include "src/isr/serial2.h"
#include "src/isr/serial3.h"
#include "src/uarts.h"
#include "src/serial/modems.h"
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
#include "src/digitals/profile_core.h"
#include "src/digitals/digitals_run.h"
#include "src/digitals/phones.h"
#include "src/serial/speeds.h"
#include "src/storage/storage.h"
#include "src/time/decret.h"
#include "src/realtime/realtime.h"
#include "src/realtime/realtime_init.h"
#include "src/output/response_crc.h"



int main(void) {
  ui32SysClock = GetSystemClockFrequency();

  InitUart0(ui32SysClock);
  InitUart2(ui32SysClock);
  InitUart3(ui32SysClock);
  InitUart4(ui32SysClock);

	InitBeep();
	InitLCD();
	InitFlash();            Delay(100); TestOK();
	InitRTC();

	InitSettings();         Delay(100); TestOK();
	InitKey();
	InitKeyboard();         Delay(100); TestOK();
	InitImpulses();
	InitFactors();
	InitGroups();           Delay(100); TestOK();
	InitZones();
	InitTariffs();          Delay(100); TestOK();
	InitRelaxs();
	InitGaps();             Delay(100); TestOK();
	InitDecret();
	InitDigitals();         Delay(100); TestOK();
	InitPhones();
	InitProfile();
	InitSpeeds();

	InitSlide();
	InitStorage();

  PrintStart();
	InitRealtime();
  PrintStop();

	InitDisplay();

    InitDevices();

    InitSerial0();
    InitSerial1();
    InitSerial2();
    InitSerial3();

    InitTimer0(ui32SysClock);
    InitTimer1(ui32SysClock);

    IntMasterEnable();

    while (1) {
    	ASSERT((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_WORK) || (enGlobal == GLB_REPROGRAM))

    	RunRealtime();
    	RunKeyboard();
    	RunDevices();
    	RunLocal();
    	RunResponseCRC_All();
    }
}
