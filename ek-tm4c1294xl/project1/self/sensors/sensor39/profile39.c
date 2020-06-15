/*------------------------------------------------------------------------------
profile39*c

------------------------------------------------------------------------------*/

#include "../../main.h"
 #include "../../memory/mem_factors.h"
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
#include "device39.h"
#include "time39.h"
#include "io39.h"
#include "fragment_open_39.h"
#include "fragment_profile_39.h"
#include "buffer_profile_39.h"
#include "profile39.h"



uint                    wProfile39;
time                    tiStart39;

time                    tiValue39;
ulong                   dwValue39;



void    InitHeader39(void)
{
/*
  if (!UseBound39())
    wProfile39 = 0;
  else
  {
    wProfile39 = (mpcwStartRelCan[ibDig] / 6) * 6;
    Clear(); sprintf(szLo+1,"начало %04u:%02u",wProfile39,(uchar)(wProfile39/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }
*/
  wProfile39 = 0;
  tiStart39 = tiValue39;

  uchar i = tiStart39.bHour*2 + tiStart39.bMinute/30;
  i = (i / 6) * 6;

  tiStart39.bHour = i / 2;
  tiStart39.bMinute = (i % 2)*30;

#ifdef MONITOR_39
  MonitorString("\n InitHeader39 ");
  MonitorString(" wProfile39="); MonitorIntDec(wProfile39);
  MonitorString(" tiStart39="); MonitorTime(tiStart39);
#endif
}



uchar   QueryHeader39(runner39*  pr)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiStart39);
  dw -= wProfile39;
  time ti1 = HouIndexToDate(dw - 1);
  time ti2 = HouIndexToDate(dw + 6 - 1);

#ifdef MONITOR_39
  MonitorString("\n QueryHeader39 ");
  MonitorString(" ti1="); MonitorTime(ti1);
  MonitorString(" ti2="); MonitorTime(ti2);
#endif

  return FragmentProfile39(pr, ti1, ti2);
}


static bool ReadData39(time  tiTime, ulong  dwValue)
{
  tiDig = tiTime; // TODO

  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  ulong dw = dwValue; // TODO
  uint w = (uint)(dw*dbPulse/500);
  mpwChannels[0] = w;

#ifdef MONITOR_39
    MonitorString("   result "); MonitorTime(tiDig);
    MonitorString(" "); MonitorIntDec(mpwChannels[0]);
#endif

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return MakeStopHou(0);
}


bool    ReadHeader39(void)
{
  DeltaBuffPrf39();

#ifdef MONITOR_39
//  MonitorString("\n ReadHeader39 ");
#endif

  uchar h;
  for (h=0; h<6; h++)
  {
    ulong dw = DateToHouIndex(tiStart39);
    dw -= (wProfile39 - h);
    time tiVirtual = HouIndexToDate(dw);

#ifdef MONITOR_39
    MonitorString("\n "); MonitorTime(tiVirtual);
#endif

    ulong dwValue = 0;

    uchar bSize = GetBuffPrfSize39();
    uchar i;
    for (i=0; i<bSize; i++)
    {
      profile39 prf = GetBuffPrf39(h);
      if (prf.fExists) {
        bool difference = DifferentDateTime(tiVirtual, prf.tiTime);

#ifdef MONITOR_39
//        MonitorString("\n ");
//        MonitorString("   vrt.="); MonitorTime(tiVirtual);
//        MonitorString(" act.="); MonitorTime(prf.tiTime);
//        MonitorBool(difference);
#endif

        if (!difference) {
          dwValue = prf.ddwValue;
          break;
        }
      }
    }  

#ifdef MONITOR_39
//    MonitorString("   Time="); MonitorTime(tiVirtual);
//    MonitorString(" Value="); MonitorLongDec(dwValue);
#endif

    if (ReadData39(tiVirtual, dwValue) == false) return false;
  }

  wProfile39 += 6;
  if (wProfile39 > 100/*wHOURS*/) return false;

  return true;
}



#ifdef  MONITOR_39

uchar   TestProfile39_Internal(runner39*  pr)
{  
  if (FragmentOpen39(pr) != 0) return 6;


  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryTime39((*pr).bNS, (*pr).bNR, (*pr).bInvokeId);
  if (Input39() != SER_GOODCHECK) return 7;
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return 8;
  tiValue39 = ReadTime39();
  dwValue39 = DateToHouIndex(tiValue39);
  DelayOff();

  (*pr).bNR++;
  Query39_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return 9;
  if (!ValidateSframe((*pr).bNR)) return 10;
  DelayOff();


  InitHeader39();


  while (true) {
    if (QueryHeader39(pr) != 0) return 11;

    if (ReadHeader39() == false) return 0;
    if (fKey == true) return 255;
  }  
}



double2 TestProfile39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  runner39 runner = InitRunner();
  uchar b = TestProfile39_Internal(&runner);
  if (b != 0) {
    MonitorString("\n error "); MonitorCharDec(b);
  } else {
    MonitorString("\n finish ");
  }

  return GetDouble2(0, true);
}

#endif 

