/*------------------------------------------------------------------------------
PROFILE32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../special/special.h"
#include "../sensor31/automatic31.h"
#include "automatic32.h"
#include "device32.h"
#include "profile32.h"



#ifndef SKIP_N32

time                    tiProfile32;

static uint             wBaseCurr32, wBaseLast32, iwProfile32;

static uint             cwErrors32;



// переход на предыдущую запись
bool    DecIndex32(void)
{
  if (wBaseLast32 == wBaseCurr32)
  {
    if (iwProfile32 != 0) iwProfile32--; else return false;
  }
  else
  {
    if (iwProfile32 != 0) iwProfile32--; else iwProfile32 = wBaseLast32-1;
  }

  return true;
}



void    QueryTop32(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "чтение данных по идентификатору"

  PushCharCod(0x0A); // "указатели"
  PushCharCod(0x00);
  PushCharCod(0x00);

  Query32(3+8+1, 3+3+1);
}



bool    ReadTop32(void)
{
  InitPop(3);

  wBaseLast32 = PopIntLtl(); // количество записей
  wBaseCurr32 = PopIntLtl(); // индекс текущей записи

  MonitorString("\n\n current index "); MonitorIntDec(wBaseCurr32);
  MonitorString("\n\n number "); MonitorIntDec(wBaseLast32);

  iwProfile32 = wBaseCurr32;

  cwErrors32 = 0; // количество ошибок чтения

  Clear(); sprintf(szLo+3,"%4u:%-4u",wBaseLast32,wBaseCurr32); DelayInf();

  return DecIndex32();
}


void    QueryHeader32(void)
{
  MonitorString("\n\n index "); MonitorIntDec(iwProfile32);

  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "чтение данных по идентификатору"

  PushCharCod(0x0B); // "график нагрузки"
  PushCharCod(iwProfile32 / 0x100);
  PushCharCod(iwProfile32 % 0x100);

  Query32(3+5+1, 3+3+1);
}


bool    ReadHeader32(void)
{
  HideCurrTime(1);

//  if (NewVersion32())
//  {
//    uint wCRC = MakeCrc16Bit32InBuff(3, 100);
//    if (wCRC != InBuff(103) + InBuff(104)*0x100)
//    {
//      MonitorString("\n bad CRC");
//
//      Clear(); sprintf(szLo+3,"ошибки: %-4u",++cwErrors32);
//      return (cwErrors32 < 48);
//    }
//  }
//
//
//  InitPop(3);
//  time ti1 = ReadPackTime32();
//
//  ShowProfileTime(ti1);
//  if ((ti1.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }
//
//  MonitorString("\n time "); MonitorTime(ti1); if ((ti1.bMinute % 30) != 0) MonitorString(" ? ");
//
//  ulong dw = DateToHouIndex(ti1);
//  dw--;
//  time ti2 = HouIndexToDate(dw); // время записи должно соответсвовать началу получасового блока
//
//  MonitorTime(ti2);
//
//
//  if (SearchDefHouIndex(ti2) == 0) return (++cwErrors32 < 48);
//  cwErrors32 = 0;
//
//
//  ShowProgressDigHou();
//  double dbPulse = mpdbPulseHou[ibDig];
//
//  InitPop(3+4+4*6*3);
//
//  uchar i;
//  for (i=0; i<MAX_LINE_N32; i++)
//  {
//    float fl = PopFloat32();
//    MonitorString("\n value "); MonitorLongDec(fl);
//
//    fl /= 1000;
//    mpdbEngFracDigCan[ibDig][i] += fl;
//
//    if (ti1.bMinute % 30 == 0)
//    {
//      uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
//      MonitorString(" "); MonitorIntDec(w);
//      mpwChannels[i] = w;
//
//      mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
//    }
//    else
//    {
//      MonitorString(" ? ");
//    }
//  }
//
//  if (IsDefect(ibDig))
//  {
//    MonitorString("\n add value");
//    MakeSpecial(ti2);
//  }

  return MakeStopHou(0);
}


#endif
