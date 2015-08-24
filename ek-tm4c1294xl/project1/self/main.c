/*------------------------------------------------------------------------------
MAIN,C


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
#include "kernel/asserts.h"
#include "hardware/watchdog.h"
#include "hardware/system_clock.h"
#include "hardware/sys_tick.h"
#include "hardware/beep.h"
#include "display/lcd.h"
#include "time/rtc.h"
#include "keyboard/infrared.h"
#include "keyboard/key.h"
#include "keyboard/keyboard.h"
#include "nvram/23x1024.h"
#include "flash/flash.h"
#include "display/display.h"
#include "isr/timer0.h"
#include "isr/timer1.h"
#include "isr/timer2.h"
#include "isr/serial0.h"
#include "isr/serial1.h"
#include "isr/serial2.h"
#include "isr/serial3.h"
#include "hardware/memory.h"
#include "hardware/power_off.h"
#include "hardware/uart_loader.h"
#include "uarts.h"
#include "serial/modems.h"
#include "serial/print.h"
#include "flash/flash1.h"
#include "flash/flash2.h"
#include "flash/storage.h"
#include "flash/records.h"
#include "settings.h"
#include "impulses/impulses.h"
#include "impulses/factors.h"
#include "groups.h"
#include "tariffs/zones.h"
#include "tariffs/tariffs.h"
#include "tariffs/relaxs.h"
#include "tariffs/gaps.h"
#include "digitals/digitals.h"
#include "digitals/limits.h"
#include "digitals/params/params.h"
#include "digitals/profile/profile_core.h"
#include "devices/devices_init.h"
#include "devices/devices.h"
#include "digitals/phones.h"
#include "special/defects.h"
#include "serial/speeds.h"
#include "serial/flow.h"
#include "output/esc/esc.h"
#include "output/esc/response_esc.h"
#include "output/unified/uni.h"
#include "output/unified/response_uni.h"
#include "time/decret.h"
#include "time/gps.h"
#include "time/correct1.h"
#include "time/correct2.h"
#include "special/recalc.h"
#include "realtime/realtime.h"
#include "realtime/realtime_init.h"
#include "output/response_crc.h"



int     main(void)
{
  MakeSystemClockFrequency();
  const uint32_t ui32SysClockFreq = GetSystemClockFrequency();

  InitSysTick(ui32SysClockFreq);

  InitUart0(ui32SysClockFreq);
  InitUart2(ui32SysClockFreq);
  InitUart3(ui32SysClockFreq);
  InitUart4(ui32SysClockFreq);

  DisableWatchdog();

  InitBeep();
  InitLCD();
  InitNvram();
  InitFlash1();
  InitFlash2();
  InitRTC();
  InitCODE();

  InitAsserts();
  InitRecords();
  InitSettings();
  InitInfrared();
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
  InitGPS();
  InitCorrect1();
  InitCorrect2();
  InitDigitals();
  InitLimits();
  InitDevices1();
  InitParams();
  InitPhones();
  InitProfile();
  InitSpeeds();
  InitEsc();
  InitUni();
  InitFlow();
  InitPowerOff();

  InitSlide();

  PrintStart();
  InitStorage();
  InitDefects();
  InitRealtime();
  PrintStop();

  InitDisplay();

//  InitCurrent();
//  InitProfiles();
  InitDevices2();

  InitSerial0();
  InitSerial1();
  InitSerial2();
  InitSerial3();

  InitTimer0(ui32SysClockFreq);
  InitTimer1(ui32SysClockFreq);
  InitTimer2(ui32SysClockFreq);

  IntMasterEnable();

  InitRecalc();
  InitUartLoader();
  LongBeep();

  InitWatchdog();

  while (1)
  {
    ASSERT((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_WORK) || (enGlobal == GLB_REPROGRAM));

    ResetWatchdog();

    RunRealtime();
    RunDevices();
    RunInfrared();
    RunKeyboard();
    RunLocal();

    RunResponseCRC_All();
    RunResponseEsc_All();
    RunResponseUni_All();
    RunResponseFlow_All();
  }
}
