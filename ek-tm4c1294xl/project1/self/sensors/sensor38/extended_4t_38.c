/*------------------------------------------------------------------------------
extended_4t_38.c


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
#include "device38.h"
#include "io38.h"
#include "dff.h"
#include "automatic_get_time_38.h"
#include "extended_4t_38.h"



#include "../../serial/monitor.h"

/*
счетчики на начало мес€цев по тарифам
 «апрос
03.06.2020 22:29:44.414
06 E8 B7 C4 04 00 06
0B GET_DATA_MULTIPLE_EX
00
09 // A+
02
1E по 4 тарифам
01 мес€ц
02 мес€ц
BE A6

 */

// значени€ счетчиков на начало мес€цев
void    QueryEngMonTariff38(uchar  ibMonRel)
{
  MonitorString("\n ibMonRel="); MonitorCharDec(ibMonRel);

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
  PushChar(0x1E); // энерги€ по 4 тарифам
  PushChar(ibMonRel);
  PushChar(ibMonRel);

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

  Query38(250, 33);
}



status   ReadEngMonTariff38_Full(uchar  ibMonRel, uchar  ibTariff)
{
  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryEngMonTariff38(ibMonRel);

    if (Input38() == SER_GOODCHECK) break;
    if (fKey == true) return ST_BADDIGITAL;
  }

  if (r == MaxRepeats()) return ST_BADDIGITAL;
  ShowPercent(70+ibTariff);

  uchar ibIn = 10;

  uchar i;
  for (i=0; i<4; i++)
  {
    MonitorString("\n i="); MonitorCharDec(i);
    ibIn++;

    uchar t;
    for (t=0; t<4; t++)
    {
      MonitorString("\n t="); MonitorCharDec(t);

      uint64_t ddw = 0;
      uchar delta = pucDecodeBitArr((uchar *) &ddw, InBuffPtr(ibIn));
      if (delta == 0xFF) return ST_BADDIGITAL;
      ibIn += delta;

      ulong dw = ddw % 0x100000000;
      uchar bStatus = (ddw % 0x100) & 0x03;
      dw >>= 3;

      MonitorString("\n "); MonitorLongDec(dw); MonitorString(" "); MonitorCharDec(bStatus);

      if (bStatus != 0) {
        Clear();
        sprintf(szLo+1, "мес€ц -%u, %u ?", ibMonRel, bStatus);
        Delay(1000);
        return ST_NOTPRESENTED;
      }

      if (t == ibTariff)
      {
        MonitorString("\n ibTariff="); MonitorCharDec(ibTariff);

        mpdwChannelsA[i] = dw;
        mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
      }  
    }  
  }

  return ST_OK;
}



status  ReadCntMonCanTariff38(uchar  ibMonAbs, uchar  ibTariff) // на начало мес€ца
{
  time2 ti2 = ReadTimeCan38();
  if (ti2.fValid == 0) return ST_BADDIGITAL;
  time ti = ti2.tiValue;

  MonitorString("\n ibMonAbs="); MonitorCharDec(ibMonAbs);
  uchar ibMonRel = (bMONTHS+ti.bMonth-1-ibMonAbs) % bMONTHS; // TODO ? 2/1
  MonitorString("\n ibMonRel="); MonitorCharDec(ibMonRel);

  status st = ReadEngMonTariff38_Full(ibMonRel,ibTariff);

  if (st != ST_OK) return st;


  uchar i;
  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}

