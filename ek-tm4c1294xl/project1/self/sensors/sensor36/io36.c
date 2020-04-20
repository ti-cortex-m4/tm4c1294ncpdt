/*------------------------------------------------------------------------------
IO36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../display/display.h"
//#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
//#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
//#include "../../serial/input_wrapper.h"
#include "../../serial/monitor.h"
//#include "../../digitals/wait_answer.h"
#include "../sensor35/include35.h"
#include "../sensor35/pack35.h"
//#include "../sensor35/router35.h"
//#include "device35.h"
//#include "action35.h"
#include "../sensor35/timer35.h"
//#include "log35.h"
#include "io36.h"



static uchar                cbInSave;
static uchar                cbOutSave;
static uchar                bCommandSave;



void    Query36Internal(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax, uchar  bCommand)
{
  cbInSave     = cbIn;
  cbOutSave    = cbOut;
  bCommandSave = bCommand;


  MonitorOut(cbIn, cbOut);


  if (cbOut > 0)
  {
    // расчет CRC счетчика
      cbHeaderBcc = cbHeaderMax;
      cwInBuffBcc = 0;

      InitPush(0);

      uchar bSum = 0;
      bool f = false;

      uchar i;
      for (i=0; i<cbOut-1; i++)
      {
        uchar b = SkipChar();
        if (f == true) bSum += b;
        if ((b & 0x7F) == 0x01) f = true;
      }

      PushChar1Bcc(bSum);

#ifdef MONITOR_35
    MonitorString("\n sensor pack start");
    MonitorOut(cbIn, cbOut);
#endif

    cbOut = Pack35(cbOut);

#ifdef MONITOR_35
    MonitorString("\n sensor pack finish");
    MonitorOut(cbIn, cbOut);
#endif

    // перенос пакета счетчика внутри пакета концентратора
    for (i=0; i<cbOut; i++)
      SetOutBuff(cbOut+12-i, OutBuff(cbOut-1-i));
  }


  // заполнение пакета маршрутизатора
  InitPush(0);
  PushChar(0xC0);

  PushChar(0x02); // идентификатор протокола

  PushChar(0); // адрес маршрутизатора
  PushChar(0);
  PushChar(0);
  PushChar(0);

  PushChar(0x00); // флаги пакета и команды

  PushChar(bCommand); // код команды

  PushModemAddress35(); // адрес модема

  PushChar(0x00);


  // расчет CRC маршрутизатора
  InitPush(13+cbOut);

  uint w = MakeCrc35OutBuff(1, 13+cbOut-1);
  PushChar(w / 0x100);
  PushChar(w % 0x100);

  PushChar(0xC0);

  cbOut = 13+cbOut+3;

#ifdef MONITOR_35
  MonitorString("\n router pack start");
  MonitorOut(cbIn, cbOut);
#endif

  cbOut = Pack35(cbOut);

#ifdef MONITOR_35
  MonitorString("\n router pack finish");
#endif

  Query(cbIn,cbOut,true);
}


void    Query36(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax)
{
  SetTimer35(0);
  Query36Internal(cwIn, cbOut, cbHeaderMax, NNCL2_DATA_SET);
}


serial  Input36(void)
{
  return mpSerial[ibPort];
}
