/*------------------------------------------------------------------------------
CORRECT1.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../time/timedate.h"
#include "../time/rtc.h"
#include "correct1.h"



uchar   GetCorrectIndex(event  ev)
{
  switch (ev)
  {
    case EVE_PROGRAM_2:     return(2);
    case EVE_EXT_CORRECT2:  return(3);
    case EVE_ESC_K:         return(4);
    case EVE_ESC_k:         return(5);
    case EVE_INQ_CORRECT1:  return(6);
    case EVE_INQ_CORRECT2:  return(7);
    case EVE_INQ_CORRECT4:  return(8);
    case EVE_UNI_CORRECT:   return(9);

    default: return(0);
  }
}



void    CorrectTime_Full(time  ti, event  ev)
{
//  uchar   i;
//  if ((i = GetCorrectIndex(evCode)) == 0) return;
//
//  AddKeyRecord(evCode);
//  tiPrevCorrect = tiCurr;
//  tiPostCorrect = tiAlt;
//
//
//  tiSetRTC = tiAlt;
//  SetCurrTime();
//  tiPrev = tiAlt;
//
//  AddKeyRecord(EVE_TIME_OK);
//
//
//  tiAlt = tiPostCorrect;
//  dwBuffC = GetSecondIndex();
//
//  tiAlt = tiPrevCorrect;
//  if (dwBuffC > GetSecondIndex())
//  {
//    dwBuffC = dwBuffC - GetSecondIndex();
//
//    mpcwPosValueCurr[0] += (uint)dwBuffC;
//    mpcwPosValueCurr[i] += (uint)dwBuffC;
//    mpcwPosCountCurr[0]++;
//    mpcwPosCountCurr[i]++;
//  }
//  else
//  {
//    dwBuffC = GetSecondIndex() - dwBuffC;
//
//    mpcwNegValueCurr[0] += (uint)dwBuffC;
//    mpcwNegValueCurr[i] += (uint)dwBuffC;
//    mpcwNegCountCurr[0]++;
//    mpcwNegCountCurr[i]++;
//  }
}
