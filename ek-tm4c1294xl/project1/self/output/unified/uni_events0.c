/*------------------------------------------------------------------------------
UNI_EVENTS0,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_records.h"
#include "../../memory/mem_flash.h"
#include "../../serial/monitor.h"
#include "../../flash/records.h"
#include "../../flash/records2.h"
#include "../../hardware/watchdog.h"
#include "uni_events0.h"



uint    GetPagesCount(uchar  ibClass)
{
  ASSERT((ibClass >= 1) && (ibClass <= 3));

  if (ibClass == 1)
    return bRECORD_PAGES;
  else if (ibClass == 2)
    return wRECORD2_PAGES;
  else
    return bRECORD_PAGES;
}


uint    GetMaxRecordsCount(uchar  ibClass)
{
  ASSERT((ibClass >= 1) && (ibClass <= 3));

  if (ibClass == 1)
    return wRECORDS;
  else if (ibClass == 2)
    return wRECORDS2;
  else
    return wRECORDS;
}


uint    GetRecordsCount(uchar  ibClass)
{
  ASSERT((ibClass >= 1) && (ibClass <= 3));

  if (ibClass == 1)
    return (cdwSysRecord < wRECORDS) ? cdwSysRecord : wRECORDS;
  else if (ibClass == 2)
    return (cdwAuxRecord < wRECORDS2) ? cdwAuxRecord : wRECORDS2;
  else
    return (cdwImpRecord < wRECORDS) ? cdwImpRecord : wRECORDS;
}


void    LoadEventsPage(uchar  ibClass, uint  iwPage)
{
  ASSERT((ibClass >= 1) && (ibClass <= 3));

  MonitorString("\n\n page "); MonitorIntDec(iwPage);
  MonitorString(" class "); MonitorCharDec(ibClass);

  ResetWatchdog();

  if (ibClass == 1)
    GetRecordsBlock(CLA_SYSTEM, iwPage);
  else if (ibClass == 2)
    GetRecordsBlock2(CLA_AUXILIARY, iwPage);
  else
    GetRecordsBlock(CLA_IMPULSE, iwPage);

  MonitorString("\n");
  uint i;
  for (i=0; i<wLEAF_BYTES; i++)
  {
    if (i % SIZEOF_RECORD == 0) { MonitorString("\n"); MonitorCharDec(i / SIZEOF_RECORD); }
    MonitorCharHex(mpbPageIn[i]);
  }
  MonitorString("\n");
}


time    ReadEventBlock(uchar  ibBlock) // 1 .. bRECORD_BLOCK
{
  BuffToRecord((uchar *) &mpbPageIn + ((ibBlock-1) % bRECORD_BLOCK)*SIZEOF_RECORD);

  MonitorString("\n block "); MonitorCharDec(ibBlock-1);
  MonitorIntDec(reCurr.cdwRecord);
  MonitorCharDec(reCurr.ev);
	MonitorTime(reCurr.ti);

  return reCurr.ti;
}
