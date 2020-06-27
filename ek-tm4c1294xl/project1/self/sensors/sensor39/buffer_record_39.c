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
#include "buffer_array_39.h"
#include "buffer_profile_39.h"
#include "buffer_record_39.h"



//#define BUFF_RECORD_39  1



static profile39    PrfFirstPrev, PrfFirstCurr;



void    InitBuffRecord39_FragmentProfile39(void) {
  memset(&PrfFirstPrev, 0, sizeof(PrfFirstPrev));
  memset(&PrfFirstCurr, 0, sizeof(PrfFirstCurr));
}


void    InitBuffRecord39(void) {
  InitPush39();
}



void    AddBuffRecord39(uint  iwStart/*, uint  cwSize*/) { // TODO GetPushOverflow
  uint cwSize = IndexInBuff()-iwStart-3;

#ifdef BUFF_RECORD_39
  MonitorX();

  MonitorString("\n AddToBuffer: Start="); MonitorIntDec(iwStart);
  MonitorString("\n");
#endif

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    uchar b = PopChar();

#ifdef BUFF_RECORD_39
    MonitorCharHex(b);
    if (i % 16 == 16-1) MonitorString("\n");
#endif

    PushChar39(b);
  }

#ifdef BUFF_RECORD_39
  MonitorString("\n");
#endif
}



record39 GetBuffRecordError(char  bError)
{
  record39 r;

  r.bError = bError;
  r.ddwValue = 0;
  r.tiValue = tiZero;
  r.fFirst = false;

  return r;
}


record39 FinishBuffRecord39(void) {
  record39 r = GetBuffRecordError(0);


  InitPop39();

  if (GetPopCapacity39() < 2)
    return GetBuffRecordError(21);

  if (PopChar39() != 1) // array
    return GetBuffRecordError(22);

  uchar bCount = PopChar39();

#ifdef BUFF_RECORD_39
  MonitorString("\n Count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  InitProfile39();

  uchar i;
  for (i=0; i<bCount; i++)
  {
    if (GetPopCapacity39() < 2 + 2+12 + 1+8)
      return GetBuffRecordError(23);

    if (PopChar39() != 0x02) // structure
      return GetBuffRecordError(24);

    if (PopChar39() != 2) // structure size
      return GetBuffRecordError(25);

    if (PopChar39() != 0x09) // string
      return GetBuffRecordError(26);

    if (PopChar39() != 12) // string size
      return GetBuffRecordError(27);

    time ti = PopTimeDate39();

    if (PopChar39() != 0x15) // unsigned long 64
      return GetBuffRecordError(28);

    uint64_t ddw = PopLongLong39();

    if (r.fFirst == false) {
      r.bError = 0;
      r.ddwValue = ddw;
      r.tiValue = ti;
      r.fFirst = true;

      PrfFirstPrev = PrfFirstCurr;

      PrfFirstCurr.fExists = true;
      PrfFirstCurr.tiTime = ti;
      PrfFirstCurr.ddwValue = ddw;
    }

#if BUFF_RECORD_39
    MonitorString("\n");
    MonitorTime(ti);
    MonitorLongDec(ddw / 1000000);
    MonitorLongDec(ddw % 1000000);
#endif

    AddProfile39(ti, ddw);
  }

  if (PrfFirstPrev.fExists == true) {
#if BUFF_RECORD_39
    MonitorString("\n");
    MonitorTime(PrfFirstPrev.tiTime);
    MonitorLongDec(PrfFirstPrev.ddwValue / 1000000);
    MonitorLongDec(PrfFirstPrev.ddwValue % 1000000);
    MonitorString(" previous");
#endif
    AddProfile39(PrfFirstPrev.tiTime, PrfFirstPrev.ddwValue);
  }

  return r;
}
