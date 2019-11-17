/*------------------------------------------------------------------------------
POSTINPUT35!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_profile.h"
//#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
//#include "../../time/timedate.h"
#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/input_wrapper.h"
#include "../../serial/monitor.h"
//#include "../../devices/devices.h"
//#include "../../digitals/digitals.h"
#include "../../digitals/wait_answer.h"
#include "unpack35.h"
#include "device35.h"
#include "automatic35.h"
#include "io35.h"
#include "postinput35.h"



#ifndef SKIP_35

volatile device         deCurr35;



void    PostInput35(void)
{
    if (InBuff(7) == 0x14)
    {
//      sprintf(szLo,"  ожидание: %u   ",(r++ / 2) + 1); Delay(500);
//
//      MonitorString("\n NNCL2 repeat");
//

      deCurr35 = GetCurr();

      cbRepeat = MaxRepeats();
      Query35Internal(250, 0, 0x12);
      SetCurr(DEV_DATAGET_35);
//      repeat = true;
    }
    else if (InBuff(7) == 0x12)
    {
//      if (IndexInBuff() < 15)
//      {
//        MonitorString("\n NNCL2 wrong size");
//        MonitorIntDec(IndexInBuff());
//
//        Clear(); sprintf(szLo+1,"ошибка: 35.4.%u",InBuff(7)); // TODO 35
//        DelayInf();
//        mpSerial[ibPort] = SER_BADCHECK;
//      }
//      else
//      {
//        MonitorString("\n NNCL2 success");
//
//        uchar i;
//        for (i=0; i<IndexInBuff()-15; i++)
//          SetInBuff(i, InBuff(12+i));
//
//        // TODO 35 проверить данные
//      }
    }
    else
    {
//      MonitorString("\n NNCL2 failure");
//      MonitorCharDec(InBuff(7));
//
//      Clear(); sprintf(szLo+1,"ошибка: 35.5.%u",InBuff(7));
//      DelayInf();
//      mpSerial[ibPort] = SER_BADCHECK;
    }
}

#endif
