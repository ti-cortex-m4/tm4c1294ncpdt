/*------------------------------------------------------------------------------
start_error.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../isr/timer0.h"
#include "../isr/timer1.h"
#include "../isr/timer2.h"
#include "../isr/timer3.h"
#include "../isr/serial0.h"
#include "../isr/serial1.h"
#include "../isr/serial2.h"
#include "../isr/serial3.h"
#include "start_error.h"



#ifdef NO_DISPLAY

void    StartError()
{
  InitSpeeds();

  InitSerial0();
  InitSerial1();
  InitSerial2();
  InitSerial3();

  const uint32_t ui32SysClockFreq = GetSystemClockFrequency();
  InitTimer0(ui32SysClockFreq);
  InitTimer1(ui32SysClockFreq);
  InitTimer2(ui32SysClockFreq);
  InitTimer3(ui32SysClockFreq);

  IntMasterEnable();

  while (1)
  {
    ResetWatchdog();

//    RunLocal_All();
//    RunSlaveModem_All();
//
    RunResponseCRC_All();
//    RunResponseEsc_All();
//    RunResponseUni_All();
//    RunResponseFlow_All();
//
//    RunThroughput();
  }
}

#endif
