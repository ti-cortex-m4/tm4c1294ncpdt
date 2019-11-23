/*------------------------------------------------------------------------------
IO35!C


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
#include "include35.h"
#include "unpack35.h"
#include "device35.h"
#include "action35.h"
#include "timer35.h"
#include "io35.h"



#ifndef SKIP_35

static uchar                cbInSave;
static uchar                cbOutSave;
static uchar                bCommandSave;



void    Query35Internal(uchar  cbIn, uchar  cbOut, uchar  bCommand)
{
  cbInSave     = cbIn;
  cbOutSave    = cbOut;
  bCommandSave = bCommand;


  if (cbOut > 0)
  {
    // расчет CRC счетчика
    uchar bCrc = MakeCrcSOutBuff(1, cbOut-3);

    InitPush(0);
    PushChar(0xC0);

    uchar i;
    for (i=0; i<cbOut-3; i++) SkipChar();

    PushChar(bCrc);
    PushChar(0xC0);


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


  // упаковка по протоколу SLIP
  uchar i;
  for (i=0; i<=cbOut-1; i++)
    mpbOutBuffSave[i] = OutBuff(i);

  uchar j = 0;
  SetOutBuff(j++, 0xC0);
  for (i=1; i<=cbOut-2; i++)
  {
    if (mpbOutBuffSave[i] == 0xC0)
    {
      SetOutBuff(j++, 0xDB);
      SetOutBuff(j++, 0xDC);
    }
    else if (mpbOutBuffSave[i] == 0xDB)
    {
      SetOutBuff(j++, 0xDB);
      SetOutBuff(j++, 0xDD);
    }
    else
    {
      SetOutBuff(j++, mpbOutBuffSave[i]);
    }
  }
  SetOutBuff(j++, 0xC0);


  Query(cbIn,j,true);
}


void    Query35(uchar  cbIn, uchar  cbOut)
{
  SetTimer35(0);
  Query35Internal(cbIn, cbOut, NNCL2_DATA_SET);
}


void    Query35Repeat(void)
{
  Query35Internal(cbInSave, cbOutSave, bCommandSave);
}



static serial Input35Internal(void)
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


serial  Input35(void)
{
  SaveDisplay();

  bool repeat;
  do
  {
    Input35Internal();
    repeat = false;

    if (mpSerial[ibPort] == SER_GOODCHECK)
    {
        action35 action = Action35(false);

        if (action == A35_WAIT)
        {
          Query35Internal(250, 0, 0x12);
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
        else
        {
          ASSERT(false);
        }
/* TODO 35
       if (InBuff(7) == NNCL2_TIME)
       {
         sprintf(szLo+10,"%2u",GetTimer35());
         Delay(500);

         MonitorString("\n NNCL2 repeat");

         if (GetTimer35() >= 99)
         {
           Clear(); sprintf(szLo+1,"время ? %u",GetTimer35()); // TODO 35
           DelayInf();
           mpSerial[ibPort] = SER_BADCHECK;
         }
         else
         {
           Query35Internal(250, 0, 0x12);
           repeat = true;
         }
       }
       else if (InBuff(7) == NNCL2_DATA_GET)
       {
         if (IndexInBuff() < 15)
         {
           MonitorString("\n NNCL2 wrong size"); MonitorIntDec(IndexInBuff());

           Clear(); sprintf(szLo+1,"длина ? %u",IndexInBuff()); // TODO 35
           DelayInf();
           mpSerial[ibPort] = SER_BADCHECK;
         }
         else
         {
           MonitorString("\n NNCL2 success");

           uchar i;
           for (i=0; i<IndexInBuff()-15; i++)
             SetInBuff(i, InBuff(12+i));

           if (Checksum35Sensor() != 0)
           {
//             Clear(); sprintf(szLo+1,"ошибка: 35.5.%u",InBuff(8));
//             DelayInf();
             mpSerial[ibPort] = SER_BADCHECK;
           }
           else
           {
             // TODO 35
           }
         }
       }
       else if (InBuff(7) == NNCL2_ERROR)
       {
         MonitorString("\n NNCL2 error"); MonitorCharDec(InBuff(7));

         Clear(); sprintf(szLo+1,"ошибка ? %u",InBuff(8));
         DelayInf();
         mpSerial[ibPort] = SER_BADCHECK;
       }
       else
       {
         MonitorString("\n NNCL2 failure"); MonitorCharDec(InBuff(7));

         Clear(); sprintf(szLo+1,"команда ? %u",InBuff(7));
         DelayInf();
         mpSerial[ibPort] = SER_BADCHECK;
       }
*/
    }
  } while (repeat);

  LoadDisplay();

  return mpSerial[ibPort];
}

#endif
