/*------------------------------------------------------------------------------
OUT_GPS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_correct1.h"
#include "../serial/ports.h"
#include "../time/decret.h"
#include "../time/gps.h"
#include "out_gps.h"



void    OutGetGps(void)
{
  InitPushCRC();
  PushChar(bPortGps);
  PushChar(bStatusGps);
  PushChar(bVersionMaxGps);
  PushChar(bVersionMinGps);
  PushChar(bGmtGps);
  Push(mpboScheduleGps, sizeof(mpboScheduleGps));
  PushIntArray(mpcwGpsStatus, 15);
  PushTime(tiPrevCorrect);
  PushTime(tiPostCorrect);
  PushIntArray(Correct1.mpwPosValueCurr, 15);
  PushIntArray(Correct1.mpwNegValueCurr, 15);
  PushIntArray(Correct1.mpwPosCountCurr, 15);
  PushIntArray(Correct1.mpwNegCountCurr, 15);
  PushIntArray(Correct1.mpwPosValuePrev, 15);
  PushIntArray(Correct1.mpwNegValuePrev, 15);
  PushIntArray(Correct1.mpwPosCountPrev, 15);
  PushIntArray(Correct1.mpwNegCountPrev, 15);
  PushChar(GetSeasonCurr());
  PushBool(boSeasonGps);
  Output(345+2);
}
