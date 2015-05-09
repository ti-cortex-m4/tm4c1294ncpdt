/*------------------------------------------------------------------------------
OUT_CORRECT,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
#include "../time/rtc.h"
#include "../time/timedate.h"
#include "../time/correct1.h"
#include "../time/correct2.h"
#include "../time/correct3.h"



void    OutCorrect1(void)
{
  if (Correct2Disabled()) { Correct2(EVE_EXT_CORRECT2); Result(bRES_BADACCESS); return; }
  if (Correct3Disabled()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); return; }

  InitPop(6);

  time ti;
  Pop(&ti, sizeof(time));

  if (ValidTimeDate(ti) == true)
  {
    SetCurrTimeDate(ti);
    Result(bRES_OK);
  }
  else Result(bRES_BADDATA);
}



void    OutCorrect2(void)
{
  if (Correct2Disabled()) { Correct2(EVE_EXT_CORRECT2); Result(bRES_BADACCESS); return; }
  if (Correct3Disabled()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); return; }

  InitPop(6);

  time ti;
  Pop(&ti, sizeof(time));

  if (ValidTimeDate(ti) == true)
  {
    if ((tiCurr.bDay   != ti.bDay)   ||
        (tiCurr.bMonth != ti.bMonth) ||
        (tiCurr.bYear  != ti.bYear))
      Result(bRES_BADMODE);
    else if ((tiCurr.bHour*2 + tiCurr.bMinute/30) != (ti.bHour*2 + ti.bMinute/30))
      Result(bRES_BADMODE);
    else
    {
      CorrectTime_Full(ti, EVE_EXT_CORRECT2);
      Result(bRES_OK);
    }
  }
  else Result(bRES_BADDATA);
}



void    OutCorrect20(void)
{
  if (Correct3Disabled()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); return; }

  InitPop(6);

  time ti;
  Pop(&ti, sizeof(time));

  if (ValidTimeDate(ti) == true)
  {
    if ((tiCurr.bDay   != ti.bDay)   ||
        (tiCurr.bMonth != ti.bMonth) ||
        (tiCurr.bYear  != ti.bYear))
      Result(bRES_BADMODE);
    else if ((tiCurr.bHour*2 + tiCurr.bMinute/30) != (ti.bHour*2 + ti.bMinute/30))
      Result(bRES_BADMODE);
    else
    {
      if (Correct2Allowed())
      {
        CorrectTime_Full(ti, EVE_EXT_CORRECT2);
        Result(bRES_OK);
      }
      else Result(bRES_BADACCESS);
    }
  }
  else Result(bRES_BADDATA);
}
