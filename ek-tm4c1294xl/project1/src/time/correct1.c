/*------------------------------------------------------------------------------
CORRECT1.C

TODO persist
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



// установка текущего времени
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

    Correct1.mpwPosValueCurr[0] += w;
    Correct1.mpwPosValueCurr[i] += w;
    Correct1.mpwPosCountCurr[0]++;
    Correct1.mpwPosCountCurr[i]++;
  }
  else
  {
    uint w = dw1 - dw2;

    Correct1.mpwNegValueCurr[0] += w;
    Correct1.mpwNegValueCurr[i] += w;
    Correct1.mpwNegCountCurr[0]++;
    Correct1.mpwNegCountCurr[i]++;
  }
}


// коррекция секунд текущего времени
bool    CorrectTime(event  ev)
{
  uchar i;
  if ((i = GetCorrectIndex(ev)) == 0) return(0);


  time ti = *GetCurrTimeDate();

  if (ti.bSecond < 30)
  {
    if (Correct1.mpwNegValueCurr[i] + ti.bSecond > wMAXCORRECT)
      return false;
    else
    {
      Correct1.mpwNegValueCurr[0] += ti.bSecond;
      Correct1.mpwNegValueCurr[i] += ti.bSecond;
      Correct1.mpwNegCountCurr[0]++;
      Correct1.mpwNegCountCurr[i]++;

      ti.bSecond = 0;
    }
  }
  else
  {
    if (Correct1.mpwPosValueCurr[i] + ti.bSecond > wMAXCORRECT)
      return false;
    else
    {
      Correct1.mpwPosValueCurr[0] += 60 - ti.bSecond;
      Correct1.mpwPosValueCurr[i] += 60 - ti.bSecond;
      Correct1.mpwPosCountCurr[0]++;
      Correct1.mpwPosCountCurr[i]++;

      ti.bSecond = 0;
      if (++ti.bMinute >= 60)
      {
        ti.bMinute = 0;
        if (++ti.bHour >= 24)
        {
          ti.bHour = 0;
          if (++ti.bDay > GetDaysInMonthYM(ti.bYear, ti.bMonth))
          {
            ti.bDay = 1;
            if (++ti.bMonth > 12)
            {
              ti.bMonth = 1;
              ti.bYear++;
            }
          }
        }
      }
    }
  }

  AddKeyRecord(ev);
  SetCurrTime(ti);
  AddKeyRecord(EVE_TIME_OK);

  return true;
}

