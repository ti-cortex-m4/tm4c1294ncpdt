/*------------------------------------------------------------------------------
PROFILE2X12!C


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
#include "../../digitals/max_shutdown.h"
#include "../../special/special.h"
#include "../../flash/records.h"
#include "../../energy.h"
#include "profile2x12.h"



void    ReadTopBx12(void)
{
  // адрес обрабатываемого блока
  if (!UseBounds())
  {
    dwBaseCurr = InBuff(1); dwBaseCurr <<= 12; dwBaseCurr += InBuff(2) << 4;
    ResetLimitsAux(ibDig);
  }
  else
  {
    if (mpboStartCan[ibDig] == false)
    {
      dwBaseCurr = InBuff(1); dwBaseCurr <<= 12; dwBaseCurr += InBuff(2) << 4;
      if (boShowMessages == true) sprintf(szLo," начало %05lX * ",dwBaseCurr);
      ResetLimitsAux(ibDig);
    }
    else
    {
      dwBaseCurr = mpcdwStartAbs32Can[ibDig];
      if (boShowMessages == true) sprintf(szLo," начало %05lX   ",dwBaseCurr);
      iwMajor = dwBaseCurr % 0x10000; AddDigRecord(EVE_PREVIOUS_TOP);
    }

    if (boShowMessages == true) DelayMsg();
  }

  // индекс по получасовому массиву
  iwDigHou = 0;

  // счётчик получасов в выключенном состоянии
  iwMajor = 0;
}


void    QueryHeaderBx12(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(6);
  (dwBaseCurr > 0xFFFF) ? PushChar(0x83) : PushChar(0x03);

  PushChar((dwBaseCurr % 0x10000) / 0x100);
  PushChar(dwBaseCurr % 0x100);

  PushChar(15*12); // 180d = B4h

  QueryIO((uint)(1+15*12+2), 3+3+2);
}


bool    ReadHeaderBx12(uchar  ibBlock, bool  fDelay)
{
  HideCurrTime(1);

  InitPop((uint)(1+(12-1-ibBlock)*15));

  PopChar();
  tiDig.bHour   = FromBCD(PopChar());                   // время/дата часового блока
  tiDig.bMinute = FromBCD(PopChar());
  tiDig.bDay    = FromBCD(PopChar());
  tiDig.bMonth  = FromBCD(PopChar());
  tiDig.bYear   = FromBCD(PopChar());

  if ((tiDig.bHour   == 0) &&                           // обрабатываем пустой блок
      (tiDig.bMinute == 0) &&
      (tiDig.bDay    == 0) &&
      (tiDig.bMonth  == 0) &&
      (tiDig.bYear   == 0))
  {
    if (++iwMajor > GetMaxShutdown()) return(0);
    sprintf(szLo," выключено: %-4u   ",iwMajor); //if (fDelay == 1) DelayOff();

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
    tiDig.bMinute = (tiDig.bMinute / 30)*30;
    if (SearchDefHouIndex(tiDig) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); }

    iwDigHou = (wHOURS+iwDigHou+1)%wHOURS;
  }
  else if (SearchDefHouIndex(tiDig) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); }


  iwMajor = 0;                                          // обнуляем счётчик после получения правильных данных


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // время записи должно соответсвовать началу получасового блока

  ulong dw = DateToHouIndex(tiCurr);
  dw -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  time ti = HouIndexToDate(dw);


  ShowProgressDigHou();
  if (fDelay == 1) Delay(50);

  PopChar();

  uchar i;
  for (i=0; i<4; i++)
  {
    uint w = PopChar();
    w     += PopChar()*0x100;

    if (w == 0xFFFF) w = 0;
    mpwChannels[i] = w;
  }

  MakeSpecial(ti);
  return(MakeStopHou(0));
}
