/*------------------------------------------------------------------------------
 OUT_GAPS!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_tariffs.h"
#include "../memory/mem_settings.h"
#include "../serial/ports.h"
#include "../time/timedate.h"
#include "../time/rtc.h"
#include "../flash/files.h"
#include "../tariffs/gaps.h"



void    OutGaps1(void)
{
  InitPushCRC();
  PushBool(boGapsFlag);
  Push(&gaGaps, sizeof(gaGaps));
  Output(1+sizeof(gaGaps));
}


void    OutGaps2(void)
{
time  ti;

  if (enGlobal == GLB_PROGRAM)
  	MakeGaps();

  InitPushCRC();
  PushBool(boGapsFlag);
  ti = *GetCurrTimeDate();
  Push(&ti, sizeof(time));
  PushChar(mpbGaps[GetDayIndexMD(ti.bMonth, ti.bDay)]);
  Push(&mpbGaps, sizeof(gaGaps));
  Output(1+sizeof(time)+1+sizeof(gaGaps));
}
