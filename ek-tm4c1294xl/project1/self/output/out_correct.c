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
#include "out_correct.h"



void    OutCorrect1(void)
{
  if (Correct2Disable()) { Correct2(EVE_INQ_CORRECT1); LongResult(bRES_BADACCESS); }
  if (Correct3Disable()) { Correct3(EVE_INQ_CORRECT1); LongResult(bRES_BADCORRECTION); }

  if (CorrectTime(EVE_INQ_CORRECT1) == 1)
    LongResult(bRES_OK);
  else
    LongResult(bRES_BADMODE);
}


void    OutCorrect2(void)
{
  if (Correct2Disable()) { Correct2(EVE_INQ_CORRECT2); LongResult(bRES_BADACCESS); }
  if (Correct3Disable()) { Correct3(EVE_INQ_CORRECT2); LongResult(bRES_BADCORRECTION); }

  CorrectTime(EVE_INQ_CORRECT2);
}


void    OutCorrect3(void)
{
  InitPushCRC();
  PushInt(mpcwPosValueCurr[0]);
  PushInt(mpcwNegValueCurr[0]);
  Output(4);
}

/*
void    OutCorrect4(void)
{
        if (Correct2Disable()) { Correct2(EVE_INQ_CORRECT4); LongResult(bRES_BADACCESS); break; }
        if (Correct3Disable()) { Correct3(EVE_INQ_CORRECT4); LongResult(bRES_BADCORRECTION); break; }

        tiAlt.bSecond = bInBuff5;
        tiAlt.bMinute = bInBuff6;
        tiAlt.bHour   = bInBuff7;

        dwBuffC = GetSecondIndex();

        tiAlt.bSecond = tiCurr.bSecond;
        tiAlt.bMinute = tiCurr.bMinute;
        tiAlt.bHour   = tiCurr.bHour;

        if (dwBuffC > GetSecondIndex())
        {
          dwBuffC = dwBuffC - GetSecondIndex();

          if (dwBuffC < wMAXCORRECT)
          {
            tiSetRTC.bSecond = bInBuff5;
            tiSetRTC.bMinute = bInBuff6;
            tiSetRTC.bHour   = bInBuff7;

            AddKeyRecord(EVE_INQ_CORRECT4);
            SetCurrTime();
            AddKeyRecord(EVE_TIME_OK);

            i = GetCorrectIndex(EVE_INQ_CORRECT4);

            mpcwNegValueCurr[0] += (uint)dwBuffC;
            mpcwNegValueCurr[i] += (uint)dwBuffC;
            mpcwNegCountCurr[0]++;
            mpcwNegCountCurr[i]++;

            LongResult(bRES_OK);
          }
          else LongResult(bRES_BADDATA);
        }
        else
        {
          dwBuffC = GetSecondIndex() - dwBuffC;

          if (dwBuffC < wMAXCORRECT)
          {
            tiSetRTC.bSecond = bInBuff5;
            tiSetRTC.bMinute = bInBuff6;
            tiSetRTC.bHour   = bInBuff7;

            AddKeyRecord(EVE_INQ_CORRECT4);
            SetCurrTime();

            i = GetCorrectIndex(EVE_INQ_CORRECT4);

            mpcwPosValueCurr[0] += (uint)dwBuffC;
            mpcwPosValueCurr[i] += (uint)dwBuffC;
            mpcwPosCountCurr[0]++;
            mpcwPosCountCurr[i]++;

            LongResult(bRES_OK);
          }
          else LongResult(bRES_BADDATA);
        }
}
*/


void    OutCorrectExt1(void)
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



void    OutCorrectExt2(void)
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
      SetCurrTime_Full(ti, EVE_EXT_CORRECT2);
      Result(bRES_OK);
    }
  }
  else Result(bRES_BADDATA);
}



void    OutCorrectExt20(void)
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
        SetCurrTime_Full(ti, EVE_EXT_CORRECT2);
        Result(bRES_OK);
      }
      else Result(bRES_BADACCESS);
    }
  }
  else Result(bRES_BADDATA);
}
