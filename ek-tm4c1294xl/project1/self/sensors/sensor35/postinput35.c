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
#include "../../devices/devices.h"
//#include "../../digitals/digitals.h"
#include "../../digitals/digitals_status.h"
#include "../../digitals/wait_answer.h"
#include "unpack35.h"
#include "device35.h"
#include "automatic35.h"
#include "io35.h"
#include "postinput35.h"



#ifndef SKIP_35

volatile device         deCurr35;



device  GetCurr35(void)
{
  return deCurr35;
}



void    PostInput35(void)
{
    if (InBuff(7) == NNCL2_TIME)
    {
      Clear(); sprintf(szLo+2,"ожидание: %u",(cbRepeat35++ / 2) + 1); Delay(100);

      deCurr35 = GetCurr();

      cbRepeat = MaxRepeats();
      Query35Internal(250, 0, NNCL2_DATA_GET);
      SetCurr(DEV_DATAGET_35);
    }
    else if (InBuff(7) == NNCL2_DATA_GET)
    {
      if (IndexInBuff() < 15)
      {
        Clear(); sprintf(szLo+1,"длина ? %u",IndexInBuff());
        DelayInf();
      }
      else
      {
        uchar i;
        for (i=0; i<IndexInBuff()-15; i++)
          SetInBuff(i, InBuff(12+i));

        if (Checksum35Sensor() == 0)
        {
          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
          return;
        }
      }
    }
    else if (InBuff(7) == NNCL2_ERROR)
    {
      Clear(); sprintf(szLo+1,"ошибка ? %u",InBuff(8));
      DelayInf();
    }
    else
    {
      Clear(); sprintf(szLo+1,"команда ? %u",InBuff(7));
      DelayInf();
    }

  mpSerial[ibPort] = SER_BADCHECK;
}

#endif
