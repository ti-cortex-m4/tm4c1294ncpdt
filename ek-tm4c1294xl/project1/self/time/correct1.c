/*------------------------------------------------------------------------------
CORRECT1,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_gps.h"
#include "../memory/mem_correct1.h"
#include "../memory/mem_records.h"
#include "../time/timedate.h"
#include "../time/rtc.h"
#include "../nvram/cache.h"
#include "../flash/records.h"
#include "correct1.h"



cache const             chCorrect1 = {CORRECT1, &Correct1, sizeof(Correct1)};



void    InitCorrect1(void)
{
  LoadCache(&chCorrect1);
}


void    ResetCorrect1(void)
{
  memset(&Correct1, 0, sizeof(Correct1));
  SaveCache(&chCorrect1);
}



void    NextMonCorrect1(void)
{
  memcpy(&Correct1.mpwPosValuePrev, &Correct1.mpwPosValueCurr, sizeof(Correct1.mpwPosValuePrev));
  memcpy(&Correct1.mpwNegValuePrev, &Correct1.mpwNegValueCurr, sizeof(Correct1.mpwNegValuePrev));
  memcpy(&Correct1.mpwPosCountPrev, &Correct1.mpwPosCountCurr, sizeof(Correct1.mpwPosCountPrev));
  memcpy(&Correct1.mpwNegCountPrev, &Correct1.mpwNegCountCurr, sizeof(Correct1.mpwNegCountPrev));

  memset(&Correct1.mpwPosValueCurr, 0, sizeof(Correct1.mpwPosValueCurr));
  memset(&Correct1.mpwNegValueCurr, 0, sizeof(Correct1.mpwNegValueCurr));
  memset(&Correct1.mpwPosCountCurr, 0, sizeof(Correct1.mpwPosCountCurr));
  memset(&Correct1.mpwNegCountCurr, 0, sizeof(Correct1.mpwNegCountCurr));

  SaveCache(&chCorrect1);
}



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
void    SetCurrTime_Full(time  ti, event  ev)
{
  uchar i;
  if ((i = GetCorrectIndex(ev)) == 0) return;


  tiRecordTime = ti;
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

  SaveCache(&chCorrect1);
}


// коррекция секунд текущего времени
bool    CorrectTime_Full(event  ev)
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

  SaveCache(&chCorrect1);

  tiRecordTime = ti;
  AddKeyRecord(ev);
  SetCurrTime(ti);
  AddKeyRecord(EVE_TIME_OK);

  return true;
}

