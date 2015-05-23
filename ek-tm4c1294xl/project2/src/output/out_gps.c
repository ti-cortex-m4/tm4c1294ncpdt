/*------------------------------------------------------------------------------
OUT_GPS.C


------------------------------------------------------------------------------*/
/*
#include "../main.h"



void    OutCorrect1(void)
{
  InitPushCRC();
  PushChar(bPortGPS);
  PushChar(bStatusGPS);
  PushChar(bVersionMaxGPS);
  PushChar(bVersionMinGPS);
  PushChar(bGMT);
  Push(mpboGPSRun, sizeof(mpboGPSRun));
  Push(mpcwGPSRun, sizeof(mpcwGPSRun));
  Push(&tiPrevCorrect, sizeof(time));
  Push(&tiPostCorrect, sizeof(time));
  Push(&mpcwPosValueCurr, sizeof(mpcwPosValueCurr));
  Push(&mpcwNegValueCurr, sizeof(mpcwNegValueCurr));
  Push(&mpcwPosCountCurr, sizeof(mpcwPosCountCurr));
  Push(&mpcwNegCountCurr, sizeof(mpcwNegCountCurr));
  Push(&mpcwPosValuePrev, sizeof(mpcwPosValuePrev));
  Push(&mpcwNegValuePrev, sizeof(mpcwNegValuePrev));
  Push(&mpcwPosCountPrev, sizeof(mpcwPosCountPrev));
  Push(&mpcwNegCountPrev, sizeof(mpcwNegCountPrev));
  PushChar(SeasonCurr());
  PushChar(boSeasonGPS);
  Output(345+2);
}



void    OutCorrect2(void)
{
  InitPushCRC();
  PushChar(bPortSMK);
  Push(mpboSMKRun, sizeof(mpboSMKRun));
  Push(mpcwSMKRun, sizeof(mpcwSMKRun));
  Push(&tiPrevCorrect, sizeof(time));
  Push(&tiPostCorrect, sizeof(time));
  Output(101);
}
*/
