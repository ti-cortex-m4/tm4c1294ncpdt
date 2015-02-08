/*------------------------------------------------------------------------------
 OUT_GAPS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_settings.h"
#include        "../ports.h"
#include        "../rtc.h"
#include        "../flash/files.h"
#include        "../tariffs/gaps.h"



void    OutGaps1(void)
{
  InitPushCRC();
  PushChar(boGapsFlag);
  Push(&gaGaps, sizeof(gaps));
  Output(1+sizeof(gaps));
}


void    OutGaps2(void)
{
  if (enGlobal == GLB_PROGRAM) MakeGaps();

  InitPushCRC();
  PushChar(boGapsFlag);
  Push(PGetCurrTimeDate(), sizeof(time));
  PushChar(mpbGaps[GetDayIndex_Alt()]);
  Push(&mpbGaps, sizeof(gaps));
  Output(1+sizeof(time)+1+sizeof(gaps));
}
