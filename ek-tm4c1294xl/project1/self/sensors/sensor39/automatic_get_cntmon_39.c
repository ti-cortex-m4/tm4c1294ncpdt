/*------------------------------------------------------------------------------
automatic_get_cntmon_38*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
// #include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "error39.h"
#include "time39.h"
#include "query_engmon_39.h"
#include "read_engmon_39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "buffer_record_39.h"
#include "io39.h"
#include "fragment_open_time_39.h"
#include "fragment_cntmon_39.h"
#include "fragment_profile_39.h"
#include "hdlc_address.h"
#include "automatic_get_cntmon_39.h"



double2 ReadCntMonCan38_Internal(uchar  ibMon)
{
  caller39 c = InitCaller39();

  time2 tm2 = FragmentOpenTime39(&c);
  if (!tm2.fValid) return GetDouble2Error1(Error39(110+0));
  time tm = tm2.tiValue;


  if (tm.bMonth != ibMon+1)
  {
    uchar bMonth = (ibMon+1) % 12 + 1;
    uchar bYear = (bMonth > tm.bMonth) ? tm.bYear-1 : tm.bYear;

    double2 db2 = FragmentCntMonCan(obisEngAbs, &c, bMonth, bYear);
    uchar bError = db2.bError;
    if (bError == ERROR_NOT_PRESENTED) { // TODO no month
/*
        Clear();
        sprintf(szLo+1, "мес€ц %02u.%02u ?",ti.bMonth,ti.bYear);
        Delay(1000);
        return GetDouble2Error();
*/
    }

    Query39_DISC();
    if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(110+0));

    return db2;
  }
  else
  {
    time ti1;
    ti1.bYear = tm.bYear;
    ti1.bMonth = tm.bMonth;
    ti1.bDay = tm.bDay;
    ti1.bHour = 0;
    ti1.bMinute = 0;
    ti1.bSecond = 0;

    time ti2;
    ti2.bYear = tm.bYear;
    ti2.bMonth = tm.bMonth;
    ti2.bDay = tm.bDay;
    ti2.bHour = 23;
    ti2.bMinute = 59;
    ti2.bSecond = 59;

    InitBuffRecord39_FragmentProfile39(); // TODO inside FragmentProfile39 by flag
    record39 r = FragmentProfile39(&c, ti1, ti2);
    if (r.bError != 0)
    {
#ifdef MONITOR_39
      MonitorString("\n error="); MonitorCharDec(r.bError);
#endif
      return GetDouble2Error1(Error39(110+0));
    }
    if (r.fFirst == false) // TODO no day
    {
/*
        Clear();
        sprintf(szLo+0, "сутки %02u.%02u.%02u ?",ti.bDay,ti.bMonth,ti.bYear);
        Delay(1000);
        return GetDouble2Error();
*/
#ifdef MONITOR_39
      MonitorString("\n no data");
#endif
      return GetDouble2Error1(Error39(110+0));
    }

    Query39_DISC();
    if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(110+0));

    return GetDouble0(r.ddwValue);
  }
}



double2 ReadCntMonCan39(uchar  ibMon)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    double2 db2 = ReadCntMonCan38_Internal(ibMon);
    if (fKey == true) break;
    if (db2.fValid)
    {
      mpdbChannelsC[0] = db2.dbValue / 1000;
      mpboChannelsA[0] = true;

      return GetDouble2(mpdbChannelsC[0], true);
    }
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(Error39(110+3));

  return GetDouble2Error1(Error39(110+3));
}
