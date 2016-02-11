/*------------------------------------------------------------------------------
PROFILE32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../special/special.h"
#include "../sensor31/automatic31.h"
#include "../sensor31/procedure31.h"
#include "automatic32.h"
#include "device32.h"
#include "profile32.h"



#ifndef SKIP_32

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

  wBaseLast32 = PopIntBig(); // количество записей
  wBaseCurr32 = PopIntBig(); // индекс текущей записи

  MonitorString("\n\n current index "); MonitorIntDec(wBaseCurr32);
  MonitorString("\n\n number "); MonitorIntDec(wBaseLast32);

  iwProfile32 = wBaseCurr32;

  cwErrors32 = 0; // количество ошибок чтения

  ClearProcedure31();

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

  if (GetVersion32() == 54)
    Query32(3+6+1, 3+3+1);
  else
    Query32(3+7+1, 3+3+1);
}



bool    ReadHeader32(void)
{
  HideCurrTime(1);

  if (Checksum32(GetVersion32() == 54 ? 6 : 7) == false)
  {
    MonitorString("\n bad CRC");

    Clear(); sprintf(szLo+3,"ошибки: %-4u",++cwErrors32);
    return (cwErrors32 < 48);
  }


  InitPop(3);
  time ti1 = ReadPackTime32();

  ShowProfileTime(ti1);
  if ((ti1.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }

  MonitorString("\n time1 "); MonitorTime(ti1); if ((ti1.bMinute % 30) != 0) MonitorString(" ? ");


  ShowProgressDigHou();


  time ti2 = mtiProcedure31Dig[ibDig];
  bool new = (ti2.bYear == 0);
  bool add = false;

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N32; i++)
  {
    double db = (GetVersion32() == 54) ? PopIntBig() : PopChar3Big32();
    MonitorString("\n value1 "); MonitorLongDec(db);

    if (new)
    {
   	  MonitorString("\n clean start ");
      AddProcedure31(ti1, ibDig, i, db);
    }
    else
    {
      uchar idx1 = GetProcedure31Idx(ti1); MonitorString("\n idx1 "); MonitorCharDec(idx1);
      uchar idx2 = GetProcedure31Idx(ti2); MonitorString(" idx2 "); MonitorCharDec(idx2);

      if (idx1 == idx2)
      {
        MonitorString("\n the same idx ");
        AddProcedure31(ti1, ibDig, i, db);
      }
      else
      {
        add = true;
        MonitorString("\n another idx ");

        SubProcedure31(ti1, ibDig, i, dbPulse);

        MonitorString("\n next start ");
        AddProcedure31(ti1, ibDig, i, db);
      }
    }
  }

  if (add)
  {
    MonitorString("\n time2 "); MonitorTime(ti2);
    ulong dw = DateToHouIndex(ti2);
    if (ti2.bMinute % 30 == 0) dw--;
    ti2 = HouIndexToDate(dw);
    MonitorString("\n time2 "); MonitorTime(ti2);

    for (i=0; i<MAX_LINE_N32; i++)
    {
      MonitorString("\n value2 ");
      MonitorIntDec(mpwChannels[i]);
    }

    if (SearchDefHouIndex(ti2) == 0) return (++cwErrors32 < 48);
    cwErrors32 = 0;

    MakeSpecial(ti2);
    return MakeStopHou(0);
  }
  else
  {
    return MakeStopHou(0);
  }
}

#endif
