/*------------------------------------------------------------------------------
UNI_EVENTS0.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_records.h"
#include "../../memory/mem_flash.h"
#include "../../include/flash.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/print2.h"
#include "../../flash/records.h"
#include "../../flash/records2.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/rtc.h"
#include "../../hardware/watchdog.h"
#include "response_uni.h"
#include "uni_events0.h"



uint    GetPagesCount(uchar  ibClass)
{
  if (ibClass == 1)
    return bRECORD_PAGES;
  else if (ibClass == 2) 
    return wRECORD2_PAGES;
  else
    return bRECORD_PAGES;
}


uint    GetMaxRecordsCount(uchar  ibClass)
{
  if (ibClass == 1)
    return wRECORDS;
  else if (ibClass == 2) 
    return wRECORDS2;
  else
    return wRECORDS;
}


uint    GetRecordsCount(uchar  ibClass)
{
  if (ibClass == 1)
    return (cdwSysRecord < wRECORDS) ? cdwSysRecord : wRECORDS;
  else if (ibClass == 2) 
    return (cdwAuxRecord < wRECORDS2) ? cdwAuxRecord : wRECORDS2;
  else
    return (cdwImpRecord < wRECORDS) ? cdwImpRecord : wRECORDS;
}


void    LoadEventsPage(uchar  ibClass, uint  iwPage)
{
  x_str("\n\n page"); x_intdec(iwPage);
  ResetWDT();

  if (ibClass == 1)
    GetRecordsBlock(CLA_SYSTEM, iwPage);
  else if (ibClass == 2) 
    GetRecordsBlock2(CLA_AUXILIARY, iwPage);
  else
    GetRecordsBlock(CLA_IMPULSE, iwPage);

  x_str("\n");
  uint i;
  for (i=0; i<wLEAF_BYTES; i++)
  {
    if (i % SIZEOF_RECORD == 0) { x_str("\n"); x_bytedec(i / SIZEOF_RECORD); }
    x_bytehex(mpbPageIn[i]);
  }
  x_str("\n");
}


time    ReadEventBlock(uchar  ibBlock) // 1 .. bRECORD_BLOCK
{
  uchar* pBuff = (uchar *) &mpbPageIn + ((ibBlock-1) % bRECORD_BLOCK)*SIZEOF_RECORD;
  BuffToRecord(pBuff);

  x_str("\n block"); x_bytedec(ibBlock-1);
  x_intdec(reCurr.cdwRecord);
  x_bytedec(reCurr.ev);
  if (reCurr.ev != 0xFF) x_time(reCurr.ti);

  return reCurr.ti;
}
