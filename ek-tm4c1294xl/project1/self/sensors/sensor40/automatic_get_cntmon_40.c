/*------------------------------------------------------------------------------
automatic_get_cntmon_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "dlms.h"
#include "error40.h"
#include "time39.h"
#include "io39.h"
#include "hdlc_address.h"
#include "query_billing_period_39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "read_engmon_39.h"
#include "dlms_read_register.h"
#include "buffer_record_39.h"
#include "fragment_open_time_39.h"
#include "fragment_cntmon_39.h"
#include "fragment_profile_39.h"
#include "automatic_get_cntmon_40.h"



static double2 Fault(uchar  bError)
{
  return GetDouble2Error1(Error40(bError));
}



double2 ReadCntMonCan38_Internal(uchar  ibMon)
{
  caller39 c = InitCaller39();

  time2 tm2 = FragmentOpenTime39(&c);
  if (!tm2.fValid) return Fault(70+0);
  time tm = tm2.tiValue;


  if (tm.bMonth != ibMon+1)
  {
    date dt;
    dt.bDay   = 1;
    dt.bMonth = (ibMon+1) % 12 + 1;
    dt.bYear  = (dt.bMonth > tm.bMonth) ? tm.bYear-1 : tm.bYear;

    double8 db8 = FragmentCntMonCan(obisBillingPeriodMon, obisScalerForBillingPeriod, &c, dt);

    if (db8.bError == ERROR_NOT_PRESENTED) {
      Clear();
      sprintf(szLo+1, "мес€ц %02u.%02u ?", dt.bMonth, dt.bYear);
      Delay(1000);
      return Fault(70+1);
    }

    DISC();
    if (Input39() != SER_GOODCHECK) return Fault(70+2);

    mpdbChannelsC[0] = db8.mdbValue[0];
    mpdbChannelsC[1] = db8.mdbValue[5];
    mpdbChannelsC[2] = db8.mdbValue[6];
    mpdbChannelsC[3] = db8.mdbValue[7];

    uchar i;
    for (i=0; i<4; i++)
    {
      mpdbChannelsC[i] = mpdbChannelsC[i] * mpdbTransCnt[ibDig];
      mpboChannelsA[i] = true;
    }

    return GetDouble0(-1);
  }
  else
  {
    date dt;
    dt.bDay   = tm.bDay;
    dt.bMonth = tm.bMonth;
    dt.bYear  = tm.bYear;

    double8 db8 = FragmentCntMonCan(obisBillingPeriodDay, obisScalerForBillingPeriod, &c, dt);

    if (db8.bError == ERROR_NOT_PRESENTED) {
      Clear();
      sprintf(szLo+0, "сутки %02u.%02u.%02u ?", dt.bDay, dt.bMonth, dt.bYear);
      Delay(1000);
      return Fault(70+3);
    }

    DISC();
    if (Input39() != SER_GOODCHECK) return Fault(70+4);

    mpdbChannelsC[0] = db8.mdbValue[0];
    mpdbChannelsC[1] = db8.mdbValue[5];
    mpdbChannelsC[2] = db8.mdbValue[6];
    mpdbChannelsC[3] = db8.mdbValue[7];

    uchar i;
    for (i=0; i<4; i++)
    {
      mpdbChannelsC[i] = mpdbChannelsC[i] * mpdbTransCnt[ibDig];
      mpboChannelsA[i] = true;
    }

    return GetDouble0(-1);
  }
}



double2 ReadCntMonCan40(uchar  ibMon)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    double2 db2 = ReadCntMonCan38_Internal(ibMon);
    if (fKey == true) break;
    if (db2.fValid)
    {
      return GetDouble0(mpdbChannelsC[diCurr.ibLine]);
    }
  }

  DISC();
  if (Input39() != SER_GOODCHECK) return Fault(70+5);

  return Fault(70+6);
}



#ifdef  MONITOR_40

double2 TestReadCntMonCan39(void)
{
  fMonitorLogBasic = true;
  fMonitorLogHex = true;

  MonitorOpen(0);

  double2 db2;

  uchar m;
  for (m=8; m>=6; m--)
  {
    db2 = ReadCntMonCan40(m-1);
    if (db2.bError)
      break;
  }

  MonitorClose();

  return db2;
}

#endif
