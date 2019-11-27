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
  Delay(1000); // DelayInf(); TODO 35
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
    uint tm = GetTimer35();
    if (display) {
      if (tm > 99) sprintf(szHi+10,"%2X",tm); else sprintf(szHi+10,"%2u",tm);
      DelayOff();
    } else {
      if (tm > 99) sprintf(szLo+10,"%2X",tm); else sprintf(szLo+10,"%2u",tm);
      DelayOff();
    }

    if (GetTimer35() >= bMaxTimer35) {
      uint w = GetTimer35();
      MonitorString("\t repeat: error by timeout "); MonitorCharDec(w);
      Clear(); sprintf(szLo+2,"время ? %u",w); Delay35();
      return event0(true, R35_REPEAT_ERROR_TIMEOUT, A35_ERROR, w);
    } else {
      MonitorString("\t repeat: start");
      return event0(false, R35_REPEAT_START, A35_WAIT, 0);
    }
  }
  else if (InBuff(7) == NNCL2_DATA_GET) {
    Timeout35(GetTimer35());

    if (IndexInBuff() < 15) {
      uint w = IndexInBuff();
      MonitorString("\t sensor error: bad size "); MonitorIntDec(w);
      Clear(); sprintf(szLo+2,"длина ? %u",w); Delay35();
      return event0(true, R35_ROUTER_ERROR_SIZE, A35_ERROR, w);
    } else {
      MonitorString("\t sensor success: good size ");

      uchar i;
      for (i=0; i<IndexInBuff()-15; i++)
        SetInBuff(i, InBuff(12+i));

      SetIndexInBuff(IndexInBuff()-15);

      MonitorString("\t unwrap finished"); MonitorIn();

      if (ChecksumSensor35() == 0) {
        MonitorString("\t sensor success");
        return event0(false, R35_SENSOR_SUCCESS, A35_SUCCESS, 0);
      } else {
        MonitorString("\t sensor failure");
        return event0(true, R35_SENSOR_FAILURE, A35_ERROR, 0);
      }
    }
  } else if (InBuff(7) == NNCL2_ERROR) {
    uint w = InBuff(12);
    MonitorString("\t router error: "); MonitorCharDec(w);
    Clear(); sprintf(szLo+2,"ошибка ? %u",w); Delay35();
    return event0(true, R35_ROUTER_ERROR_ERROR, A35_BREAK, w);
  } else {
    uint w = InBuff(7);
    MonitorString("\t router unknown command: "); MonitorCharDec(w);
    Clear(); sprintf(szLo+2,"команда ? %u",w); Delay35();
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
