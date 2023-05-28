/*------------------------------------------------------------------------------
extended_4t_41.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../sensor38/device38.h"
#include "../sensor38/io38.h"
#include "../sensor38/dff.h"
#include "include41.h"
#include "automatic_get_time_41.h"
#include "extended_4t_41.h"

#ifdef  MONITOR_41
#include "../../time/rtc.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#endif



// �������� ��������� �� ������ �������
void    QueryEngMonTariff41(uchar  ibMonRel)
{
//  MonitorString("\n QueryEngMonTariff41 "); MonitorCharDec(ibMonRel);

  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0B); // GET_DATA_MULTIPLE_EX
  PushChar(0x00);

  PushChar(0x09); // A+
  PushChar(0x02);
  PushChar(0x1E); // ������� �� 4 �������
  PushChar(ibMonRel);
  PushChar(ibMonRel);
/*
  PushChar(0x0A); // A-
  PushChar(0x02);
  PushChar(0x1E);
  PushChar(ibMonRel);
  PushChar(ibMonRel);

  PushChar(0x0B); // R+
  PushChar(0x02);
  PushChar(0x1E);
  PushChar(ibMonRel);
  PushChar(ibMonRel);

  PushChar(0x0C); // R-
  PushChar(0x02);
  PushChar(0x1E);
  PushChar(ibMonRel);
  PushChar(ibMonRel);
*/
  Query38(250, 33-15);
}



status   ReadEngMonTariff41_Full(uchar  ibMonRel, uchar  ibTariff)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryEngMonTariff41(ibMonRel);

    if (Input38() == SER_GOODCHECK) break;
    if (fKey == true) return ST_BADDIGITAL;
  }

  if (r == MaxRepeats()) return ST_BADDIGITAL;
  ShowPercent(70+ibTariff);


  uchar* pbIn = InBuffPtr(10);

  uchar i;
  for (i=0; i<MAX_LINE_41; i++)
  {
    *(pbIn++);

    uchar t;
    for (t=0; t<4; t++)
    {
      int64_t ddw = 0;
      pbIn = DffDecodePositive(pbIn, &ddw);

      uchar bStatus = (ddw % 0x100) & 0x03;
      ulong dw = (ddw >> 3) % 0x100000000;

#ifdef MONITOR_41
      MonitorString("\n status="); MonitorCharDec(bStatus);
      MonitorString(" value="); MonitorLongDec(dw);
#endif

      if (!GoodStatus38(bStatus)) {
        Clear();
        sprintf(szLo+1, "����� -%u (%u) ?", ibMonRel, bStatus);
        Delay(1000);
        return ST_NOTPRESENTED;
      }

      if (t == ibTariff)
      {
        mpdwChannelsA[i] = dw;
        mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
      }  
    }  
  }

  return ST_OK;
}



status  ReadCntMonCanTariff41(uchar  ibMonAbs, uchar  ibTariff) // �� ������ ������
{
  time2 ti2 = ReadTimeCan41();
  if (ti2.fValid == 0) return ST_BADDIGITAL;
  time ti = ti2.tiValue;


  uchar ibMonRel = (bMONTHS+ti.bMonth-1-ibMonAbs) % bMONTHS;
  status st = ReadEngMonTariff41_Full(ibMonRel, ibTariff);
  if (st != ST_OK) return st;


  uchar i;
  for (i=0; i<MAX_LINE_41; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}



#ifdef  MONITOR_41

double2 TestCntMonCanTariff41(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  uchar bMonth = (*GetCurrTimeDate()).bMonth;

  uchar m;
  for (m=0; m<4; m++)
  {
    uchar ibMonAbs = (12 + bMonth - 1 - m) % 12;

    uchar t;
    for (t=0; t<4; t++)
    {
      MonitorString("\n\n month="); MonitorCharDec(ibMonAbs+1);
      MonitorString(" tariff="); MonitorCharDec(t);
      status s = ReadCntMonCanTariff41(ibMonAbs, t);
      MonitorString("\n result="); MonitorCharDec(s);

      uchar i;
      for (i=0; i<MAX_LINE_41; i++)
      {
        MonitorString("\n mpdbChannelsC[");
        MonitorCharDec(i);
        MonitorString("]=");
        MonitorDouble6(mpdbChannelsC[i]);
      }
    }
  }

  return GetDouble0(0);
}

#endif