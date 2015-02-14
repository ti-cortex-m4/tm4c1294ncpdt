/*------------------------------------------------------------------------------
REALTIME_SPEC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../rtc.h"




// базовая программа обработки переходов времени
void    ProcessTimeMntSpec(void)
{
  // переход на следующие три минуты
  if ((tiCurr.bMinute % 3 == 0) && (tiPrev.bMinute % 3 != 0))
  {
    ProcessNextMntSpec();
    fCurrent = 1;
  }

  // переход на следующие тридцать минут
  if ((tiCurr.bMinute % 30 == 0) && (tiPrev.bMinute % 30 != 0))
  {
    ProcessNextHouSpec();
    bHouInc++;
  }
}


// программа обработки переходов в реальном времени
void    NexttimeMntSpec(void)
{
time  ti;

  ResetWDT();
  if (GetLabelRTC() == 0) return;

  ti = *GetCurrTimeDate();
  if (TrueCurrTimeDate(&ti) == 0) return;

  if (tiCurr.bSecond != ti.bSecond)
  {
    // чтение текущего времени
    tiCurr = ti;

    if (enGlobal != GLB_PROGRAM)
      ProcessTimeMntSpec();

    // запись прошедшего времени
    tiPrev = tiCurr;
  }
}

