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
 #include "../../serial/monitor.h"
 #include "../../devices/devices.h"
 #include "../../devices/devices_time.h"
 #include "../../digitals/limits.h"
 #include "../../special/special.h"
#include "device38.h"
#include "io39.h"
#include "fragment_open_39.h"
#include "fragment_profile_39.h"
#include "buffer_profile_38.h"
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



schar   QueryHeader38(runner39*  runner)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiStart38);
  dw -= wProfile38;
  time ti1 = HouIndexToDate(dw - 1); // для нахождения ПРИРАЩЕНИЯ энергии за получас
  time ti2 = HouIndexToDate(dw + 6 - 1);

#ifdef MONITOR_39
  MonitorString("\n QueryHeader38 ");
  MonitorString(" ti1="); MonitorTime(ti1);
  MonitorString(" ti2="); MonitorTime(ti2);
#endif

  return FragmentProfile39(runner, ti1, ti2);
}


static bool ReadData38(time  tiTime, uint64_t  ddwValue)
{
  tiDig = tiTime; // TODO

  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  ulong dw = ddwValue; // TODO
  uint w = (uint)(dw*dbPulse/10000);
  mpwChannels[0] = w;

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return MakeStopHou(0);
}


bool    ReadHeader38(void)
{
  DeltaBuffPrf38();

#ifdef MONITOR_39
  MonitorString("\n ReadHeader38 ");
#endif

  uchar i;
  for (i=0; i<6; i++)
  {
    profile39 prf = GetBuffPrf38(i);

#ifdef MONITOR_39
    MonitorString("\n "); MonitorTime(prf.tiTime);
    MonitorString(" "); MonitorLongDec(prf.ddwValue % 0x100000000);
    MonitorString(" "); MonitorBool(prf.fExists);
#endif

    if (prf.fExists)
    {
      if (ReadData38(prf.tiTime, prf.ddwValue) == false) return false;
    }
  }

  wProfile38 += 6;
  if (wProfile38 > 12/*wHOURS*/) return false;

  return true;
}



#ifdef  MONITOR_39

uchar   RunProfile39_Internal(runner39*  runner)
{  
  FragmentOpen39(runner);


  (*runner).bNS++;
  (*runner).bInvokeId++;
  QueryTime38((*runner).bNS, (*runner).bNR, (*runner).bInvokeId);
  if (Input39() != SER_GOODCHECK) return 7;
  if (!ValidateIframe((*runner).bNS, (*runner).bNR)) return 8;
  tiValue38 = ReadTime38();
  dwValue38 = DateToHouIndex(tiValue38);
  DelayOff();

  (*runner).bNR++;
  Query38_RR((*runner).bNR);
  if (Input39() != SER_GOODCHECK) return 9;
  if (!ValidateSframe((*runner).bNR)) return 10;
  DelayOff();


  InitHeader38();


  while (true) {
    if (QueryHeader38(runner) != 0) return 11;

    if (ReadHeader38() == false) return 0;
    if (fKey == true) return 255;
  }  
}



double2 RunProfile39(void)
{
  MonitorOpen(0);

  runner39 runner = InitRunner();
  uchar b = RunProfile39_Internal(&runner);
  if (b !== 0) {
    MonitorString("\n error "); MonitorCharDec(b);
  } else {
    MonitorString("\n finish ");
  }

  return GetDouble2(0, false);
}

#endif 

