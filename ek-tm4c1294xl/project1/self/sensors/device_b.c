/*------------------------------------------------------------------------------
DEVICE_B!C

 Меркурий-230
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
#include "../digitals/digitals_messages.h"
#include "../digitals/limits.h"
#include "../digitals/profile/refill.h"
#include "../digitals/max_shutdown.h"
#include "../special/special.h"
#include "../flash/records.h"
#include "../energy.h"
#include "device_b.h"



#ifndef SKIP_B

// версии
uchar                   bVersionB1, bVersionB2, bVersionB3;



// проверка сетевого адреса
bool    ReadAddressB(void)
{
//  return(InBuff(0) == diCurr.bAddress);
  return(1);
}


// проверка результата операции
bool    ReadResultB(void)
{
  TestResult(InBuff(1));
  return(ReadAddressB() && (InBuff(1) == 0));
}



// открытие канала связи
void    QueryOpenB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(1);

  PushChar(bKeysLevelB);

  if (boEnblKeys != true)
  {
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
  }
  else
  {
    line ln = mpphKeys[ibDig];
    bool f = 0;

    uchar i;
    for (i=0; i<6; i++)
    {
      if (ln.szLine[i] == 0) f = 1;

      if (f == 0)
        PushChar(ln.szLine[i] - '0');
      else
        PushChar(0);
    }
  }

  QueryIO(2+2, 2+1+6+2);
}



void    QuerySerialB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(0);

  QueryIO(1+4+3+2, 3+0+2);
}


ulong   ReadSerialB(void)
{
  InitPop(1);

  ulong dw = PopChar()*1000000;
  dw += PopChar()*10000;
  dw += PopChar()*100;
  dw += PopChar();

  return dw;
}



// посылка запроса на чтение версии
void    QueryVersionB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(3);

  QueryIO(1+3+2, 3+0+2);
}


// чтение версии
void    ReadVersionB(void)
{
  InitPop(1);

  bVersionB1 = FromBCD( PopChar() );
  bVersionB2 = FromBCD( PopChar() );
  bVersionB3 = FromBCD( PopChar() );

  Clear();
  sprintf(szLo+1, "версия %u.%u.%u", bVersionB1, bVersionB2, bVersionB3);
  (boShowMessages == true) ? DelayMsg() : DelayInf();
}


// проверка версии: 7.1.0 и выше
bool    TestVersionB710(void)
{
  return ((uint)100*bVersionB1 + 10*bVersionB2 + bVersionB3 >= 710);
}



// посылка запроса на чтение логического номера
void    QueryIdB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(5);

  QueryIO(1+2+2, 3+0+2);
}


// чтение логического номера
bool    ReadIdB(void)
{
  InitPop(0);
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;
  if ((PopChar() != diCurr.bAddress) && (0 != diCurr.bAddress)) return 0;

  return 1;
}



// посылка запроса на чтение энергии
void    QueryEnergyB(uchar  bTime)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(5);                          // чтение накопленной энергии

  PushChar(bTime);                      // вид энергии
  PushChar(0);                          // по всем тарифам

  QueryIO(1+16+2, 2+2+2);
}


// чтение энергии
void    ReadEnergyB(void)
{
uchar   i;

  InitPop(1);

  for (i=0; i<4; i++)
  {
    coEnergy.mpbBuff[2] = PopChar();
    coEnergy.mpbBuff[3] = PopChar();
    coEnergy.mpbBuff[0] = PopChar();
    coEnergy.mpbBuff[1] = PopChar();

    if ((coEnergy.mpbBuff[0] == 0xFF) &&
        (coEnergy.mpbBuff[1] == 0xFF) &&
        (coEnergy.mpbBuff[2] == 0xFF) &&
        (coEnergy.mpbBuff[3] == 0xFF)) coEnergy.dwBuff = 0;

    mpdwChannelsA[i] = coEnergy.dwBuff;
  }

  coEnergy.dwBuff = mpdwChannelsA[diCurr.ibLine];
}



// посылка запроса на коррекцию времени
void    QueryControlB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(0x0D);

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  QueryIO(1+1+2, 3+3+2);
}


/*
// посылка запроса на установку времени
void    QueryManageB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(0x0C);

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  tiAlt = tiCurr;
  PushChar(Weekday()+1);

  PushChar( ToBCD(tiCurr.bDay)   );
  PushChar( ToBCD(tiCurr.bMonth) );
  PushChar( ToBCD(tiCurr.bYear)  );

  tiAlt = tiCurr;
  PushChar(Season());

  QueryIO(1+1+2, 3+8+2);
}
*/


// чтене времени/даты
void    QueryTimeB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(4);
  PushChar(0);

  QueryIO(1+8+2, 3+0+2);
}


// чтение времени/даты
time    ReadTimeB(void)
{
time  ti;

  InitPop(1);

  ti.bSecond = FromBCD( PopChar() );
  ti.bMinute = FromBCD( PopChar() );
  ti.bHour   = FromBCD( PopChar() );

  PopChar();

  ti.bDay    = FromBCD( PopChar() );
  ti.bMonth  = FromBCD( PopChar() );
  ti.bYear   = FromBCD( PopChar() );

  return ti;
}



// посылка запроса на чтение вершины массива
void    QueryTopB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(0x13);

  QueryIO(1+9+2, 2+1+2);
}


// чтение вершины массива
void    ReadTopBOld(void)
{
  // адрес обрабатываемого блока
  if (!UseBounds())
  {
    wBaseCurr = InBuff(1)*0x100 + InBuff(2);
    ResetLimitsAux(ibDig);
  }
  else
  {
    if (mpboStartCan[ibDig] == false)
    {
      wBaseCurr = InBuff(1)*0x100 + InBuff(2);
      if (boShowMessages == true) sprintf(szLo,"  начало %04X * ",wBaseCurr);
      ResetLimitsAux(ibDig);
    }
    else
    {
      wBaseCurr = mpcwStartAbs16Can[ibDig];
      if (boShowMessages == true) sprintf(szLo,"  начало %04X   ",wBaseCurr);
      iwMajor = wBaseCurr; AddDigRecord(EVE_PREVIOUS_TOP);
    }

    if (boShowMessages == true) DelayMsg();
  }

  // индекс по получасовому массиву
  iwDigHou = 0;

  // счётчик получасов в выключенном состоянии
  iwMajor = 0;

  StartRefill();

#ifdef  DAYS100
  dwTmpPrev = 0;

  wBaseInit = InBuff(1)*0x100 + InBuff(2);
#endif
}



// посылка запроса на чтение заголовка часового блока
void    QueryHeaderB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(6);
  PushChar(3);

  PushChar(wBaseCurr / 0x100);
  PushChar(wBaseCurr % 0x100);

  PushChar(15);

  QueryIO(1+15+2, 3+3+2);
}


// посылка запроса на чтение заголовка часового блока
void    QueryHeaderB_Plus(uchar  bSize)
{
  ShowLo(szWaiting);

  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(6);
  PushChar(4);

  PushChar(wBaseCurr / 0x100);
  PushChar(wBaseCurr % 0x100);

  PushChar(bSize);

  QueryIO((uint)18*bSize+2, 3+3+2);
}



bool    TestHeaderB(uchar  ibBlock)
{
  tiDig.bHour   = FromBCD( InBuff((uint)2+ibBlock*18) );// время/дата часового блока
  tiDig.bMinute = FromBCD( InBuff((uint)3+ibBlock*18) );
  tiDig.bDay    = FromBCD( InBuff((uint)4+ibBlock*18) );
  tiDig.bMonth  = FromBCD( InBuff((uint)5+ibBlock*18) );
  tiDig.bYear   = FromBCD( InBuff((uint)6+ibBlock*18) );

  if ((tiDig.bHour   == 99) &&                          // ошибка преобразователя
      (tiDig.bMinute == 99) &&
      (tiDig.bDay    == 99) &&
      (tiDig.bMonth  == 99) &&
      (tiDig.bYear   == 99))
  {
    ShowLo(szNoDevice); DelayMsg();
    return(0);
  }

  return(1);
}


// чтение заголовка часового блока
bool    ReadHeaderB(uchar  ibBlock, bool  fDelay)
{
  HideCurrTime(1);

  tiDig.bHour   = FromBCD( InBuff((uint)2+ibBlock*18) );// время/дата часового блока
  tiDig.bMinute = FromBCD( InBuff((uint)3+ibBlock*18) );
  tiDig.bDay    = FromBCD( InBuff((uint)4+ibBlock*18) );
  tiDig.bMonth  = FromBCD( InBuff((uint)5+ibBlock*18) );
  tiDig.bYear   = FromBCD( InBuff((uint)6+ibBlock*18) );

  if ((tiDig.bHour   == 0) &&                           // обрабатываем пустой блок
      (tiDig.bMinute == 0) &&
      (tiDig.bDay    == 0) &&
      (tiDig.bMonth  == 0) &&
      (tiDig.bYear   == 0))
  {
    if (++iwMajor > GetMaxShutdown()) return(0);
    sprintf(szLo," выключено: %-4u   ",iwMajor); if (fDelay == 1) DelayOff();

    if (iwDigHou != 0)
    {
       iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;

       ShowProgressDigHou();
       return(MakeStopHou(0));
    }
    else return(1);
  }


  if ((tiDig.bDay   == tiSummer.bDay) &&
      (tiDig.bMonth == tiSummer.bMonth))
  {
    if ((tiDig.bHour   == 3) &&
        (tiDig.bMinute == 0))
    {
      tiDig.bHour   = 2;
      tiDig.bMinute = 0;
    }
  }


  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if ((tiDig.bMinute % 30) != 0)                        // обрабатываем неполный получасовой блок
  {
    tiDig = HouIndexToDate(DateToHouIndex(tiDig) + 1);
  }
#ifdef  DAYS100
  else if (SearchDefHouIndex2(31*48) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); }

  if ((wBasePrev > wBaseInit) && (wBaseCurr <= wBaseInit)) return 0;
  wBasePrev = wBaseCurr;
#else
  if (SearchDefHouIndex(tiDig) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); }
#endif


  iwMajor = 0;                                          // обнуляем счётчик после получения правильных данных


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // время записи должно соответсвовать началу получасового блока

  ulong dw = DateToHouIndex(tiCurr);
  dw -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  time ti = HouIndexToDate(dw);


  ShowProgressDigHou();
  if (fDelay == 1) DelayOff();


  uchar i;
  for (i=0; i<4; i++)
  {
    uint w = InBuff( (uint)8+ibBlock*18+i*2 );
    w     += InBuff( (uint)9+ibBlock*18+i*2 )*0x100;

    if (w == 0xFFFF) w = 0;
    mpwChannels[i] = w;
  }

  MakeRefillWinter(ti);
  MakeSpecial(ti);
  if (boDsblRefill == false) MakeRefill(ti);
  return(MakeStopHou(0));
}



void    ReadCurrentB(void)
{
  ReadEnergyB();
  double db = mpdbLevel[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdwChannelsA[i] * db;
  }

  MakeCurrent();
}


#endif
