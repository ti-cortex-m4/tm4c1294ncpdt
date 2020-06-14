/*------------------------------------------------------------------------------
io38.c


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
#include "pack38.h"
#include "decompress38.h"
#include "io38.h"




void    Query38(uchar  cbIn, uchar  cbOut)
{
  InitPush(cbOut-3);

  uint w = MakeCrc35OutBuff(1, cbOut-4);
  PushChar(w / 0x100);
  PushChar(w % 0x100);

  PushChar(0xC0);

  cbOut = Pack38(cbOut);

  Query(cbIn,cbOut,true);
}



serial  Input38(void)
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
      Decompress38();

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (MakeCrc35InBuff(1, IndexInBuff()-2) == 0)
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

  MonitorIn();
  return mpSerial[ibPort];
}
