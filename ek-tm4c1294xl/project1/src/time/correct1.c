/*------------------------------------------------------------------------------
CORRECT1.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_gps.h"
#include "../memory/mem_correct1.h"
#include "../time/timedate.h"
#include "../time/rtc.h"
#include "../flash/records.h"
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
  uchar i;
  if ((i = GetCorrectIndex(ev)) == 0) return;

  AddKeyRecord(ev);
  tiPrevCorrect = tiCurr;
  tiPostCorrect = ti;


  SetCurrTime(ti);
  tiPrev = ti;

  AddKeyRecord(EVE_TIME_OK);


  ulong dw1 = GetSecondIndex(tiPrevCorrect);
  ulong dw2 = GetSecondIndex(tiPostCorrect);

  if (dw2 > dw1)
  {
    uint w = dw2 - dw1;

    mpcwPosValueCurr[0] += w;
    mpcwPosValueCurr[i] += w;
    mpcwPosCountCurr[0]++;
    mpcwPosCountCurr[i]++;
  }
  else
  {
  	uint w = dw1 - dw2;

    mpcwNegValueCurr[0] += w;
    mpcwNegValueCurr[i] += w;
    mpcwNegCountCurr[0]++;
    mpcwNegCountCurr[i]++;
  }
}
