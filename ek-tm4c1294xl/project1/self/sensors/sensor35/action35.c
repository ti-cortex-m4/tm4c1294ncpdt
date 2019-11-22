/*------------------------------------------------------------------------------
action35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../display/display.h"
//#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
//#include "../../hardware/watchdog.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports2.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/input_wrapper.h"
//#include "../../serial/monitor.h"
//#include "../../devices/devices.h"
//#include "../../digitals/digitals_status.h"
//#include "../../digitals/wait_answer.h"
//#include "unpack35.h"
//#include "device35.h"
//#include "automatic35.h"
//#include "io35.h"
//#include "timer35.h"
//#include "timeout35.h"
//#include "status35.h"
#include "action35.h"



#ifndef SKIP_35

action35    Action35(void)
{
/*
    if (InBuff(7) == NNCL2_TIME)
    {
      sprintf(szHi+10,"%2u",GetTimer35());
      Delay(300); // Inf

      if (GetTimer35() >= 99)
      {
        // TODO 35
        Clear(); sprintf(szLo+1,"время ? %u",GetTimer35());
        MonitorString("\n sensor error: bad time "); MonitorIntDec(IndexInBuff());
        Delay(1000); // Inf
      }
      else
      {
        MonitorString("\n repeat: start");

        cbRepeat = MaxRepeats();
        Query35Internal(250, 0, NNCL2_DATA_GET);
        SetCurr(DEV_DATAGET_35);

        return;
      }
    }
    else if (InBuff(7) == NNCL2_DATA_GET)
    {
      Timeout35(GetTimer35());

      if (IndexInBuff() < 15)
      {
        Clear(); sprintf(szLo+1,"длина ? %u",IndexInBuff());
        MonitorString("\n sensor error: bad size "); MonitorIntDec(IndexInBuff());
        Delay(1000); // Inf
      }
      else
      {
        MonitorString("\n sensor success: good size ");

        uchar i;
        for (i=0; i<IndexInBuff()-15; i++)
          SetInBuff(i, InBuff(12+i));

        MonitorString("\n unwrap finished");
        MonitorIn();

        if (Checksum35Sensor() == 0)
        {
          MonitorString("\n sensor success");

          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
          return;
        }
        else
        {
            MonitorString("\n sensor failure");
        // TODO 35
        }
      }
    }
  else if (InBuff(7) == NNCL2_ERROR)
  {
    Clear(); sprintf(szLo+1,"ошибка ? %u",InBuff(8));
    MonitorString("\n router error: "); MonitorCharDec(InBuff(8));
    Delay(1000); // Inf
  }
  else
  {
    Clear(); sprintf(szLo+1,"команда ? %u",InBuff(7));
    MonitorString("\n router unknown command: "); MonitorCharDec(InBuff(7));
    Delay(1000); // Inf
  }

  MonitorString("\n repeat: bad check");
  mpSerial[ibPort] = SER_BADCHECK;
*/
}

#endif
