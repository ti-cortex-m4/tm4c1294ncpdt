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
#include "kernel/wdt.h"
#include "hardware/watchdog.h"
#include "hardware/system_clock.h"
#include "hardware/sys_tick.h"
#include "hardware/beep.h"
#include "hardware/uarts.h"
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
#include "isr/timer3.h"
#include "isr/serial0.h"
#include "isr/serial1.h"
#include "isr/serial2.h"
#include "isr/serial3.h"
#include "isr/serial_flow.h"
#include "hardware/memory.h"
#include "hardware/power_off.h"
#include "hardware/uart_loader.h"
#include "hardware/pulse_generator.h"
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
#include "digitals/current/current2.h"
#include "digitals/profile/profile_core.h"
#include "digitals/profile/profile_interval.h"
#include "digitals/extended/diagram.h"
#include "devices/devices_init.h"
#include "devices/devices.h"
#include "digitals/phones.h"
#include "digitals/phones2/phones2.h"
#include "digitals/address/ascii_address.h"
#include "special/defects.h"
#include "serial/speeds.h"
#include "serial/input_mode_reset.h"
#include "serial/slave_modem.h"
#include "serial/bulk.h"
#include "serial/flow.h"
#include "serial/auto_flow.h"
#include "serial/monitor.h"
#include "output/esc/esc.h"
#include "output/esc/response_esc.h"
#include "output/unified/uni.h"
#include "output/unified/response_uni.h"
#include "time/decret.h"
#include "time/gps.h"
#include "time/correct1.h"
#include "time/correct2.h"
#include "time/correct3.h"
#include "special/recalc.h"
#include "realtime/realtime.h"
#include "realtime/realtime_init.h"
#include "realtime/throughput.h"
#include "realtime/period30.h"
#include "output/response_crc.h"



int     main(void)
{
  MakeSystemClockFrequency();
  const uint32_t ui32SysClockFreq = GetSystemClockFrequency();

  InitSysTick(ui32SysClockFreq);

  InitUart0();
  InitUart2();
  InitUart3();
  InitUart4();

  DisableWatchdog();

  InitBeep();
  InitLCD();
  InitNvram();
  InitFlash1();
  InitFlash2();
  InitRTC();
  InitCODE();

  InitWDT();

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
  InitTariffs_Custom();
  InitRelaxs();
  InitGaps();
  InitDecret();
  InitGps();
  InitCorrect1();
  InitCorrect2();
  InitCorrect3();
  InitDigitals();
  InitLimits();
  InitDevices1();
  InitParams();
  InitPhones();
  InitPhones2();
  InitAsciiAddress();
  InitProfile();
  InitProfileInterval();
  InitSpeeds();
  InitInputModeReset();
  InitSlaveModem();
  InitBulk();
  InitEsc();
  InitUni();
  InitFlow();
  InitAutoFlow();
  InitMonitor();

  InitSlide();

  PrintStart();
  InitStorage();
  InitDefects_Custom();
  InitRealtime_Custom();
  InitThroughput();
  InitPeriod30();
  InitDiagram();
  PrintStop();

  InitDisplay();

//  InitCurrent();
  InitCurrent2();
//  InitProfiles();
  InitDevices2();

  InitSerial0();
  InitSerial1();
  InitSerial2();
  InitSerial3();
  InitSerialFlow();

  InitTimer0(ui32SysClockFreq);
  InitTimer1(ui32SysClockFreq);
  InitTimer2(ui32SysClockFreq);
  InitTimer3(ui32SysClockFreq);

  InitRecalc();

  InitPowerOff();
  InitUartLoader();
  InitPulseGenerator();

  IntMasterEnable();
  LongBeep();

  while (1)
  {
    ASSERT((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_WORK) || (enGlobal == GLB_REPROGRAM));

Lo(12, ToBCD(ibDig));
Lo(14, ToBCD(GetProfileIntervalDig()));

    ResetWatchdog();

    RunRealtime();
    RunDevices();
    RunInfrared();
    RunKeyboard();

    RunLocal_All();
    RunSlaveModem_All();

    RunResponseCRC_All();
    RunResponseEsc_All();
    RunResponseUni_All();
    RunResponseSerialFlow_All();
    RunResponseFlow_All();

    RunThroughput();
  }
}
