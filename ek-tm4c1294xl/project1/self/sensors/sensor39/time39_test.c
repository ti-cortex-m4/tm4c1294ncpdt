/*------------------------------------------------------------------------------
time39_test.c

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/rtc.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "device39.h"
#include "time39.h"
#include "io39.h"
#include "fragment_open_time_39.h"
#include "time39.h"
#include "time39_test.h"



#ifdef  MONITOR_39

double2 TestTimeCorrect39(void)
{
//  fMonitorLogBasic = false;
//  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller();

  time2 tmThat1 = FragmentOpenTime39(&c);
  if (!tmThat1.fValid) return GetDouble2Error1(1);


  time tmThis1 = *GetCurrTimeDate();
  slong wDeltaSeconds1 = GetSecondIndex(tmThis1) - GetSecondIndex(tmThat1.tiValue);
  MonitorString("\n before correction ");
  MonitorString("\n this:  "); MonitorTime(tmThis1);
  MonitorString("\n that:  "); MonitorTime(tmThat1.tiValue);
  MonitorString("\n delta: "); MonitorSignedLongDec(wDeltaSeconds1);


  c.bNS++;
  c.bInvokeId++;
  QueryCorrectTime39(c.bNS, c.bNR, c.bInvokeId, wDeltaSeconds1);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(2);
  if (ValidateFrame(c.bNS, c.bNR) == 100/*!= 0*/) return GetDouble2Error1(3);


  c.bNS++;
  c.bInvokeId++;
  QueryTime39(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(4);
  if (ValidateFrame(c.bNS, c.bNR) == 100/*!= 0*/) return GetDouble2Error1(5);
  time tmThat2 = ReadTime39();

  c.bNR++;
  Query39_RR(c.bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(6);
  if (ValidateFrame(c.bNS, c.bNR) == 100/*!= 0*/) return GetDouble2Error1(7);


  time tmThis2 = *GetCurrTimeDate();
  slong wDeltaSeconds2 = GetSecondIndex(tmThis2) - GetSecondIndex(tmThat2);
  MonitorString("\n after correction ");
  MonitorString("\n this:  "); MonitorTime(tmThis2);
  MonitorString("\n that:  "); MonitorTime(tmThat2);
  MonitorString("\n delta: "); MonitorSignedLongDec(wDeltaSeconds2);


  return GetDouble2(0, true);
}

#endif

