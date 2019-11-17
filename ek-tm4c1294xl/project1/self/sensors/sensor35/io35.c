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
#include "unpack35.h"
#include "device35.h"
//#include "automatic35.h"
#include "io35.h"



#ifndef SKIP_35

uchar                       cbRepeat35;


void    Query35Internal(uchar  cbIn, uchar  cbOut, uchar  bCommand)
{
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


  // заполнение пакета концентратора
  InitPush(0);
  PushChar(0xC0);

  PushChar(0x02);

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  PushChar(0x00);

  PushChar(bCommand);

  PushChar(0xB6);   // TODO 35
  PushChar(0x59);
  PushChar(0x00);
  PushChar(0x00);

  PushChar(0x00);


  // расчет CRC концентратора
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
  cbRepeat35 = 0;
  Query35Internal(cbIn, cbOut, 0x11);
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
      if (Checksum35Router() == 0)
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

  uint r = 0;

  bool repeat;
  do
  {
    Input35Internal();
    repeat = false;

    if (mpSerial[ibPort] == SER_GOODCHECK)
    {
       if (InBuff(7) == 0x14)
       {
         sprintf(szLo,"  ожидание: %u   ",(r++ / 2) + 1); Delay(500);

         MonitorString("\n NNCL2 repeat");

         Query35Internal(250, 0, 0x12);
         repeat = true;
       }
       else if (InBuff(7) == 0x12)
       {
         if (IndexInBuff() < 15)
         {
           MonitorString("\n NNCL2 wrong size");
           MonitorIntDec(IndexInBuff());

           Clear(); sprintf(szLo+1,"ошибка: 35.4.%u",InBuff(7)); // TODO 35
           DelayInf();
           mpSerial[ibPort] = SER_BADCHECK;
         }
         else
         {
           MonitorString("\n NNCL2 success");

           uchar i;
           for (i=0; i<IndexInBuff()-15; i++)
             SetInBuff(i, InBuff(12+i));

           // TODO 35 проверить данные
         }
       }
       else
       {
         MonitorString("\n NNCL2 failure");
         MonitorCharDec(InBuff(7));

         Clear(); sprintf(szLo+1,"ошибка: 35.5.%u",InBuff(7));
         DelayInf();
         mpSerial[ibPort] = SER_BADCHECK;
       }
    }
  } while (repeat);

  LoadDisplay();

  return mpSerial[ibPort];
}

#endif
