/*------------------------------------------------------------------------------
profile39*c

------------------------------------------------------------------------------*/

#include "../../main.h"
// #include "../../serial/ports_stack.h"
// #include "../../serial/ports_devices.h"
// #include "../../memory/mem_settings.h"
// #include "../../memory/mem_digitals.h"
// #include "../../memory/mem_ports.h"
// #include "../../memory/mem_current.h"
// #include "../../memory/mem_factors.h"
// #include "../../memory/mem_realtime.h"
// #include "../../memory/mem_energy_spec.h"
// #include "../../memory/mem_profile.h"
// #include "../../memory/mem_limits.h"
// #include "../../display/display.h"
 #include "../../keyboard/keyboard.h"
 #include "../../keyboard/time/key_timedate.h"
// #include "../../time/timedate.h"
 #include "../../time/calendar.h"
// #include "../../time/delay.h"
// #include "../../serial/ports.h"
// #include "../../serial/ports_devices.h"
 #include "../../serial/monitor.h"
// #include "../../devices/devices.h"
// #include "../../devices/devices_time.h"
// #include "../../digitals/current/current_run.h"
// #include "../../digitals/limits.h"
// #include "../../special/special.h"
// #include "../../hardware/watchdog.h"
// #include "automatic_s.h"
#include "device38.h"
#include "io38.h"
#include "monitor38.h"
#include "fragment_open_38.h"
#include "fragment_profile_38.h"
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
}



schar   QueryHeader38(runner38  runner)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiStart38);
  dw -= wProfile38;
  time ti1 = HouIndexToDate(dw);
  time ti2 = HouIndexToDate(dw + 6 - 1);


  return FragmentProfile38(runner, ti1, ti2);
}


static bool ReadData38(time  tiTime, uint64_t  ddwValue)
{
  tiDig = tiTime; // TODO

  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  ulong dw = mpPrf38[h].mpdwValue[i];
  uint w = (uint)(dw*dbPulse/10000);
  mpwChannels[i] = w;

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return MakeStopHou(0);
}


bool    ReadHeader38(void)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    profile38 prf = GetPrf38(i);
    if (prf.fPresents)
    {
      if (ReadData38(prf.tiTime, prf.ddwValue) == false) return false;
    }
  }

  wProfile38 += 6;
  if (wProfile38 > wHOURS) return false;

  return true;
}



#ifdef  MONITOR_38

uchar   RunProfile39_Internal(runner38  runner)
{  
  FragmentOpen38(runner);


  runner.bNS++;
  runner.bInvokeId++;
  QueryTime38(runner.bNS, runner.bNR, runner.bInvokeId);
  if (Input38() != SER_GOODCHECK) return 7;
  if (!ValidateIframe(runner.bNS, runner.bNR)) return 8;
  tiValue38 = ReadTime38();
  dwValue38 = DateToHouIndex(tiValue38);
  DelayOff();

  runner.bNR++;
  Query38_RR(runner.bNR);
  if (Input38() != SER_GOODCHECK) return 9;
  if (!ValidateSframe(runner.bNR)) return 10;
  DelayOff();


  InitHeader38();


  while (true) {
    if (QueryHeader38(runner) != 0) return 11;

    if (ReadHeader38() == false) return 0;
    if (fKey == true) return 255;
  }  
}



void    RunProfile39(runner38  runner)
{
  uchar b = RunProfile39_Internal(runner);
  if (b == 0){
    MonitorString("\n error ");
  } else {
    MonitorString("\n finish "); MonitorCharDec(b);
  }
}

#endif 

