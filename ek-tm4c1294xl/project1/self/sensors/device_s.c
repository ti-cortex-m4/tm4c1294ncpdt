/*------------------------------------------------------------------------------
DEVICE_S.C

 Энергомера СЕ102
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../display/display.h"
#include "../keyboard/time/key_timedate.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../serial/ports_common.h"
#include "../devices/devices.h"
#include "../devices/devices_time.h"
#include "../digitals/current/current_run.h"
#include "../digitals/limits.h"
#include "../special/special.h"
#include "../hardware/watchdog.h"
#include "automatic_s.h"
#include "device_s.h"
//#include        "xdata.h"
//#include        "ports.h"
//#include        "display.h"
//#include        "delay.h"
//#include        "lines.h"
//#include        "engine.h"
//#include        "limits.h"
//#include        "timedate.h"
//#include        "essential.h"
//#include        "digitals.h"
//#include        "automatic_s.h"
//#include        "_timedate.h"



#ifndef SKIP_S

void    PushAddressS(void)
{
uint	i;

  i = mpdwAddress1[diCurr.bAddress-1] % 0x10000;
  PushChar(i % 0x100);
  PushChar(i / 0x100);

  i = wPrivate;
  PushChar(i % 0x100);
  PushChar(i / 0x100);

  i = mpdwAddress2[diCurr.bAddress-1] % 0x10000;
  PushChar(i % 0x100);
  PushChar(i / 0x100);
  i = mpdwAddress2[diCurr.bAddress-1] / 0x10000;
  PushChar(i % 0x100);
  PushChar(i / 0x100);
}



void    QueryTimeS(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x20);

  QueryS_IO(100+18, 15);
}


void    ReadTimeAltS(void)
{
  InitPop(9);

  tiAlt.bSecond = FromBCD(PopChar());
  tiAlt.bMinute = FromBCD(PopChar());
  tiAlt.bHour   = FromBCD(PopChar());

  PopChar();

  tiAlt.bDay    = FromBCD(PopChar());
  tiAlt.bMonth  = FromBCD(PopChar());
  tiAlt.bYear   = FromBCD(PopChar());
}



void    QueryControlS(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD7);
  PushChar(0x01);
  PushChar(0x21);

  PushChar(ToBCD(tiCurr.bSecond));
  PushChar(ToBCD(tiCurr.bMinute));
  PushChar(ToBCD(tiCurr.bHour));

  tiAlt = tiCurr;
  PushChar((Weekday() + 1) % 7);

  PushChar(ToBCD(tiCurr.bDay));
  PushChar(ToBCD(tiCurr.bMonth));
  PushChar(ToBCD(tiCurr.bYear));

  QueryS_IO(100+11, 22);
}



void    QueryConfigS(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x01);

  QueryS_IO(100+16, 15);
}


void    ReadConfigS(void)
{
  InitPop(9);

  switch (PopChar() & 0x03)
  {
    case 0x00: wDividerS = 1; break;
    case 0x01: wDividerS = 10; break;
    case 0x02: wDividerS = 100; break;
    default:   wDividerS = 1000; break;
  }  
}



void    QueryVersionS(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD0);
  PushChar(0x01);
  PushChar(0x00);

  QueryS_IO(100+17, 15);
}


void    ReadVersionS(void)
{
  InitPop(9);
  
  Clear();
  sprintf(szLo+1, "версия %u.%u.%u", PopChar(), PopChar(), PopChar());
}



void    QueryEngDayS(uchar  bDay)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD1);
  PushChar(0x01);
  PushChar(0x2F);
  PushChar(bDay);

  QueryS_IO(100+15, 16);
}


void    QueryEngMonS(uchar  bMonth)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD1);
  PushChar(0x01);
  PushChar(0x31);
  PushChar(bMonth);

  QueryS_IO(100+15, 16);
}


void    ReadEnergyS(void)
{
  InitPop(9);
                   
  coEnergy.mpbBuff[3] = PopChar();
  coEnergy.mpbBuff[2] = PopChar();
  coEnergy.mpbBuff[1] = PopChar();
  coEnergy.mpbBuff[0] = PopChar();

  mpdwChannelsA[0] = coEnergy.dwBuff;
  mpboChannelsA[0] = true;
}



void    InitHeaderS(void)
{
uchar i;

  if (!UseBounds())
    wBaseCurr = 0;
  else 
  {
    wBaseCurr = (mpcwStartRelCan[ibDig] / 6) * 6;
    sprintf(szLo," начало %04u:%02bu ",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;

  i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 4) * 4;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
}


void    QueryHeaderS(void)
{
  NoShowTime(1);


  tiAlt = tiDigPrev;
  dwBuffC = DateToHouIndex();

  dwBuffC -= wBaseCurr;

  HouIndexToDate(dwBuffC);
  tiDig = tiAlt;


  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD5);
  PushChar(0x01);
  PushChar(0x34);

  PushChar(ToBCD(tiDig.bDay));
  PushChar(ToBCD(tiDig.bMonth));
  PushChar(ToBCD(tiDig.bYear));
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);
  PushChar(4);

  QueryS_IO(100+23, 20);
}


bool    ReadDataS(uchar  i)
{
  sprintf(szLo," %02bu:%02bu %02bu.%02bu.%02bu",
          tiDig.bHour,tiDig.bMinute, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  tiAlt = tiDig;
  if (SearchDefHouIndex() == 0) return(1); 


  ShowProgressDigHou();      

  InitPop(9+i*3);                                    

  dwBuffC  = PopChar();
  dwBuffC += PopChar()*0x100;
  dwBuffC += PopChar()*0x10000;

  if (dwBuffC != 0xFFFFFF)
  {
    reBuffB = mpdbPulseHou[ibDig];
    reBuffA = (float)dwBuffC/wDividerS;
    mpreEngFrac[ibDig] += reBuffA;

    if ((ulong)(mpreEngFrac[ibDig]*reBuffB) < 0xFFFF)
    { wBuffD = (uint)(mpreEngFrac[ibDig]*reBuffB); }
    else
    { wBuffD = 0xFFFF; mpcwOverflowHou[ibDig]++; }

    mpwChannels[0] = wBuffD;
    mpreEngFrac[ibDig] -= (float)wBuffD/reBuffB;

    tiAlt = tiDig;
    MakePrevHou();  
    return(MakeStopHou(0));  
  }
  else
  {
    szLo[15] = '*';
    return(MakeStopHou(0));
  }
}


bool    ReadHeaderS(void)
{
uchar i;

  for (i=0; i<4; i++)
  {
    tiAlt = tiDigPrev;
    dwBuffC = DateToHouIndex();

    dwBuffC += 4-1;
    dwBuffC -= (wBaseCurr + i);

    HouIndexToDate(dwBuffC);
    tiDig = tiAlt;

    if (dwBuffC < dwValueC)     
      if (ReadDataS(4-1-i) == 0) return(0);
  }
  
  wBaseCurr += 4;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}



void    ReadCurrentS(void)
{
  ReadEnergyS();
  mpdwBaseDig[0] = coEnergy.dwBuff*mpdbPulseMnt[ibDig]/wDividerS;

  MakeCurrent();
}

#endif

// device_24: чтение данных по сезонному времени
// поиск счетчиков
// признаки переполнения получасов - проверить изменение коэффициентов
// разрыв получасового опроса
