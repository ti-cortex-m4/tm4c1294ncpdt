/*------------------------------------------------------------------------------
REALTIME_SPEC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "../time/rtc.h"
#include "../hardware/watchdog.h"
#include "realtime.h"
#include "next_minute3.h"
#include "next_minute30.h"
#include "realtime_spec.h"



static void ProcessTimeMnt(void)
{
  // переход на следующие три минуты
  if ((tiCurr.bMinute % 3 == 0) && (tiPrev.bMinute % 3 != 0))
  {
  	NextMinute3();
    fCurrent = 1;
  }

  // переход на следующие тридцать минут
  if ((tiCurr.bMinute % 30 == 0) && (tiPrev.bMinute % 30 != 0))
  {
  	NextMinute30();
    bHouInc++;
  }
}


void    NexttimeMnt(void)
{
  ResetWDT();
  // TODO if (GetLabelRTC() == 0) return;

  time tiT = *GetCurrTimeDate();
  if (TrueCurrTimeDate(tiT) == 0) return;

  if (tiCurr.bSecond != tiT.bSecond)
  {
    tiCurr = tiT;

    if (enGlobal != GLB_PROGRAM)
      ProcessTimeMnt();

    tiPrev = tiCurr;
  }
}
