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
#include "../../kernel/tuples.h"
#include "device39.h"
#include "time39.h"
#include "io39.h"
#include "buffer_record_39.h"
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



t2time  QueryHeader39(void)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiStart39);
  dw -= wProfile39;
  time ti1 = HouIndexToDate(dw /*- 1*/);
  time ti2 = HouIndexToDate(dw + 6/* - 1*/);

#ifdef MONITOR_39
  MonitorString("\n QueryHeader39 ");
  MonitorString(" from="); MonitorTime(ti1);
  MonitorString(" to="); MonitorTime(ti2);
#endif

  return GetTuple2Time(ti1,ti2);
}


static bool ReadData39(time  tiTime, ulong  dwValue)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiTime.bHour, tiTime.bDay,tiTime.bMonth,tiTime.bYear);

  if (SearchDefHouIndex(tiTime) == 0) return(1);

  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

/*
  double db = dwValue;
  mpdbEngFracDigCan[ibDig][0] += db;

  uint w = (uint)(mpdbEngFracDigCan[ibDig][0]*dbPulse/1000);
  mpwChannels[0] = w;

  mpdbEngFracDigCan[ibDig][0] -= (double)w*1000/dbPulse;
*/

  ulong dw = dwValue;
  uint w = (uint)(dw*dbPulse/1000);
  mpwChannels[0] = w;

#ifdef MONITOR_39
    MonitorString(" out="); MonitorTime(tiTime);
    MonitorString(" "); MonitorIntDec(mpwChannels[0]);
#endif

  if (IsDefect(ibDig)) MakeSpecial(tiTime);
  return MakeStopHou(0);
}


bool    ReadHeader39(void)
{
  DeltaProfile39();

#ifdef MONITOR_39
  MonitorString("\n ReadHeader39 ");
#endif

  uchar h;
  for (h=0; h<6; h++)
  {
    ulong dw = DateToHouIndex(tiStart39);
    dw -= (wProfile39 - (6-1-h));
    time tiVirtual = HouIndexToDate(dw);

    ulong dwValue = 0;
    uchar bSize = GetProfileSize39();

#ifdef MONITOR_39
    MonitorString("\n time="); MonitorTime(tiVirtual);
    MonitorString(" size="); MonitorCharDec(bSize);
#endif

    uchar i;
    for (i=0; i<bSize; i++)
    {
      profile39 prf = GetProfile39(i);
      if (prf.fExists) {
        if (!DifferentDateTime(tiVirtual, prf.tmTime)) {
          dwValue = prf.ddwValue;
          break;
        }
      }
    }  

#ifdef MONITOR_39
    MonitorString(" in="); MonitorTime(tiVirtual);
    MonitorString(" "); MonitorLongDec(dwValue);
#endif

    if (ReadData39(tiVirtual, dwValue) == false) return false;
  }

  wProfile39 += 6;
  if (wProfile39 > wHOURS) return false;

  return true;
}



#ifdef  MONITOR_39

uchar   TestProfile39_Internal(caller39*  pc)
{  
  if (FragmentOpen39(pc) != 0) return 6;


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryTime39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId);
  if (Input39() != SER_GOODCHECK) return 7;
  if (!ValidateIframe((*pc).bNS, (*pc).bNR)) return 8;
  tiValue39 = ReadTime39();
  dwValue39 = DateToHouIndex(tiValue39);

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return 9;
  if (!ValidateSframe((*pc).bNR)) return 10;


  InitHeader39();
  InitRecord39_FragmentProfile39();


  while (true) {
    t2time t2 = QueryHeader39();
    record39 r = FragmentProfile39(pc, t2.ti1, t2.ti2);
    if (r.bError != 0) return 11;

    if (ReadHeader39() == false) return 0;
    if (fKey == true) return 255;
  }  
}



double2 TestProfile39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller39();

  uchar bError = TestProfile39_Internal(&c);
  if (bError != 0)  {
    return GetDouble2Error();
  } else {
    return GetDouble0(0);
  }
}

#endif 

