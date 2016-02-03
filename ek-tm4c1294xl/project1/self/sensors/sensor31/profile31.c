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
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../special/special.h"
#include "automatic31.h"
#include "device31.h"
#include "profile31.h"



#ifndef SKIP_31

time                    tiProfile31;

static uint             wBaseCurr31, wBaseLast31, iwProfile31;

static uint             cwErrors31;



// ������� �� ���������� ������
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
  PushChar(0x06); // "������ ������ �� ��������������"

  PushCharCod(0x0B); // "���������"
  PushCharCod(0x00);
  PushCharCod(0x00);

  Query31(3+13+1, 3+3+1);
}



bool    ReadTop31(void)
{
  InitPop(3+2);

  wBaseCurr31 = PopIntLtl(); // ������ ������� ������
  wBaseLast31 = PopIntLtl(); // ���������� �������

  MonitorString("\n\n current index "); MonitorIntDec(wBaseCurr31);
  MonitorString("\n\n number "); MonitorIntDec(wBaseLast31);

  iwProfile31 = wBaseCurr31;

  cwErrors31 = 0; // ���������� ������ ������

  Clear(); sprintf(szLo+2,"%5u:%-5u",wBaseLast31,wBaseCurr31); DelayInf();

  return DecIndex31();
}


void    QueryHeader31(void)
{
  MonitorString("\n\n index "); MonitorIntDec(iwProfile31);

  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "������ ������ �� ��������������"

  PushCharCod(0x0E); // "������ ��������"
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

      Clear(); sprintf(szLo+3,"������: %-4u",++cwErrors31);
      return (cwErrors31 < 48);
    }
  }


  InitPop(3);
  time ti1 = ReadPackTime31();

  ShowProfileTime(ti1);
  if ((ti1.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }

  MonitorString("\n time "); MonitorTime(ti1); if ((ti1.bMinute % 30) != 0) MonitorString(" ? ");

  ulong dw = DateToHouIndex(ti1);
  dw--;
  time ti2 = HouIndexToDate(dw); // ����� ������ ������ �������������� ������ ������������ �����

  MonitorTime(ti2);


  if (SearchDefHouIndex(ti2) == 0) return (++cwErrors31 < 48);
  cwErrors31 = 0;

  ShowProgressDigHou();


  bool def = IsDefect(ibDig);
  //bool add = ((ti1.bMinute % 30 == 0) || def);
  MonitorString("\n def "); MonitorCharDec(def); //MonitorString(" add "); MonitorCharDec(add);

  InitPop(3+4+4*6*3);

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    double db = PopFloat31();
    MonitorString("\n value "); MonitorLongDec(db*1000); MonitorString("+"); MonitorLongDec(mpdbEngFracDigCan[ibDig][i]*1000);

    db /= 1000;
    mpdbEngFracDigCan[ibDig][i] += db;

    if (def)
    {
      uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
      MonitorString("="); MonitorIntDec(w);
      mpwChannels[i] = w;

      mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
      MonitorString("+"); MonitorLongDec(mpdbEngFracDigCan[ibDig][i]*1000);
    }
    else
    {
      MonitorString(" skip ");
    }
  }

  if (def)
  {
    MonitorString("\n add value");
    MakeSpecial(ti2);
  }
  else
  {
    MonitorString("\n don't add value");
  }

  return MakeStopHou(0);
}


#endif
