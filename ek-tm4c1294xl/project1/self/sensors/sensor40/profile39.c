/*------------------------------------------------------------------------------
profile39*c

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/calendar.h"
#include "../../time/timedate.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/limits.h"
#include "../../special/special.h"
#include "io40.h"
#include "buffer_record_40.h"
#include "dlms_read_register.h"
#include "buffer_profile_40.h"
#include "profile39.h"
#include "fragment_open_time_40.h"
#include "fragment_profile_40.h"



static time             tiValue;
static ulong            dwValue;

static uint             wProfile;
static time             tiStart;

static double           dbScaler;



void    SetTime_Profile40(time  tm)
{
  tiValue = tm;
  dwValue = DateToHouIndex(tiValue);
}


time    GetTime_Profile40(void)
{
  return tiValue;
}


void    SetScaler_Profile40(double  db)
{
  dbScaler = db;
}



void    InitHeader40(void)
{
#ifdef MONITOR_40
  MonitorString("\n InitHeader40 ");
  MonitorString(" tiValue="); MonitorTime(tiValue);
#endif

  if (!UseBounds())
    wProfile = 0;
  else
  {
    wProfile = (mpcwStartRelCan[ibDig] / 6) * 6;
    Clear(); sprintf(szLo+1, "начало %04u:%02u", wProfile, (uchar)(wProfile/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiStart = tiValue;

  uchar i = tiStart.bHour*2 + tiStart.bMinute/30;
  i = (i / 6) * 6;

  tiStart.bHour = i / 2;
  tiStart.bMinute = (i % 2)*30;

#ifdef MONITOR_40
  MonitorString(" wProfile="); MonitorIntDec(wProfile);
  MonitorString(" tiStart="); MonitorTime(tiStart);
#endif
}



t2time  QueryHeader40(void)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiStart);
  dw -= wProfile;
  time tm1 = HouIndexToDate(dw + 1);
  time tm2 = HouIndexToDate(dw + 6);

#ifdef MONITOR_40
  MonitorString("\n QueryHeader40 (end time)");
  MonitorString(" from="); MonitorTime(tm1);
  MonitorString(" to="); MonitorTime(tm2);
#endif

  return GetTuple2Time(tm1,tm2);
}


static bool ReadData40(time  tiTime, ulong  mdwValue[4])
{
#ifdef MONITOR_40
    MonitorString("\n ReadData40 (begin time)");
#endif

  sprintf(szLo," %02u    %02u.%02u.%02u", tiTime.bHour, tiTime.bDay,tiTime.bMonth,tiTime.bYear);

  if (SearchDefHouIndex(tiTime) == 0) return(1);

  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
#if true
    double db = (double)mdwValue[i]*dbScaler;
    mpdbEngFracDigCan[ibDig][i] += db;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse/1000);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w*1000/dbPulse;
#else
    uint w = (uint)(mdwValue[i]*dbScaler*dbPulse/1000);
    mpwChannels[i] = w;
#endif
  }

#ifdef MONITOR_40
    MonitorString(" "); MonitorTime(tiTime);
    MonitorString(" "); MonitorIntDec(mpwChannels[0]);
    MonitorString(" "); MonitorIntDec(mpwChannels[1]);
    MonitorString(" "); MonitorIntDec(mpwChannels[2]);
    MonitorString(" "); MonitorIntDec(mpwChannels[3]);
#endif

  if (IsDefect(ibDig)) MakeSpecial(tiTime);
  return MakeStopHou(0);
}


bool    ReadProfiles40(void)
{
  uchar bSize = GetProfileSize40();

  uchar i;
  for (i=0; i<bSize; i++)
  {
    profile40 prf = GetProfile40(bSize - i - 1);
    if (prf.fExists)
    {
      time tm = HouIndexToDate(DateToHouIndex(prf.tmHhrEnd) - 1);
      if (ReadData40(tm, prf.mdwValue) == false) return false;
    }
  }

  wProfile += 6;
  if (wProfile > wHOURS) return false;

  return true;
}



#ifdef  MONITOR_40

uchar   TestProfile40_Internal(caller40*  pc)
{  
  time2 tm2 = FragmentOpenTime40(pc);
  if (!tm2.fValid) return 1;
  tiValue = tm2.tiValue;

  dwValue = DateToHouIndex(tiValue);


  double2 scaler = ReadRegisterScaler39(obisScalerForProfile1, pc);
  if (!scaler.fValid) return 2;

  SetScaler_Profile40(scaler.dbValue);


  InitHeader40(); // step 40.1


  while (true) {
    t2time t2 = QueryHeader40(); // step 40.3

    if (!FragmentProfile40(pc, t2.ti1, t2.ti2))
      return 3;

    if (!FinishRecord40_AddProfile40()) // step 40.25
      return 4;

    if (ReadProfiles40() == false) return 0; // step 40.26
    if (fKey == true) return 255;
  } // repeat: step 40.27
} // finish: step 40.28



double2 TestProfile40(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  caller40 c = InitCaller40();

  uchar bError = TestProfile40_Internal(&c);
  if (bError != 0)  {
    return GetDouble2Error();
  } else {
    return GetDouble0(0);
  }
}

#endif 
