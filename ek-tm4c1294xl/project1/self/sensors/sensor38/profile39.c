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
// #include "../../keyboard/time/key_timedate.h"
// #include "../../time/timedate.h"
// #include "../../time/calendar.h"
// #include "../../time/delay.h"
// #include "../../serial/ports.h"
// #include "../../serial/ports_devices.h"
// #include "../../serial/monitor.h"
// #include "../../devices/devices.h"
// #include "../../devices/devices_time.h"
// #include "../../digitals/current/current_run.h"
// #include "../../digitals/limits.h"
// #include "../../special/special.h"
// #include "../../hardware/watchdog.h"
// #include "automatic_s.h"
#include "profile39.h"



time                    tiValue38;
ulong                   dwValue38;


/*
void    InitHeader39(void)
{
  if (!UseBound39())
    wBaseCurr = 0;
  else
  {
    wBaseCurr = (mpcwStartRelCan[ibDig] / 6) * 6;
    Clear(); sprintf(szLo+1,"начало %04u:%02u",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;

  uchar i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 4) * 4;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
}


void    QueryHeader39(void)
{
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddress39();

  PushChar(0xD5);
  PushChar(0x01);
  PushChar(0x34);

  PushChar(ToBCD(tiDig.bDay));
  PushChar(ToBCD(tiDig.bMonth));
  PushChar(ToBCD(tiDig.bYear));
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);
  PushChar(4);

  Query39(100+23, 20);
}


static bool ReadData39(uchar  i)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);


  ShowProgressDigHou();

  InitPop(9+i*3);

  ulong dw = PopChar();
  dw += PopChar()*0x100;
  dw += PopChar()*0x10000;

  if (dw != 0xFFFFFF)
  {
    double dbPulse = mpdbPulseHou[ibDig];

    double db = (double)dw/wDividerS;
    mpdbEngFrac[ibDig] += db;

    uint w;
    if ((ulong)(mpdbEngFrac[ibDig]*dbPulse) < 0xFFFF)
    { w = (uint)(mpdbEngFrac[ibDig]*dbPulse); }
    else
    { w = 0xFFFF; mpcwOverflowHhr[ibDig]++; }

    mpwChannels[0] = w;
    mpdbEngFrac[ibDig] -= (double)w/dbPulse;

    MakeSpecial(tiDig);
    return(MakeStopHou(0));
  }
  else
  {
    szLo[15] = '*';
    return(MakeStopHou(0));
  }
}


bool    ReadHeader39(void)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);

    dw += 4-1;
    dw -= (wBaseCurr + i);

    tiDig = HouIndexToDate(dw);

    if (dw < dwValueS)
      if (ReadData39(4-1-i) == 0) return(0);
  }

  wBaseCurr += 4;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}



#ifdef  MONITOR_38

void    RunProfile39(void)
{  
  QueryTime39();
  if (Input39() != SER_GOODCHECK) { MonitorString("\n error 1"); return; }

  tiValue38 = ReadTime39();
  dwValue38 = DateToHouIndex(tiValue38);

  InitHeader39();

  while (true) {
    QueryHeader39();
    if (Input39() != SER_GOODCHECK) { MonitorString("\n error 2"); return; }

    if (ReadData39() == false) { MonitorString("\n finish "); return; }
    if (fKey == true) return;
  }  
}

#endif 
*/