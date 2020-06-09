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
// #include "../../keyboard/time/key_timedate.h"
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



void    QueryHeader38(void)
{
/*
  HideCurrTime(1);


  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wProfile38;
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
*/
}

/*
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
*/

bool    ReadHeader38(void)
{
/*
  uchar i;
  for (i=0; i<4; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);

    dw += 4-1;
    dw -= (wProfile38 + i);

    tiDig = HouIndexToDate(dw);

    if (dw < dwValueS)
      if (ReadData39(4-1-i) == 0) return(0);
  }

  wProfile38 += 4;
  if (wProfile38 > wHOURS) return(0);
*/
  return true;
}



#ifdef  MONITOR_38

uchar   RunProfile39_Internal(void)
{  
  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return 1;
  DelayOff();

  Query38_SNRM();
  if (Input38() != SER_GOODCHECK) return 2;
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query38_Open2(bNS, bNR);
  if (Input38() != SER_GOODCHECK) return 3;
  if (!ValidateIframe(bNS, bNR)) return 4;
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return 5;
  if (!ValidateSframe(bNR)) return 6;
  DelayOff();


  bNS++;
  bInvokeId++;
  QueryTime38(bNS, bNR, bInvokeId);
  if (Input38() != SER_GOODCHECK) return 7;
  if (!ValidateIframe(bNS, bNR)) return 8;
  tiValue38 = ReadTime38();
  dwValue38 = DateToHouIndex(tiValue38);
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return 9;
  if (!ValidateSframe(bNR)) return 10;
  DelayOff();


  InitHeader38();


  while (true) {
    QueryHeader38();
    if (Input38() != SER_GOODCHECK) return 11;

    if (ReadHeader38() == false) return 0;
    if (fKey == true) return 255;
  }  
}



void    RunProfile39(void)
{
  uchar b = RunProfile39_Internal();
  if (b == 0){
    MonitorString("\n error ");
  } else {
    MonitorString("\n finish "); MonitorCharDec(b);
  }
}

#endif 

