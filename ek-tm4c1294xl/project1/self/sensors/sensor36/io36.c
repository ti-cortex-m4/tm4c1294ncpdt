/*------------------------------------------------------------------------------
IO36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/input_wrapper.h"
#include "../../serial/monitor.h"
#include "../../digitals/wait_answer.h"
#include "../sensor35/include35.h"
#include "../sensor35/pack35.h"
//#include "../sensor35/router35.h"
//#include "device35.h"
#include "action36.h"
#include "../sensor35/timer35.h"
#include "../sensor35/log35.h"
#include "io36.h"



static uint                 cwInSave;
static uchar                cbOutSave;
static uchar                bCommandSave;



void    Query36Internal(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax, uchar  bCommand)
{
  cwInSave     = cwIn;
  cbOutSave    = cbOut;
  bCommandSave = bCommand;


  MonitorOut(cwIn, cbOut);


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

  Query(cwIn,cbOut,true);
}


void    Query36(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax)
{
  SetTimer35(0);
  Query36Internal(cwIn, cbOut, cbHeaderMax, NNCL2_DATA_SET);
}


void    Query36Repeat(void)
{
  MonitorString("\n repeat last query");
  Log35(R35_REPEAT_LAST_QUERY, bCommandSave);

  Query36Internal(cbInSave, cbOutSave, bCommandSave);
}



static serial Input36Internal(void)
{
  InputStart();
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
      Decompress35();

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (ChecksumRouter35() == 0)
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return mpSerial[ibPort];
}


serial  Input36(void)
{
  SaveDisplay();

  bool repeat;
  do
  {
    Input36Internal();
    repeat = false;

    if (mpSerial[ibPort] == SER_GOODCHECK)
    {
      action35 action = Action36(false);
      if (action == A35_WAIT)
      {
        Query36Internal(250, 0, NNCL2_DATA_GET);
        repeat = true;
      }
      else if (action == A35_SUCCESS)
      {
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else if (action == A35_ERROR)
      {
        mpSerial[ibPort] = SER_BADCHECK;
      }
      else if (action == A35_BREAK)
      {
        mpSerial[ibPort] = SER_BADCHECK; // возможно стоит применить другое решение
      }
      else
      {
        ASSERT(false);
      }
    }
  } while (repeat);

  LoadDisplay();

  return mpSerial[ibPort];
}
