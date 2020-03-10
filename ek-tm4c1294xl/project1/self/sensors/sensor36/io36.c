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
//#include "include35.h"
#include "unpack36.h"
//#include "router35.h"
//#include "device35.h"
//#include "action35.h"
//#include "timer35.h"
//#include "log35.h"
#include "io36.h"



void    Query36_Stop(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0xA0);
  PushChar(0x07);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x53);
  PushChar(0x80);
  PushChar(0xD7);
  PushChar(0x7E);

  Query(1000, 9, true);
}



void    Query36(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0xA0);
  PushChar(0x20);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x93);
  PushChar(0xFE);
  PushChar(0xC9);
  PushChar(0x81);
  PushChar(0x80);
  PushChar(0x14);
  PushChar(0x05);
  PushChar(0x02);
  PushChar(0x00);
  PushChar(0x80);
  PushChar(0x06);
  PushChar(0x02);
  PushChar(0x00);
  PushChar(0x80);
  PushChar(0x07);
  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x08);
  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0xCE);
  PushChar(0x6A);
  PushChar(0x7E);

  Query(1000, 34, true);
}



serial  Input36(void)
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
//      if (ChecksumRouter35() == 0)
//      {
//        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
//      }
//      else
//        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return mpSerial[ibPort];
}
