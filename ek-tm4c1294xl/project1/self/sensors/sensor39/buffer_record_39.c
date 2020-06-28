/*------------------------------------------------------------------------------
buffer_record_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "include39.h"
#include "error39.h"
#include "buffer_array_39.h"
#include "buffer_profile_39.h"
#include "buffer_record_39.h"



static profile39    PrfFirstPrev, PrfFirstCurr;



void    InitRecord39_FragmentProfile39(void) {
  memset(&PrfFirstPrev, 0, sizeof(PrfFirstPrev));
  memset(&PrfFirstCurr, 0, sizeof(PrfFirstCurr));
}


void    InitRecord39(void) {
  InitPush39();
}



void    AddRecord39(uint  iwStart) {
  if (IsPushOverflow39()) {
    Error39(130+0);
    return;
  }

  uint cwSize = IndexInBuff()-iwStart-3;

#ifdef BUFFER_RECORD_39
  MonitorArray39();

  MonitorString("\n AddToBuffer: start="); MonitorIntDec(iwStart);
  MonitorString("\n");
#endif

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    uchar b = PopChar();

#ifdef BUFFER_RECORD_39
    MonitorCharHex(b);
    if (i % 16 == 16-1) MonitorString("\n");
#endif

    PushChar39(b);
  }

#ifdef BUFFER_RECORD_39
  MonitorString("\n");
#endif
}



record39 GetRecordError39(char  bError)
{
  record39 r;

  r.bError = bError;
  r.ddwValue = 0;
  r.tmValue = tiZero;
  r.fFirst = false;

  return r;
}



static record39 Fault(uchar  bError)
{
  return GetRecordError39(Error39(bError));
}



record39 FinishRecord39(void) {
  record39 r = GetRecordError39(0);


  InitPop39();

  if (GetPopCapacity39() < 2)
    return Fault(130+1);

  if (PopChar39() != 1) // array
    return Fault(130+2);

  uchar bCount = PopChar39();

#ifdef BUFFER_RECORD_39
  MonitorString("\n count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  InitProfile39();

  uchar i;
  for (i=0; i<bCount; i++)
  {
    if (GetPopCapacity39() < 2 + 2+12 + 1+8)
      return Fault(130+3);

    if (PopChar39() != 0x02) // structure
      return Fault(130+4);

    if (PopChar39() != 2) // structure size
      return Fault(130+5);

    if (PopChar39() != 0x09) // string
      return Fault(130+6);

    if (PopChar39() != 12) // string size
      return Fault(130+7);

    time tm = PopTimeDate39();

    if (PopChar39() != 0x15) // unsigned long 64
      return Fault(130+8);

    uint64_t ddw = PopLongLong39();

    if (r.fFirst == false) {
      r.bError = 0;
      r.ddwValue = ddw;
      r.tmValue = tm;
      r.fFirst = true;

      PrfFirstPrev = PrfFirstCurr;

      PrfFirstCurr.fExists = true;
      PrfFirstCurr.tmTime = tm;
      PrfFirstCurr.ddwValue = ddw;
    }

#if BUFFER_RECORD_39
    MonitorString("\n");
    MonitorTime(tm);
    MonitorLongDec(ddw / 1000000);
    MonitorLongDec(ddw % 1000000);
#endif

    AddProfile39(tm, ddw);
  }

  if (PrfFirstPrev.fExists == true) {
#if BUFFER_RECORD_39
    MonitorString("\n");
    MonitorTime(PrfFirstPrev.tmTime);
    MonitorLongDec(PrfFirstPrev.ddwValue / 1000000);
    MonitorLongDec(PrfFirstPrev.ddwValue % 1000000);
    MonitorString(" previous");
#endif
    AddProfile39(PrfFirstPrev.tmTime, PrfFirstPrev.ddwValue);
  }

  return r;
}
