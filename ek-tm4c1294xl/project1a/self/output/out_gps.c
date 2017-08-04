/*------------------------------------------------------------------------------
OUT_GPS!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_correct1.h"
#include "../serial/ports.h"
#include "../time/decret.h"
#include "../time/gps.h"
#include "out_gps.h"



void    OutCorrectGps(void)
{
  InitPushCRC();
  PushChar(bPortGps);
  PushChar(bStatusGps);
  PushChar(bVersionMaxGps);
  PushChar(bVersionMinGps);
  PushChar(bGmtGps);
  Push(mpboScheduleGps, sizeof(mpboScheduleGps));
  PushIntBigArray(mpcwGpsStatus20, 20);
  PushTime(tiPrevCorrect);
  PushTime(tiPostCorrect);
  PushIntBigArray(Correct1.mpwPosValueCurr, 15);
  PushIntBigArray(Correct1.mpwNegValueCurr, 15);
  PushIntBigArray(Correct1.mpwPosCountCurr, 15);
  PushIntBigArray(Correct1.mpwNegCountCurr, 15);
  PushIntBigArray(Correct1.mpwPosValuePrev, 15);
  PushIntBigArray(Correct1.mpwNegValuePrev, 15);
  PushIntBigArray(Correct1.mpwPosCountPrev, 15);
  PushIntBigArray(Correct1.mpwNegCountPrev, 15);
  PushChar(GetSeasonCurr());
  PushBool(boSeasonGps);
  Output(345+2);
}
