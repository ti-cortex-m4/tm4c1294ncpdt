/*------------------------------------------------------------------------------
 OUT_GAPS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_settings.h"
#include        "../ports.h"
#include        "../timedate.h"
#include        "../rtc.h"
#include        "../flash/files.h"
#include        "../tariffs/gaps.h"



void    OutGaps1(void)
{
  InitPushCRC();
  PushChar(boGapsFlag);
  Push(&gaGaps, sizeof(gaGaps));
  Output(1+sizeof(gaGaps));
}


void    OutGaps2(void)
{
time  ti;

  if (enGlobal == GLB_PROGRAM)
  	MakeGaps();

  InitPushCRC();
  PushChar(boGapsFlag);
  ti = *PGetCurrTimeDate();
  Push(&ti, sizeof(time));
  PushChar(mpbGaps[GetDayIndexMonthDay(ti.bMonth, ti.bDay)]);
  Push(&mpbGaps, sizeof(gaGaps));
  Output(1+sizeof(time)+1+sizeof(gaGaps));
}
