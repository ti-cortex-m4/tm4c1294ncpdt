/*------------------------------------------------------------------------------
DEVICE_C!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_realtime.h"
#include "../../display/display.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../digitals/current/current2.h"
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



void    QuerySerialC(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(18);

  PushChar(0);
  PushChar(0);
  PushChar(0);

  RevQueryIO(4+10+2, 3+3+2);
}


ulong   ReadSerialC(void)
{
  InitPop(4);

  ulong dw = 0;

  uchar i;
  for (i=0; i<10; i++)
  {
    uchar b = PopChar();
    if ((b < '0') || (b > '9')) break;

    dw = dw*10 + (b-'0');
  }

  return dw;
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



void    ReadCurrentC(void)
{
  ReadEnergyC();

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdwChannelsA[i];
  }

  MakeCurrent2();
}

#endif
