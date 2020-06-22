/*------------------------------------------------------------------------------
time39_test.c

------------------------------------------------------------------------------*/

#include "../../main.h"
// #include "../../memory/mem_factors.h"
// #include "../../memory/mem_energy_spec.h"
// #include "../../display/display.h"
// #include "../../keyboard/keyboard.h"
// #include "../../keyboard/time/key_timedate.h"
 #include "../../time/timedate.h"
 #include "../../time/calendar.h"
 #include "../../time/rtc.h"
 #include "../../serial/monitor.h"
 #include "../../serial/monitor_settings.h"
// #include "../../devices/devices.h"
// #include "../../devices/devices_time.h"
// #include "../../digitals/limits.h"
// #include "../../special/special.h"
//#include "../../kernel/tuples.h"
#include "device39.h"
#include "time39.h"
#include "io39.h"
//#include "buffer_record_39.h"
#include "fragment_open_time_39.h"
//#include "fragment_profile_39.h"
//#include "buffer_profile_39.h"
#include "time39.h"
#include "time39_test.h"



#ifdef  MONITOR_39

double2 TestTimeCorrect39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller();

  time2 tmA = FragmentOpenTime39(&c);
  if (!tmA.fValid) return GetDouble2Error1(1);


  time tmSensor1 = tmA.tiValue;
  time tmMaster1 = *GetCurrTimeDate();
  ulong wDeltaSeconds1 = AbsLong(GetSecondIndex(tmSensor1) - GetSecondIndex(tmMaster1));
  MonitorString("\n before correction ");
  MonitorString("\n sensor: "); MonitorTime(tmSensor1);
  MonitorString("\n master: "); MonitorTime(tmMaster1);
  MonitorString("\n delta:  "); MonitorLongDec(wDeltaSeconds1);


  QueryCorrectTime39(c.bNS, c.bNR, c.bInvokeId, wDeltaSeconds1);


  c.bNS++;
  c.bInvokeId++;
  QueryTime39(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(2);
  if (!ValidateFrame(c.bNS, c.bNR)) return GetDouble2Error1(3);
  time tmSensor2 = ReadTime39();

  c.bNR++;
  Query39_RR(c.bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(4);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return GetDouble2Error1(5);


  time tmMaster2 = *GetCurrTimeDate();
  ulong wDeltaSeconds2 = AbsLong(GetSecondIndex(tmSensor2) - GetSecondIndex(tmMaster2));
  MonitorString("\n after correction ");
  MonitorString("\n sensor: "); MonitorTime(tmSensor2);
  MonitorString("\n master: "); MonitorTime(tmMaster2);
  MonitorString("\n delta:  "); MonitorLongDec(wDeltaSeconds2);


  return GetDouble2(0, true);
}

#endif

