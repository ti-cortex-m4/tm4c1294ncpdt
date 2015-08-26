/*------------------------------------------------------------------------------
CORRECT3.C

 ('Отчет № 49 от 07.09.2009')
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_correct3.h"
#include "../memory/mem_gps.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "../time/gps.h"
#include "correct1.h"
#include "correct3.h"



cache const             chCorrect3Flag = {CORRECT3_FLAG, &boCorrect3Flag, sizeof(bool)};



void    InitCorrect3(void)
{
  LoadCache(&chCorrect3Flag);
}


void    ResetCorrect3(void)
{
  boCorrect3Flag = false;
  SaveCache(&chCorrect3Flag);

  bMaxCorrect3 = 3;

  cdwAbsCorrect3 = 0;
  cdwPosCorrect3 = 0;

  memset(&tiPosCorrect3, 0, sizeof(tiPosCorrect3));
  memset(&tiNegCorrect3, 0, sizeof(tiNegCorrect3));

  memset(&mpcwCorrect3, 0, sizeof(mpcwCorrect3));
}

/*
bit     Correct3Allow(void)
{
  return (cdwPosCorrect3 < bMaxCorrect3);
}
*/

bool    Correct3Disabled(void)
{
//  if ((bPortGPS == 0) || (bPortGPS > bPORTS)) return 0;
//  if (boCorrect3 == false) return 0;
//
//  return !Correct3Allow();
  return false;
}


void    Correct3(event  ev)
{
//  uchar i;
//  if ((i = GetCorrectIndex(ev)) == 0) return;
//
//  mpcwCorrect3[0]++;
//  mpcwCorrect3[i]++;
}



void    OutCorrect3(void)
{
  InitPushCRC();

  uchar i;
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  PushChar(UseGps() ? true : false); // TODO
  PushBool(boCorrect3Flag);
  PushLong(cdwAbsCorrect3);
  PushLong(cdwPosCorrect3);
  PushChar(bMaxCorrect3);
  Push(&tiPosCorrect3, sizeof(time));
  Push(&tiNegCorrect3, sizeof(time));
  PushChar(Correct3Disabled() ? true : false);
  Push(&mpcwCorrect3, sizeof(mpcwCorrect3)); // TODO

  Output(100);
}
