/*------------------------------------------------------------------------------
CTRL_HOURS!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_schedule.h"
#include "../../realtime/realtime.h"



// разрешение коррекции часов цифровых счётчиков
bool    ControlTime(void)
{
  if ((tiCurr.bHour == 2) || (tiCurr.bHour == 3))
  {
    if ((tiCurr.bDay   == tiSummer.bDay)   &&
        (tiCurr.bMonth == tiSummer.bMonth)) return(0);

    if ((tiCurr.bDay   == tiWinter.bDay)   &&
        (tiCurr.bMonth == tiWinter.bMonth)) return(0);
  }

  return( mpboCtrlHou[ GetCurrHouIndex() ] );
}
