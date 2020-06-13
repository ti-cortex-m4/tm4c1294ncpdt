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



uint                    wProfile38;
time                    tiStart38;

time                    tiValue38;
ulong                   dwValue38;



void    InitHeader38(void)
{
/*
  if (!UseBound39())
    wProfile38 = 0;
  else
  {
    wProfile38 = (mpcwStartRelCan[ibDig] / 6) * 6;
    Clear(); sprintf(szLo+1,"начало %04u:%02u",wProfile38,(uchar)(wProfile38/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }
*/
  wProfile38 = 0;
  tiStart38 = tiValue38;

  uchar i = tiStart38.bHour*2 + tiStart38.bMinute/30;
  i = (i / 6) * 6;

  tiStart38.bHour = i / 2;
  tiStart38.bMinute = (i % 2)*30;

#ifdef MONITOR_39
  MonitorString("\n InitHeader38 ");
  MonitorString(" wProfile38="); MonitorIntDec(wProfile38);
  MonitorString(" tiStart38="); MonitorTime(tiStart38);
#endif
}



uchar   QueryHeader38(runner39*  pr)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiStart38);
  dw -= wProfile38;
  time ti1 = HouIndexToDate(dw - 1);
  time ti2 = HouIndexToDate(dw + 6 - 1);

#ifdef MONITOR_39
  MonitorString("\n QueryHeader38 ");
  MonitorString(" ti1="); MonitorTime(ti1);
  MonitorString(" ti2="); MonitorTime(ti2);
#endif

  uchar b = FragmentProfile39(pr, ti1, ti2);
  MonitorString(" error1="); MonitorCharDec(b);
  return b;
}


static bool ReadData38(time  tiTime, ulong  dwValue)
{
  tiDig = tiTime; // TODO

  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  ulong dw = dwValue; // TODO
  uint w = (uint)(dw*dbPulse);
  mpwChannels[0] = w;

#ifdef MONITOR_39
//    MonitorString("   time="); MonitorTime(tiDig);
//    MonitorString(" value="); MonitorIntDec(mpwChannels[0]);
#endif

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return MakeStopHou(0);
}


bool    ReadHeader38(void)
{
  DeltaBuffPrf38();

#ifdef MONITOR_39
  MonitorString("\n ReadHeader38 ");
#endif

  uchar h;
  for (h=0; h<6; h++)
  {
    ulong dw = DateToHouIndex(tiStart38);
    dw -= (wProfile38 - h);
    time tiVirtual = HouIndexToDate(dw);

#ifdef MONITOR_39
//    MonitorString("\n tiVirtual="); MonitorTime(tiVirtual);
#endif

    ulong dwValue = 0;

    uchar bSize = GetBuffPrfSize38();
    uchar i;
    for (i=0; i<bSize; i++)
    {
      profile39 prf = GetBuffPrf38(h);
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

    if (ReadData38(tiVirtual, dwValue) == false) return false;
  }

  wProfile38 += 6;
  if (wProfile38 > 50/*wHOURS*/) return false;

  return true;
}



#ifdef  MONITOR_39

uchar   RunProfile39_Internal(runner39*  pr)
{  
  FragmentOpen39(pr);


  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryTime39((*pr).bNS, (*pr).bNR, (*pr).bInvokeId);
  if (Input39() != SER_GOODCHECK) return 7;
  if (!ValidateIframe((*pr).bNS, (*pr).bNR)) return 8;
  tiValue38 = ReadTime39();
  dwValue38 = DateToHouIndex(tiValue38);
  DelayOff();

  (*pr).bNR++;
  Query38_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return 9;
  if (!ValidateSframe((*pr).bNR)) return 10;
  DelayOff();


  InitHeader38();


  while (true) {
    if (QueryHeader38(pr) != 0) return 11;

    if (ReadHeader38() == false) return 0;
    if (fKey == true) return 255;
  }  
}



double2 RunProfile39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  runner39 runner = InitRunner();
  uchar b = RunProfile39_Internal(&runner);
  if (b != 0) {
    fMonitorLogBasic = true;
    fMonitorLogHex = true;
    MonitorIn();
    MonitorString("\n error "); MonitorCharDec(b);
  } else {
    MonitorString("\n finish ");
  }

  return GetDouble2(0, true);
}

#endif 

