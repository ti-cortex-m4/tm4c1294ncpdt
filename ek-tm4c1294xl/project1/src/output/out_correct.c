/*------------------------------------------------------------------------------
OUT_CORRECT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "../flash/files.h"


/*
void    OutCorrect1(void)
{
    if (Correct2Disable()) { Correct2(EVE_EXT_CORRECT2); Result(bRES_BADACCESS); break; }
    if (Correct3Disable()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); break; }

    InitPop(6);
    Pop(&tiAlt, sizeof(time));

    if (TrueTimeDate() == 1)
    {
      tiSetRTC = tiAlt;
      SetCurrTimeDate();

      Result(bRES_OK);
    }
    else Result(bRES_BADDATA);
}



void    OutCorrect2(void)
{
    if (Correct2Disable()) { Correct2(EVE_EXT_CORRECT2); Result(bRES_BADACCESS); break; }
    if (Correct3Disable()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); break; }

    InitPop(6);
    Pop(&tiAlt, sizeof(time));

    if (TrueTimeDate() == 1)
    {
      if ((tiCurr.bDay   != tiAlt.bDay)   ||
          (tiCurr.bMonth != tiAlt.bMonth) ||
          (tiCurr.bYear  != tiAlt.bYear))
        Result(bRES_BADMODE);
      else
      if (GetHouIndex() != (tiAlt.bHour*2 + tiAlt.bMinute/30))
        Result(bRES_BADMODE);
      else
      { / *
        tiSetRTC = tiAlt;
        SetCurrTime();
        tiPrev = tiAlt;
        * /
        CorrectTime_Full(EVE_EXT_CORRECT2);

        Result(bRES_OK);
      }
    }
    else Result(bRES_BADDATA);
}



void    OutCorrect20(void)
{
    if (Correct3Disable()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); break; }

    InitPop(6);
    Pop(&tiAlt, sizeof(time));

    if (TrueTimeDate() == 1)
    {
      if ((tiCurr.bDay   != tiAlt.bDay)   ||
          (tiCurr.bMonth != tiAlt.bMonth) ||
          (tiCurr.bYear  != tiAlt.bYear))
        Result(bRES_BADMODE);
      else
      if (GetHouIndex() != (tiAlt.bHour*2 + tiAlt.bMinute/30))
        Result(bRES_BADMODE);
      else
      {
        if (Correct2Allow())
        {
          CorrectTime_Full(EVE_EXT_CORRECT2);
          Result(bRES_OK);
        }
        else Result(bRES_BADACCESS);
      }
    }
    else Result(bRES_BADDATA);
}
*/
