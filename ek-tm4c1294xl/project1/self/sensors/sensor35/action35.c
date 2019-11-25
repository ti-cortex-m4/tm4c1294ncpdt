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



uchar                   bMaxTimer35;



#ifndef SKIP_35

static void Delay35() {
  Delay(1000); // DelayInf();
}


static event35 event0(bool  fLog, result35  enResult, action35  enAction, uint  wData) {
  event35 event;
  event.fLog = fLog;
  event.enResult = enResult;
  event.enAction = enAction;
  event.wData = wData;
  return event;
}


static event35 Event35(bool  display) {
  if (InBuff(7) == NNCL2_TIME) {
    if (display) {
      sprintf(szHi+10,"%2u",GetTimer35());
      DelayOff();
    } else {
      sprintf(szLo+10,"%2u",GetTimer35());
      DelayOff();
    }

    if (GetTimer35() >= 99) {
      uint w = GetTimer35();
      MonitorString("\n repeat: error by timeout "); MonitorCharDec(w);
      Clear(); sprintf(szLo+2,"����� ? %u",w); Delay35();
      return event0(true, R35_REPEAT_ERROR_TIMEOUT, A35_ERROR, w);
    } else {
      MonitorString("\n repeat: start");
      return event0(false, R35_REPEAT_START, A35_WAIT, 0);
    }
  }
  else if (InBuff(7) == NNCL2_DATA_GET) {
    Timeout35(GetTimer35());

    if (IndexInBuff() < 15) {
      uint w = IndexInBuff();
      MonitorString("\n sensor error: bad size "); MonitorIntDec(w);
      Clear(); sprintf(szLo+2,"����� ? %u",w); Delay35();
      return event0(true, R35_ROUTER_ERROR_SIZE, A35_ERROR, w);
    } else {
      MonitorString("\n sensor success: good size ");

      uchar i;
      for (i=0; i<IndexInBuff()-15; i++)
        SetInBuff(i, InBuff(12+i));

      SetIndexInBuff(IndexInBuff()-15);

      MonitorString("\n unwrap finished"); MonitorIn();

      if (ChecksumSensor35() == 0) {
        MonitorString("\n sensor success");
        return event0(false, R35_SENSOR_SUCCESS, A35_SUCCESS, 0);
      } else {
        MonitorString("\n sensor failure");
        return event0(true, R35_SENSOR_FAILURE, A35_ERROR, 0);
      }
    }
  } else if (InBuff(7) == NNCL2_ERROR) {
    uint w = InBuff(12);
    MonitorString("\n router error: "); MonitorCharDec(w);
    Clear(); sprintf(szLo+2,"������ ? %u",w); Delay35();
    return event0(true, R35_ROUTER_ERROR_ERROR, A35_BREAK, w);
  } else {
    uint w = InBuff(7);
    MonitorString("\n router unknown command: "); MonitorCharDec(w);
    Clear(); sprintf(szLo+2,"������� ? %u",w); Delay35();
    return event0(true, R35_ROUTER_ERROR_COMMAND, A35_ERROR, w);
  }
}


action35 Action35(bool  display) {
  event35 event = Event35(display);
  if (event.fLog) {
    Log35(event.enResult, event.wData);
  }
  return event.enAction;
}

#endif