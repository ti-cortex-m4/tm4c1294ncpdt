/*------------------------------------------------------------------------------
action35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include35.h"
#include "unpack35.h"
#include "io35.h"
#include "timer35.h"
#include "timeout35.h"
#include "log35.h"
#include "action35.h"



#ifndef SKIP_35

static void Delay35() {
  Delay(1000); // DelayInf();
}


static step35 event1(bool fLog, event35 enEvent, action35 enAction, uint  wData) {
  step35 step1;
  step1.fLog = fLog;
  step1.enEvent = enEvent;
  step1.enAction = enAction;
  step1.wData = wData;
  return step1;
}


static step35 Step35(bool hi) {
  if (InBuff(7) == NNCL2_TIME) {
    if (hi) {
      sprintf(szHi+10,"%2u",GetTimer35());
      Delay(300); // Inf
    } else {
      sprintf(szLo+10,"%2u",GetTimer35());
      Delay(500); // TODO 35
    }

    if (GetTimer35() >= 99) {
      uint w = GetTimer35();
      MonitorString("\n repeat: error by timeout "); MonitorCharDec(w);
      Clear(); sprintf(szLo+1,"время ? %u",w); Delay35();
      return event1(true, E35_REPEAT_ERROR_TIMEOUT, A35_ERROR, w);
    } else {
      MonitorString("\n repeat: start");
      return event1(false, E35_REPEAT_START, A35_WAIT, 0);
    }
  }
  else if (InBuff(7) == NNCL2_DATA_GET) {
    Timeout35(GetTimer35());

    if (IndexInBuff() < 15) {
      uint w = IndexInBuff();
      MonitorString("\n sensor error: bad size "); MonitorIntDec(w);
      Clear(); sprintf(szLo+1,"длина ? %u",w); Delay35();
      return event1(true, E35_ROUTER_ERROR_SIZE, A35_ERROR, w);
    }
    else {
      MonitorString("\n sensor success: good size ");

      uchar i;
      for (i=0; i<IndexInBuff()-15; i++)
        SetInBuff(i, InBuff(12+i));

      MonitorString("\n unwrap finished"); MonitorIn();

      if (Checksum35Sensor() == 0) {
        MonitorString("\n sensor success");
        return event1(false, E35_SENSOR_SUCCESS, A35_SUCCESS, 0);
      }
      else {
        MonitorString("\n sensor failure");
        return event1(true, E35_SENSOR_FAILURE, A35_ERROR, 0);
      }
    }
  }
  else if (InBuff(7) == NNCL2_ERROR) {
    uint w = InBuff(12);
    MonitorString("\n router error: "); MonitorCharDec(w);
    Clear(); sprintf(szLo+1,"ошибка ? %u",w); Delay35();
    return event1(true, E35_ROUTER_ERROR_ERROR, A35_ERROR, w);
  }
  else {
    uint w = InBuff(7);
    MonitorString("\n router unknown command: "); MonitorCharDec(w);
    Clear(); sprintf(szLo+1,"команда ? %u",w); Delay35();
    return event1(true, E35_ROUTER_ERROR_COMMAND, A35_ERROR, w);
  }
}


action35 Action35(bool  hi) {
  step35 step = Step35(hi);
  if (step.fLog) {
    Log35(step.enEvent, step.wData);
  }
  return step.enAction;
}

#endif
