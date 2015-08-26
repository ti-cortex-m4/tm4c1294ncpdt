/*------------------------------------------------------------------------------
CORRECT3.C

 ('Отчет № 49 от 07.09.2009')
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../time/gps.h"
#include "correct1.h"
#include "correct3.h"



cache const             chCorrect3Flag = {CORRECT3_FLAG, &boCorrect3Flag, sizeof(bool)};
cache const             chCorrect3SuccessMax = {CORRECT3_SUCCESS_MAX, &bCorrect3SuccessMax, sizeof(uchar)};

cache const             chCorrect3Total = {CORRECT3_TOTAL, &dwCorrect3Total, sizeof(ulong)};
cache const             chCorrect3Success = {CORRECT3_SUCCESS, &dwCorrect3Success, sizeof(ulong)};

cache const             chCorrect3SuccessTime = {CORRECT3_SUCCESS_TIME, &tiCorrect3Sucess, sizeof(time)};
cache const             chCorrect3ErrorTime = {CORRECT3_ERROR_TIME, &tiCorrect3ErrorTime, sizeof(time)};

cache const             chCorrect3Status15 = {CORRECT3_STATUS, &mpcwCorrect3Status15, sizeof(mpcwCorrect3Status15)};



void    InitCorrect3(void)
{
  LoadCacheBool(&chCorrect3Flag,false);
  LoadCacheChar(&chCorrect3SuccessMax, 1, 100, 3);

  LoadCache(&chCorrect3Total);
  LoadCache(&chCorrect3Success);

  LoadCache(&chCorrect3SuccessTime);
  LoadCache(&chCorrect3ErrorTime);

  LoadCache(&chCorrect3Status15);
}


void    ResetCorrect3(void)
{
  boCorrect3Flag = false;
  SaveCache(&chCorrect3Flag);

  bCorrect3SuccessMax = 3;
  SaveCache(&chCorrect3SuccessMax);

  dwCorrect3Total = 0;
  SaveCache(&chCorrect3Total);

  dwCorrect3Success = 0;
  SaveCache(&chCorrect3Success);

  tiCorrect3Sucess = tiZero;
  SaveCache(&chCorrect3SuccessTime);

  tiCorrect3ErrorTime = tiZero;
  SaveCache(&chCorrect3ErrorTime);

  memset(&mpcwCorrect3Status15, 0, sizeof(mpcwCorrect3Status15));
  SaveCache(&chCorrect3Status15);
}



bool    Correct3Allowed(void)
{
  return (dwCorrect3Success < bCorrect3SuccessMax);
}


bool    Correct3Disabled(void)
{
  if (UseGps() == false) return false;
  if (boCorrect3Flag == false) return false;

  return (Correct3Allowed() == false);
}


void    Correct3(event  ev)
{
  uchar i;
  if ((i = GetCorrectIndex(ev)) == 0) return;

  mpcwCorrect3Status15[0]++;
  mpcwCorrect3Status15[i]++;

  SaveCache(&chCorrect3Status15);
}



void    OutCorrect3(void)
{
  InitPushCRC();

  uchar i;
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  PushBool(UseGps());
  PushBool(boCorrect3Flag);
  PushLong(dwCorrect3Total);
  PushLong(dwCorrect3Success);
  PushChar(bCorrect3SuccessMax);
  PushTime(tiCorrect3Sucess);
  PushTime(tiCorrect3ErrorTime);
  PushBool(Correct3Disabled());
  PushIntArray(mpcwCorrect3Status15, 15);

  Output(100);
}
