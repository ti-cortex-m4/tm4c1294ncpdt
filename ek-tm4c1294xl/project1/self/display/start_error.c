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
#include "start_error.h"



#ifdef NO_DISPLAY

void    StartError()
{
  InitSpeeds(); // TODO

  InitSerial0(); // TODO
  InitSerial1(); // TODO
  InitSerial2(); // TODO
  InitSerial3(); // TODO

  const uint32_t ui32SysClockFreq = GetSystemClockFrequency(); // TODO
  InitTimer0(ui32SysClockFreq); // TODO
  InitTimer1(ui32SysClockFreq); // TODO
  InitTimer2(ui32SysClockFreq); // TODO
  InitTimer3(ui32SysClockFreq); // TODO

  IntMasterEnable();

  while (1)
  {
    ResetWatchdog(); // TODO

//    RunLocal_All(); // TODO
//    RunSlaveModem_All(); // TODO
//
    RunResponseCRC_All(); // TODO
    RunResponseEsc_All(); // TODO
//    RunResponseUni_All(); // TODO
//    RunResponseFlow_All(); // TODO
//
//    RunThroughput(); // TODO
  }
}

#endif
