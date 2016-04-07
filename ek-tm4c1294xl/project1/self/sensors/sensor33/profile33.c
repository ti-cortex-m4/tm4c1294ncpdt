/*------------------------------------------------------------------------------
PROFILE33.C


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
#include "../../special/special.h"
#include "../sensor31/automatic31.h"
#include "../sensor31/procedure31.h"
#include "automatic33.h"
#include "device33.h"
#include "profile33.h"



#ifndef SKIP_33

time                    tiProfile33;

static uint             wBaseCurr33, wBaseLast33, iwProfile33;

static uint             cwErrors33;



// переход на предыдущую запись
bool    DecIndex33(void)
{
  if (wBaseLast33 == wBaseCurr33)
  {
    if (iwProfile33 != 0) iwProfile33--; else return false;
  }
  else
  {
    if (iwProfile33 != 0) iwProfile33--; else iwProfile33 = wBaseLast33-1;
  }

  return true;
}



void    QueryTop33(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "чтение данных по идентификатору"

  PushCharCod(0x0A); // "указатели"
  PushCharCod(0x00);
  PushCharCod(0x00);

  if (GetVersion33() == 16)
    Query33(3+6+1, 3+3+1);
  else
    Query33(3+8+1, 3+3+1);
}



bool    ReadTop33(void)
{
  InitPop(3);

  wBaseLast33 = PopInt33(); // количество записей
  wBaseCurr33 = PopInt33(); // индекс текущей записи

  MonitorString("\n\n current index "); MonitorIntDec(wBaseCurr33);
  MonitorString("\n\n number "); MonitorIntDec(wBaseLast33);

  iwProfile33 = wBaseCurr33;

  cwErrors33 = 0; // количество ошибок чтения

  ClearProcedure31(true,true);

  Clear(); sprintf(szLo+3,"%4u:%-4u",wBaseLast33,wBaseCurr33); DelayInf();

  return DecIndex33();
}


void    QueryHeader33(void)
{
  MonitorString("\n\n index "); MonitorIntDec(iwProfile33);

  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "чтение данных по идентификатору"

  PushCharCod(0x0B); // "график нагрузки"
  PushCharCod(iwProfile33 / 0x100);
  PushCharCod(iwProfile33 % 0x100);

  if (GetVersion33() == 16)
    Query33(3+8+1, 3+3+1);
  else
    Query33(3+6+1, 3+3+1);
}


bool    ReadHeader33(void)
{
  HideCurrTime(1);

  if (Checksum33(GetVersion33() == 16 ? 8 : 6) == false)
  {
    MonitorString("\n bad CRC");

    Clear(); sprintf(szLo+3,"ошибки: %-4u",cwErrors33);
    return (++cwErrors33 < 48);
  }


  InitPop(3);
  time ti1 = ReadPackTime33();

  ShowProfileTime(ti1);
  if ((ti1.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }

  MonitorString("\n time1 "); MonitorTime(ti1); if ((ti1.bMinute % 30) != 0) MonitorString(" ? ");


  time ti2 = mtiProcedure31Dig[ibDig];
  bool new = (ti2.bYear == 0);
  bool add = false;

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N33; i++)
  {
    double db = (GetVersion33() == 16) ? PopLong33() : PopInt33();
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

    for (i=0; i<MAX_LINE_N33; i++)
    {
      MonitorString("\n value2 ");
      MonitorIntDec(mpwChannels[i]);
    }

    if (SearchDefHouIndex(ti2) == false)
      return (++cwErrors33 < 48);
    else
      cwErrors33 = 0;

    ShowProgressDigHou();

    MakeSpecial(ti2) ? MonitorString("\n is added") : MonitorString("\n isn't added");
    return MakeStopHou(0);
  }
  else
  {
    MonitorString("\n don't add");
    return true;
  }
}

#endif
