/*------------------------------------------------------------------------------
CORRECT3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "correct1.h"
#include "correct3.h"


/*
void    ResetCorrect3(void)
{
  boCorrect3 = FALSE;

  bMaxCorrect3 = 3;

  cdwAbsCorrect3 = 0;
  cdwPosCorrect3 = 0;

  memset(&tiPosCorrect3, 0, sizeof(tiPosCorrect3));
  memset(&tiNegCorrect3, 0, sizeof(tiNegCorrect3));

  memset(&mpcwCorrect3, 0, sizeof(mpcwCorrect3));
}


bit     Correct3Allow(void)
{
  return (cdwPosCorrect3 < bMaxCorrect3);
}
*/

bool    Correct3Disabled(void)
{
//  if ((bPortGPS == 0) || (bPortGPS > bPORTS)) return 0;
//  if (boCorrect3 == FALSE) return 0;
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

/*
#ifndef MODBUS

void    OutCorrect3(void)
{
uchar i;

  InitPushCRC();
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  PushChar(((bPortGPS > 0) && (bPortGPS <= bPORTS)) ? boTrue : FALSE);
  PushChar(boCorrect3);
  PushLong(&cdwAbsCorrect3);
  PushLong(&cdwPosCorrect3);
  PushChar(bMaxCorrect3);
  Push(&tiPosCorrect3, sizeof(time));
  Push(&tiNegCorrect3, sizeof(time));
  PushChar(Correct3Disable() ? boTrue : FALSE);
  Push(&mpcwCorrect3, sizeof(mpcwCorrect3));

  Output(100);
}

#endif
*/
