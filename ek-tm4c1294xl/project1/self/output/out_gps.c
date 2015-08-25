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
  Push(mpcwGpsSchedule, sizeof(mpcwGpsSchedule));
  Push(&tiPrevCorrect, sizeof(time));
  Push(&tiPostCorrect, sizeof(time));
  Push(&Correct1.mpwPosValueCurr, sizeof(Correct1.mpwPosValueCurr));
  Push(&Correct1.mpwNegValueCurr, sizeof(Correct1.mpwNegValueCurr));
  Push(&Correct1.mpwPosCountCurr, sizeof(Correct1.mpwPosCountCurr));
  Push(&Correct1.mpwNegCountCurr, sizeof(Correct1.mpwNegCountCurr));
  Push(&Correct1.mpwPosValuePrev, sizeof(Correct1.mpwPosValuePrev));
  Push(&Correct1.mpwNegValuePrev, sizeof(Correct1.mpwNegValuePrev));
  Push(&Correct1.mpwPosCountPrev, sizeof(Correct1.mpwPosCountPrev));
  Push(&Correct1.mpwNegCountPrev, sizeof(Correct1.mpwNegCountPrev));
  PushChar(GetSeasonCurr());
  PushBool(boSeasonGps);
  Output(345+2);
}
