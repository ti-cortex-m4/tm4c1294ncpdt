/*------------------------------------------------------------------------------
PROFILE31.C


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
#include "../../time/timedate.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "procedure31.h"
#include "automatic31.h"
#include "device31.h"
#include "profile31.h"



#ifndef SKIP_31

time                    tiProfile31;

static uint             wBaseCurr31, wBaseLast31, iwProfile31;

static uint             cwErrors31;



// переход на предыдущую запись
bool    DecIndex31(void)
{
  if (wBaseLast31 == wBaseCurr31)
  {
    if (iwProfile31 != 0) iwProfile31--; else return false;
  }
  else
  {
    if (iwProfile31 != 0) iwProfile31--; else iwProfile31 = wBaseLast31-1;
  }

  return true;
}



void    QueryTop31(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "чтение данных по идентификатору"

  PushCharCod(0x0B); // "указатели"
  PushCharCod(0x00);
  PushCharCod(0x00);

  Query31(3+13+1, 3+3+1);
}



bool    ReadTop31(void)
{
  InitPop(3+2);

  wBaseCurr31 = PopIntLtl(); // индекс текущей записи
  wBaseLast31 = PopIntLtl(); // количество записей

  MonitorString("\n\n current index "); MonitorIntDec(wBaseCurr31);
  MonitorString("\n\n number "); MonitorIntDec(wBaseLast31);

  iwProfile31 = wBaseCurr31;

  cwErrors31 = 0; // количество ошибок чтения

  StartProcedure31();

  Clear(); sprintf(szLo+2,"%5u:%-5u",wBaseLast31,wBaseCurr31); DelayInf();

  return DecIndex31();
}


void    QueryHeader31(void)
{
  MonitorString("\n\n index "); MonitorIntDec(iwProfile31);

  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "чтение данных по идентификатору"

  PushCharCod(0x0E); // "график нагрузки"
  PushCharCod(iwProfile31 / 0x100);
  PushCharCod(iwProfile31 % 0x100);

  Query31(3+102+1, 3+3+1);
}


bool    ReadHeader31(void)
{
  HideCurrTime(1);

  if (NewVersion31())
  {
    uint wCRC = MakeCrc16Bit31InBuff(3, 100);
    if (wCRC != InBuff(103) + InBuff(104)*0x100)
    {
      MonitorString("\n bad CRC");

      Clear(); sprintf(szLo+3,"ошибки: %-4u",cwErrors31);
      return (++cwErrors31 < 48);
    }
  }


  InitPop(3);
  time ti1 = ReadPackTime31();

  ShowProfileTime(ti1);
  if ((ti1.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }

  MonitorString("\n time1 "); MonitorTime(ti1); if ((ti1.bMinute % 30) != 0) MonitorString(" ? ");


  time ti2 = mtiProcedure31Dig[ibDig];
  bool new = (ti2.bYear == 0);
  bool add = false;

  InitPop(3+4+4*6*3);

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    double db = PopFloat31();
    MonitorString("\n value1 "); MonitorLongDec(db);

    if (new)
    {
   	  MonitorString("\n clean start ");
      AddProcedure31(ti1, ibDig, i, db);
    }
    else
    {
      uchar bIdx1 = GetProcedure31Idx(ti1);
      ulong dwDay1 = DateToDayIndex(ti1); MonitorString("\n idx1 "); MonitorCharDec(bIdx1); MonitorString("/"); MonitorLongDec(dwDay1);

      uchar bIdx2 = GetProcedure31Idx(ti2);
      ulong dwDay2 = DateToDayIndex(ti2); MonitorString(" idx2 "); MonitorCharDec(bIdx2); MonitorString("/"); MonitorLongDec(dwDay2);

      bool fSameDay = (dwDay1 == dwDay2);
      bool fPrevDay = ((dwDay1 + 1 == dwDay2) && (bIdx1 == 47) && (bIdx2 == 47));

      MonitorString(" "); MonitorCharDec(bIdx1 == bIdx2); MonitorCharDec(fSameDay); MonitorCharDec(fPrevDay);

      if ((bIdx1 == bIdx2) && (fSameDay || fPrevDay))
      {
        MonitorString("\n the same idx ");
        AddProcedure31(ti1, ibDig, i, db);
      }
      else
      {
        add = true;
        MonitorString("\n another idx ");

        SubProcedure31(ti1, ibDig, i);

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

    if (SearchDefHouIndex(ti2) == false)
      return (++cwErrors31 < 48);
    else
      cwErrors31 = 0;

    ShowProgressDigHou();

    MakeSpecial31(ti2, MAX_LINE_N31) ? MonitorString("\n is added") : MonitorString("\n isn't added");
    return MakeStopHou(0);
  }
  else
  {
    MonitorString("\n don't add");
    return true;
  }
}

#endif
