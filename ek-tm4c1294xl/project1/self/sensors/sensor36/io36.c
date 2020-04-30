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
#include "include36.h"
#include "router36.h"
#include "../sensor35/device35.h"
#include "action36.h"
#include "../sensor35/timer35.h"
#include "../sensor35/log35.h"
#include "io36.h"



static bool                 fBccSave;
static uint                 cwInSave;
static uchar                cbOutSave;
static uchar                cbHeaderMaxSave;
static uchar                bCommandSave;



void    Query36Internal(bool  fBcc, uint  cwIn, uchar  cbOut, uchar  cbHeaderMax, uchar  bCommand)
{
  fBccSave = fBcc;
  cwInSave = cwIn;
  cbOutSave = cbOut;
  cbHeaderMaxSave = cbHeaderMax;
  bCommandSave = bCommand;


  MonitorOut(cwIn, cbOut);


  if (cbOut > 0)
  {
    if (fBcc)
    {
      // расчет CRC счетчика
      cbHeaderBcc = cbHeaderMax;
      cwInBuffBcc = 0;

      InitPush(0);

      uchar bSum = 0;
      bool f = false;

      uchar j;
      for (j=0; j<cbOut-1; j++)
      {
        uchar b = SkipChar();
        if (f == true) bSum += b;
        if ((b & 0x7F) == 0x01) f = true;
      }

      PushChar1Bcc(bSum);
    }
/*
#ifdef MONITOR_36
    MonitorString("\n sensor pack start");
    MonitorOut(cwIn, cbOut);
#endif

    cbOut = Pack35(cbOut);

#ifdef MONITOR_36
    MonitorString("\n sensor pack finish");
    MonitorOut(cwIn, cbOut);
#endif
*/
    // перенос пакета счетчика внутри пакета концентратора
    uchar i;
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

#ifdef MONITOR_36
  MonitorString("\n router pack start");
  MonitorOut(cwIn, cbOut);
#endif

  cbOut = Pack35(cbOut);

#ifdef MONITOR_36
  MonitorString("\n router pack finish");
#endif

  Query(cwIn,cbOut,true);
}


void    Query36(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax)
{
  SetTimer35(0);
  Query36Internal(false, cwIn, cbOut, cbHeaderMax, NNCL2_DATA_SET);
}


void    BccQuery36(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax)
{
  SetTimer35(0);
  Query36Internal(true, cwIn, cbOut, cbHeaderMax, NNCL2_DATA_SET);
}


void    Query36Repeat(void)
{
  MonitorString("\n repeat last query");
  Log35(R35_REPEAT_LAST_QUERY, bCommandSave);

  Query36Internal(fBccSave, cwInSave, cbOutSave, cbHeaderMaxSave, bCommandSave);
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
      Decompress36();

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (ChecksumRouter36() == 0)
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


serial  Input36_(bool  fIgnoreChecksumError)
{
  SaveDisplay();

  bool repeat;
  do
  {
    Input36Internal();
    repeat = false;

    if (mpSerial[ibPort] == SER_GOODCHECK)
    {
      action35 action = Action36(false, fIgnoreChecksumError);
      if (action == A35_WAIT)
      {
        Query36Internal(false, 2000, 0, 0, NNCL2_DATA_GET);
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


serial  Input36(void) {
  return Input36_(false);
}



bool    NoData36(void) {
  return (IndexInBuff() == 3)
          && (InBuff(0) == 0x82)
          && (InBuff(1) == 0x03)
          && (InBuff(2) == 0x03);
}
