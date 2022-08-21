/*------------------------------------------------------------------------------
time39_test.c

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/rtc.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "dlms.h"
#include "error40.h"
#include "time39.h"
#include "io39.h"
#include "time39.h"
#include "time39_test.h"
#include "fragment_open_time_40.h"



#ifdef  MONITOR_40

static double2 Fault(uchar  bError)
{
  return GetDouble2Error1(Error40(bError));
}



double2 TestTimeCorrect39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  caller40 c = InitCaller40();

  time2 tmThat1 = FragmentOpenTime40(&c);
  if (!tmThat1.fValid) return Fault(1);


  time tmThis1 = *GetCurrTimeDate();
  slong wDeltaSeconds1 = GetSecondIndex(tmThis1) - GetSecondIndex(tmThat1.tiValue);
  MonitorString("\n before correction ");
  MonitorString("\n this:  "); MonitorTime(tmThis1);
  MonitorString("\n that:  "); MonitorTime(tmThat1.tiValue);
  MonitorString("\n delta: "); MonitorSignedLongDec(wDeltaSeconds1);


  c.bNS++;
  c.bInvokeId++;
  QueryCorrectTime39(c, wDeltaSeconds1);
  if (Input39() != SER_GOODCHECK) return Fault(2);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(3);

  c.bNR++;
  RR(c.bNR);
  if (Input39() != SER_GOODCHECK) return Fault(4);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(5);


  c.bNS++;
  c.bInvokeId++;
  QueryTime39(c);
  if (Input39() != SER_GOODCHECK) return Fault(6);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(7);
  time tmThat2 = ReadTime39();

  c.bNR++;
  RR(c.bNR);
  if (Input39() != SER_GOODCHECK) return Fault(8);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return Fault(9);


  time tmThis2 = *GetCurrTimeDate();
  slong wDeltaSeconds2 = GetSecondIndex(tmThis2) - GetSecondIndex(tmThat2);
  MonitorString("\n after correction ");
  MonitorString("\n this:  "); MonitorTime(tmThis2);
  MonitorString("\n that:  "); MonitorTime(tmThat2);
  MonitorString("\n delta: "); MonitorSignedLongDec(wDeltaSeconds2);


  return GetDouble0(0);
}

#endif



/*
7e a0 1f 00 02 12 9d 03 54 cc f6 e6 e6 00 c3 01 c2 00 08 00 00 01 00 00 ff 06 01 10 fc 7c 02 6a 7e
7e a0 14 03 00 02 12 9d 74 7e bd e6 e7 00 c7 01 c2 00 00 98 5b 7e

7e a0 1f 00 02 12 9d 03 54 cc f6 e6 e6 00 c3 01 c2 00 08 00 00 01 00 00 ff 06 01 10 03 e8 6f 47 7e
7e a0 14 03 00 02 12 9d 74 7e bd e6 e7 00 c7 01 c2 00 00 98 5b 7e
*/

