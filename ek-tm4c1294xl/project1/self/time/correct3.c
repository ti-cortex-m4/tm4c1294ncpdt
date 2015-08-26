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
cache const             chCorrect3Max = {CORRECT3_MAX, &bCorrect3Max, sizeof(uchar)};



void    InitCorrect3(void)
{
  LoadCacheBool(&chCorrect3Flag,false);
  LoadCacheChar(&chCorrect3Max,1,100,3);
}


void    ResetCorrect3(void)
{
  boCorrect3Flag = false;
  SaveCache(&chCorrect3Flag);

  bCorrect3Max = 3;
  SaveCache(&chCorrect3Max);

  cdwAbsCorrect3 = 0;
  cdwPosCorrect3 = 0;

  memset(&tiPosCorrect3, 0, sizeof(tiPosCorrect3));
  memset(&tiNegCorrect3, 0, sizeof(tiNegCorrect3));

  memset(&mpcwCorrect3, 0, sizeof(mpcwCorrect3));
}

/*
bit     Correct3Allowed(void)
{
  return (cdwPosCorrect3 < bCorrect3Max);
}
*/

bool    Correct3Disabled(void)
{
//  if ((bPortGPS == 0) || (bPortGPS > bPORTS)) return 0;
//  if (boCorrect3 == false) return 0;
//
//  return !Correct3Allowed();
  return false;
}


void    Correct3(event  ev)
{
  uchar i;
  if ((i = GetCorrectIndex(ev)) == 0) return;

  mpcwCorrect3[0]++;
  mpcwCorrect3[i]++;
}



void    OutCorrect3(void)
{
  InitPushCRC();

  uchar i;
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  PushBool(UseGps());
  PushBool(boCorrect3Flag);
  PushLong(cdwAbsCorrect3);
  PushLong(cdwPosCorrect3);
  PushChar(bCorrect3Max);
  PushTime(tiPosCorrect3);
  PushTime(tiNegCorrect3);
  PushBool(Correct3Disabled());
  Push(&mpcwCorrect3, sizeof(mpcwCorrect3)); // TODO

  Output(100);
}
