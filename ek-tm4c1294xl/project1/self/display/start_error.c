/*------------------------------------------------------------------------------
start_error.c


------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "../main.h"
#include "../serial/speeds.h"
#include "../hardware/system_clock.h"
#include "../hardware/watchdog.h"
#include "../isr/timer0.h"
#include "../isr/timer1.h"
#include "../isr/timer2.h"
#include "../isr/timer3.h"
#include "../isr/serial0.h"
#include "../isr/serial1.h"
#include "../isr/serial2.h"
#include "../isr/serial3.h"
#include "../output/response_crc.h"
#include "../output/esc/response_esc.h"
#include "../display/display.h"
#include "../display/messages.h"
#include "start_error.h"



#ifdef NO_DISPLAY
void    StartError(const char  *sz)
{
  ShowHi(szAlarm);
  ShowLo(sz);

  InitSpeeds(); // TODO

  InitSerial0();
  InitSerial1();
  InitSerial2();
  InitSerial3();

  const uint32_t ui32SysClockFreq = GetSystemClockFrequency();
  InitTimer0(ui32SysClockFreq); // TODO
  InitTimer1(ui32SysClockFreq); // TODO
  InitTimer2(ui32SysClockFreq); // TODO
  InitTimer3(ui32SysClockFreq); // TODO

  IntMasterEnable();

  while (1)
  {
    ResetWatchdog();

    RunResponseCRC_All_StartError(); // TODO
    RunResponseEsc_All_StartError(); // TODO
  }
}
#endif
