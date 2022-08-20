/*------------------------------------------------------------------------------
profile39*c

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_energy_spec.h"
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
#include "io39.h"
#include "buffer_record_39.h"
#include "dlms_read_register.h"
#include "fragment_open_time_39.h"
#include "fragment_profile_39.h"
#include "buffer_profile_39.h"
#include "profile39.h"



uint                    wProfile40;
time                    tiStart40;

double                  dbScaler;

time                    tiValue40;
ulong                   dwValue40;



void    SetTime_Profile40(time  tm)
{
  tiValue40 = tm;
  dwValue40 = DateToHouIndex(tiValue40);
}


time    GetTime_Profile40(void)
{
  return tiValue40;
}


void    SetScaler_Profile40(double  db)
{
  dbScaler = db;
}



void    InitHeader40(void)
{
/* TODO
  if (!UseBound40())
    wProfile40 = 0;
  else
  {
    wProfile40 = (mpcwStartRelCan[ibDig] / 6) * 6;
    Clear(); sprintf(szLo+1,"начало %04u:%02u",wProfile40,(uchar)(wProfile40/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }
*/
  wProfile40 = 0;
  tiStart40 = tiValue40;

  uchar i = tiStart40.bHour*2 + tiStart40.bMinute/30;
  i = (i / 6) * 6;

  tiStart40.bHour = i / 2;
  tiStart40.bMinute = (i % 2)*30;

#ifdef MONITOR_40
  MonitorString("\n InitHeader40 ");
  MonitorString(" wProfile40="); MonitorIntDec(wProfile40);
  MonitorString(" tiStart40="); MonitorTime(tiStart40);
#endif
}



t2time  QueryHeader40(void)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiStart40);
  dw -= wProfile40;
  time ti1 = HouIndexToDate(dw /*- 1*/);
  time ti2 = HouIndexToDate(dw + 6-1/* - 1*/); // TODO

#ifdef MONITOR_40
  MonitorString("\n QueryHeader40 ");
  MonitorString(" from="); MonitorTime(ti1);
  MonitorString(" to="); MonitorTime(ti2);
#endif

  return GetTuple2Time(ti1,ti2);
}


static bool ReadData40(time  tiTime, ulong  mdwValue[4])
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiTime.bHour, tiTime.bDay,tiTime.bMonth,tiTime.bYear);

  if (SearchDefHouIndex(tiTime) == 0) return(1);

  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar c;
  for (c=0; c<4; c++)
  {
#if true
    double db = (double)mdwValue[c]*dbScaler;
    mpdbEngFracDigCan[ibDig][c] += db;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][c]*dbPulse/1000);
    mpwChannels[c] = w;

    mpdbEngFracDigCan[ibDig][c] -= (double)w*1000/dbPulse;
#else
    uint w = (uint)(mdwValue[c]*dbScaler*dbPulse/1000);
    mpwChannels[c] = w;
#endif
  }

#ifdef MONITOR_40
    MonitorString("\n profile "); MonitorTime(tiTime);
    MonitorString(" "); MonitorIntDec(mpwChannels[0]);
    MonitorString(" "); MonitorIntDec(mpwChannels[1]);
    MonitorString(" "); MonitorIntDec(mpwChannels[2]);
    MonitorString(" "); MonitorIntDec(mpwChannels[3]);
#endif

  if (IsDefect(ibDig)) MakeSpecial(tiTime);
  return MakeStopHou(0);
}


bool    ReadHeader40(void)
{
  uchar bSize = GetProfileSize39();

  uchar i;
  for (i=0; i<bSize; i++)
  {
    profile39 prf = GetProfile39(bSize - i - 1);
    if (prf.fExists)
    {
      time tm = HouIndexToDate(DateToHouIndex(prf.tmTime) - 1);
      if (ReadData40(tm, prf.mdwValue) == false) return false;
    }
  }

  wProfile40 += 6;
  if (wProfile40 > wHOURS) return false;

  return true;
}



#ifdef  MONITOR_39

uchar   TestProfile40_Internal(caller39*  pc)
{  
  time2 tm2 = FragmentOpenTime39(pc);
  if (!tm2.fValid) return 1;
  tiValue40 = tm2.tiValue;

  dwValue40 = DateToHouIndex(tiValue40);


  double2 scaler = ReadRegisterScaler39(obisScalerForProfile1, pc);
  if (!scaler.fValid) return 2;

  SetScaler_Profile40(scaler.dbValue);


  InitHeader40(); // step 40.1


  while (true) {
    t2time t2 = QueryHeader40(); // step 40.3
    bool success = FragmentProfile39(pc, t2.ti1, t2.ti2, true);
    if (!success) return 11;

    if (ReadHeader40() == false) return 0; // step 40.26
    if (fKey == true) return 255;
  } // repeat: step 40.27
} // finish: step 40.28



double2 TestProfile40(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller39();

  uchar bError = TestProfile40_Internal(&c);
  if (bError != 0)  {
    return GetDouble2Error();
  } else {
    return GetDouble0(0);
  }
}

#endif 
