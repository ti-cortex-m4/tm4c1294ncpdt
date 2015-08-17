/*------------------------------------------------------------------------------
UNI_EVENTS0,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_records.h"
#include "../../memory/mem_flash.h"
#include "../../serial/print2.h"
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

  x_str("\n\n page"); x_intdec(iwPage);

  ResetWatchdog();

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
  BuffToRecord((uchar *) &mpbPageIn + ((ibBlock-1) % bRECORD_BLOCK)*SIZEOF_RECORD);

  x_str("\n block"); x_bytedec(ibBlock-1);
  x_intdec(reCurr.cdwRecord);
  x_bytedec(reCurr.ev);
  if (reCurr.ev != 0xFF) x_time(reCurr.ti);

  return reCurr.ti;
}
