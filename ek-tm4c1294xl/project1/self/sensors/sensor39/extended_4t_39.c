/*------------------------------------------------------------------------------
extended_4t_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "time39.h"
#include "query_engmon_39.h"
#include "query_params_39.h"
#include "fragment_open_39.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "extended_4t_39.h"



static const obis_t obisEngTariff[4] = {
  {1, 0, 15, 8, 1, 255},
  {1, 0, 15, 8, 2, 255},
  {1, 0, 15, 8, 3, 255},
  {1, 0, 15, 8, 4, 255},
};



const obis_t *GetOBIS(uchar  ibTariff)
{
  ASSERT(sizeof(obisEngTariff)/sizeof(obisEngTariff[0]) == 4);
  ASSERT(ibTariff < 4);
  return &obisEngTariff[ibTariff];
}



status  CntMonCanTariff39_Internal(uchar  ibMon, uchar  ibTariff)
{
  caller39 r = InitCaller();
  if (FragmentOpen39(&r) != 0) return ST_BADDIGITAL;


  r.bNS++;
  r.bInvokeId++;
  QueryTime39(r.bNS, r.bNR, r.bInvokeId);
  if (Input39() != SER_GOODCHECK) return ST_BADDIGITAL;
  if (!ValidateIframe(r.bNS, r.bNR)) return ST_BADDIGITAL;
  time ti = ReadTime39();
  //DelayOff();

  r.bNR++;
  Query39_RR(r.bNR);
  if (Input39() != SER_GOODCHECK) return ST_BADDIGITAL;
  if (!ValidateSframe(r.bNR)) return ST_BADDIGITAL;
  //DelayOff();


  uchar bMonth = ibMon + 1;
  uchar bYear = (bMonth > ti.bMonth) ? ti.bYear-1 : ti.bYear;

  r.bNS++;
  QueryEngMon39(*GetOBIS(ibTariff), r.bNS, r.bNR, r.bInvokeId++, bMonth, bYear);
  if (Input39() != SER_GOODCHECK) return ST_BADDIGITAL;
  if (!ValidateIframe(r.bNS, r.bNR)) return ST_BADDIGITAL;

  bool present = (IsEngMonPresent39() == 0);
  bool absent = (IsEngMonAbsent39() == 0);

  ulong64_ ddw2 = GetULong64Error1(0);
  if (present) {
    InitPop(17 + GetHdlcAddressesSize());
    ddw2 = PopUnsignedValueDLSM();
  }

#ifdef MONITOR_39
  MonitorString("\n present="); MonitorBool(present);
  MonitorString("\n absent="); MonitorBool(absent);
  MonitorString("\n valid="); MonitorBool(ddw2.fValid);
  MonitorString("\n value="); MonitorLongDec(ddw2.ddwValue);
#endif
  //DelayOff();

  r.bNR++;
  Query39_RR(r.bNR);
  if (Input39() != SER_GOODCHECK) return ST_BADDIGITAL;
  if (!ValidateSframe(r.bNR)) return ST_BADDIGITAL;
  //DelayOff();


  double2 scaler = ReadRegisterScaler39(*GetOBIS(ibTariff), &r);
  if (!scaler.fValid) return ST_BADDIGITAL;
  double dbScaler = scaler.dbValue;
//  MonitorString("\n scaler="); MonitorDouble6(dbScaler);


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return ST_BADDIGITAL;
  //DelayOff();

  if (present) {
    mpdbChannelsC[0] = (dbScaler * ddw2.ddwValue / 1000) * mpdbTransCnt[ibDig];
    mpboChannelsA[0] = true;
#ifdef MONITOR_39
    MonitorString("\n result="); MonitorDouble6(mpdbChannelsC[0]);
#endif
    return ST_OK;
  }

  if (absent) {
    return ST_NOTPRESENTED;
  }

  return ST_BADDIGITAL;
}



status  ReadCntMonCanTariff39(uchar  ibMonAbs, uchar  ibTariff) // на начало мес€ца
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    status s = CntMonCanTariff39_Internal(ibMonAbs, ibTariff);
    if (fKey == true) break;

    if (s == ST_OK) return s;
    if (s == ST_NOTPRESENTED) return s;
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return ST_BADDIGITAL;
  //DelayOff();

  return ST_BADDIGITAL;
}



#ifdef  MONITOR_39

double2 TestCntMonCanTariff39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  uchar bMonth = (*GetCurrTimeDate()).bMonth;

  uchar m;
  for (m=0; m<10; m++) {
    uchar ibMonthAbs = (12 + bMonth - 1 - m) % 12;
    
    uchar t;
    for (t=0; t<4; t++) {
      MonitorString("\n\n month="); MonitorCharDec(ibMonthAbs);
      MonitorString(" tariff="); MonitorCharDec(t);
      status s = ReadCntMonCanTariff39(ibMonthAbs, t);
      MonitorString("\n status="); MonitorCharDec(s);
    }
  }

  return GetDouble2(0, true);
}

#endif
