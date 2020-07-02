/*------------------------------------------------------------------------------
buffer_record_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "error39.h"
#include "buffer_array_39.h"
#include "buffer_profile_39.h"
#include "buffer_record_39.h"



static profile39    FirstPrev, FirstCurr;



void    InitRecord39_FragmentProfile39(void) {
  memset(&FirstPrev, 0, sizeof(FirstPrev));
  memset(&FirstCurr, 0, sizeof(FirstCurr));
}


void    InitRecord39(void) {
  InitPush39();
}



void    AddRecord39(uint  iwStart) {
  if (IsPushOverflow39()) {
    Error39(140+0);
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
  static const time tiZero = { 0, 0, 0, 0, 0, 0 };
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


static record39 Fault_(uchar  bError, uint  wData)
{
  return GetRecordError39(Error39_(bError, wData));
}



record39 FinishRecord39(void) {
  record39 r = GetRecordError39(0);


  InitPop39();

  uint wCapacity1 = GetPopCapacity39();
  if (wCapacity1 < 2)
    return Fault_(140+1, wCapacity1);

  uchar bTypeArray = PopChar39();
  if (bTypeArray != 1) // array
    return Fault_(140+2, bTypeArray);

  uchar bCount = PopChar39();

#ifdef BUFFER_RECORD_39
  MonitorString("\n count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  uchar i;
  for (i=0; i<bCount; i++)
  {
    uint wCapacity2 = GetPopCapacity39();
    if (wCapacity2 < 2 + 2+12 + 1+8)
      return Fault_(140+3, wCapacity2);

    uchar bTypeStructure = PopChar39();
    if (bTypeStructure != 0x02) // structure
      return Fault_(140+4, bTypeStructure);

    uchar bSizeStructure = PopChar39();
    if (bSizeStructure != 2) // structure size
      return Fault_(140+5, bSizeStructure);

    uchar bTypeString = PopChar39();
    if (bTypeString != 0x09) // string
      return Fault_(140+6, bTypeString);

    uchar bSizeString = PopChar39();
    if (bSizeString != 12) // string size
      return Fault_(140+7, bSizeString);

    time tm = PopTimeDate39();

    uchar bTypeLong64 = PopChar39();
    if (bTypeLong64 != 0x15) // unsigned long 64
      return Fault_(140+8, bTypeLong64); // ???

    uint64_t ddwValue = PopLongLong39();

    if (r.fFirst == false) {
      r.bError = 0;
      r.ddwValue = ddwValue;
      r.tmValue = tm;
      r.fFirst = true;
    }
  }

  return r;
}



record39 FinishRecordProfile39(void) {
  record39 r = GetRecordError39(0);


  InitPop39();

  if (GetPopCapacity39() < 2)
    return Fault(140+1);

  if (PopChar39() != 1) // array
    return Fault(140+2);

  uchar bCount = PopChar39();

#ifdef BUFFER_RECORD_39
  MonitorString("\n count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  InitProfile39();

  uchar i;
  for (i=0; i<bCount; i++)
  {
    if (GetPopCapacity39() < 2 + 2+12 + 1+8)
      return Fault(140+3);

    if (PopChar39() != 0x02) // structure
      return Fault(140+4);

    if (PopChar39() != 2) // structure size
      return Fault(140+5);

    if (PopChar39() != 0x09) // string
      return Fault(140+6);

    if (PopChar39() != 12) // string size
      return Fault(140+7);

    time tm = PopTimeDate39();

    if (PopChar39() != 0x15) // unsigned long 64
      return Fault(140+8);

    uint64_t ddw = PopLongLong39();

    if (r.fFirst == false) {
      r.bError = 0;
      r.ddwValue = ddw;
      r.tmValue = tm;
      r.fFirst = true;

      FirstPrev = FirstCurr;

      FirstCurr.fExists = true;
      FirstCurr.tmTime = tm;
      FirstCurr.ddwValue = ddw;
    }

#if BUFFER_RECORD_39
    MonitorString("\n");
    MonitorTime(tm);
    MonitorLongDec(ddw / 1000000);
    MonitorLongDec(ddw % 1000000);
#endif
    AddProfile39(tm, ddw);
  }

  if (FirstPrev.fExists == true) {
#if BUFFER_RECORD_39
    MonitorString("\n");
    MonitorTime(FirstPrev.tmTime);
    MonitorLongDec(FirstPrev.ddwValue / 1000000);
    MonitorLongDec(FirstPrev.ddwValue % 1000000);
    MonitorString(" previous");
#endif
    AddProfile39(FirstPrev.tmTime, FirstPrev.ddwValue);
  }

  if (IsProfileOveflow39())
    return Fault(140+9);
  else
    return r;
}
