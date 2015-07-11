/*------------------------------------------------------------------------------
DEVICE_C.C
              
 
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
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
#include "../digitals/current/current2.h"
#include "../digitals/digitals_messages.h"
#include "../digitals/limits.h"
#include "../digitals/profile/refill.h"
#include "../special/special.h"
#include "../flash/records.h"
#include "../energy.h"
#include "device_c.h"



#ifndef SKIP_C

// проверка сетевого адреса для счётчиков CC-301
bool    ReadAddressC(void)
{
  return(InBuff(0) == diCurr.bAddress);
}


// проверка результата операции для счётчиков CC-301
bool    ReadResultC(void)
{
  TestResult(InBuff(3));
  return(ReadAddressC() && (InBuff(3) == 0));
}



// посылка запроса на открытие канала связи
void    QueryOpenC(void)
{ /*
  InitPush(0);

  PushChar(diCurr.bAddress);       
  PushChar(31);
  PushChar(0);
  PushChar(0);

  PushChar('0');
  PushChar('0');
  PushChar('0');
  PushChar('0');
  PushChar('0');
  PushChar('0');
  PushChar('0');
  PushChar('0');

  RevQueryIO(4+2, 4+8+2);
  */
  InitPush(0);

  PushChar(diCurr.bAddress);       
  PushChar(3);
  PushChar(32);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+6+2, 3+3+2);
}



// посылка запроса на чтение логического номера
void    QueryIdC(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);       
  PushChar(3);
  PushChar(21);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+1+2, 3+3+2);
}


// чтение логического номера
bool    ReadIdC(void)
{
  InitPop(0);
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 3) return 0;
  if (PopChar() != 21) return 0;
  if (PopChar() != 0) return 0;
  if ((PopChar() != diCurr.bAddress) && (0 != diCurr.bAddress)) return 0;

  return 1;
}



// посылка запроса на чтене времени/даты
void    QueryTimeC(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);       
  PushChar(3);
  PushChar(32);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+6+2, 3+3+2);
}


// чтение времени/даты
time    ReadTimeC(void)
{
time  ti;

  InitPop(4);

  ti.bSecond = PopChar();
  ti.bMinute = PopChar();
  ti.bHour   = PopChar();
  ti.bDay    = PopChar();
  ti.bMonth  = PopChar();
  ti.bYear   = PopChar();

  return ti;
}



void    QueryControlC(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);       
  PushChar(16);
  PushChar(32);
  PushChar(0);

  PushChar( tiCurr.bSecond );
  PushChar( tiCurr.bMinute );
  PushChar( tiCurr.bHour   );
  PushChar( tiCurr.bDay    );
  PushChar( tiCurr.bMonth  );
  PushChar( tiCurr.bYear   );

  RevQueryIO(4+2, 4+6+2);
}


void    QueryVersionC(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(20);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+4+2, 3+3+2);
}


void    ReadVersionC(void)
{
  InitPop(4);
  
  Clear();
  sprintf(szLo+2, "версия %c%c%c%c", PopChar(), PopChar(), PopChar(), PopChar());
}


// посылка запроса на чтение энергии для счётчиков CC-301
void    QueryEnergyAbsC(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(1);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


// посылка запроса на чтение энергии для счётчиков CC-301
void    QueryEnergyMonC(uchar  ibMonth)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(3);

  PushChar(ibMonth);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


// посылка запроса на чтение энергии для счётчиков CC-301
void    QueryEnergyDayC(uchar  ibDay)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(2);

  PushChar(ibDay);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


// чтение энергии
void    ReadEnergyC(void)
{
uchar   i;

  InitPop(4);

  for (i=0; i<4; i++)
  {
    coEnergy.mpbBuff[0] = PopChar();
    coEnergy.mpbBuff[1] = PopChar();
    coEnergy.mpbBuff[2] = PopChar();
    coEnergy.mpbBuff[3] = PopChar();

    mpdwChannelsA[i] = coEnergy.dwBuff;
  }

  coEnergy.dwBuff = mpdwChannelsA[diCurr.ibLine];
}


void    InitHeaderC_1(void)
{
  iwMajor = 0;

  if (!UseBounds())
    wBaseCurr = 0;
  else 
  {
    wBaseCurr = mpcwStartRelCan[ibDig];

    Clear();
    sprintf(szLo+1,"начало %04u:%02u",wBaseCurr,(uchar)(wBaseCurr/48 + 1));

    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;
}


void    InitHeaderC_6(void)
{
uchar i;

  if (!UseBounds())
    wBaseCurr = 0;
  else 
  {
    wBaseCurr = (mpcwStartRelCan[ibDig] / 6) * 6;

    Clear();
    sprintf(szLo+1,"начало %04u:%02u",wBaseCurr,(uchar)(wBaseCurr/48 + 1));

    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;

  i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / 6) * 6;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
}


void    QueryHeaderC_1(void)
{
  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(36);

  PushChar(tiDig.bMonth);
  PushChar(tiDig.bDay);
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);

  RevQueryIO(4+8+2, 3+3+2);
}


void    QueryHeaderC_6(void)
{
  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(40);

  PushChar(tiDig.bMonth);
  PushChar(tiDig.bDay);
  PushChar(tiDig.bHour*2 + tiDig.bMinute/30);

  RevQueryIO(4+8*6+2, 3+3+2);
}


bool    ReadHeaderC(uchar  i)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);


  ShowProgressDigHou();      

  InitPop(4+i*8);

  uchar c;
  for (c=0; c<4; c++)        
  {
    uint w = PopChar();
    w += PopChar()*0x100;

    mpwChannels[c] = w;
  }

  if (IsDefect(ibDig)) MakeSpecial(tiDig);
  return(MakeStopHou(0));  
}


bool    ReadHeaderC_1(void)
{
  return ReadHeaderC(0);
}


bool    ReadHeaderC_6(void)
{
uchar i;

  for (i=0; i<6; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);
    dw += 5;
    dw -= (wBaseCurr + i);
    tiDig = HouIndexToDate(dw);

    if (dw < dwValueC)     
      if (ReadHeaderC(5-i) == 0) return(0);
  }
  
  wBaseCurr += 6;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}



void    ReadCurrentC(void)
{
  ReadEnergyC();

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdwChannelsA[i];
  }

  MakeCurrent(); // TODO MakeCurrent2();
}

#endif
