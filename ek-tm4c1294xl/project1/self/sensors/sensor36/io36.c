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
#include "unpack36.h"
#include "monitor36.h"
#include "io36.h"



void    Query36(uint  cwIn, uchar  cbOut)
{
  MonitorOutput36();
  Query(cwIn, cbOut, true);
}



bool    ValidInput36(void)
{
  InitPop(1);

  uint wFormat = PopIntBig();
//  MonitorString(" Format="); MonitorIntHex(wFormat);
  uint wSize = wFormat & 0x0FFF;
//  MonitorString(" wSize="); MonitorIntHex(wSize);

  uint wCRCexpected = MakeCRC16_X25InBuff(1, wSize-2);
//  MonitorString(" CRC="); MonitorIntHex(wCRCexpected);
  int i = wSize-1;
  uint wCRCactual = InBuff(i) + InBuff(i+1)*0x100; //MonitorIntHex(wCRCactual);
  if (wCRCexpected != wCRCactual) //? MonitorString(" CRC_ok") : MonitorString(" CRC_error");
    return false;

  return true;
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
      MonitorInput36();
      if (ValidInput36())
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
