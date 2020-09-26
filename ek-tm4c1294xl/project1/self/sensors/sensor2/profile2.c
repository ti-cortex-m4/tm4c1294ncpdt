/*------------------------------------------------------------------------------
PROFILE_2!C

 Меркурий-230
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/decret.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/limits.h"
#include "../../digitals/profile/refill.h"
#include "../../digitals/max_shutdown.h"
#include "../../special/special.h"
#include "../../flash/records.h"
#include "../../energy.h"
#include "profile2.h"



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
