/*------------------------------------------------------------------------------
buffer_record_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "include40.h"
#include "error40.h"
#include "buffer_array_39.h"
#include "buffer_profile_39.h"
#include "buffer_record_39.h"



void    InitRecord39(void) {
  InitPush39();
}



void    AddRecord39(uint  iwStart) {
  if (IsPushOverflow39()) {
    Error40(150+0);
    return;
  }

  uint cwSize = IndexInBuff()-iwStart-3;

#ifdef BUFFER_ARRAY_40
  MonitorArray39();

  MonitorString("\n AddToBuffer: start="); MonitorIntDec(iwStart);
  MonitorString("\n");
#endif

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    uchar b = PopChar();

#ifdef BUFFER_ARRAY_40
    MonitorCharHex(b);
    if (i % 16 == 16-1) MonitorString("\n");
#endif

    PushChar39(b);
  }

#ifdef BUFFER_ARRAY_40
  MonitorString("\n");
#endif
}



static bool Fault(uchar  bError)
{
  Error40(bError);
  return false;
}


static bool FaultData(uchar  bError, uint  wData)
{
  ErrorData40(bError, wData);
  return false;
}



bool    FinishRecord39(void) {
  InitPop39();

  uint wCapacity = GetPopCapacity39();
  if (wCapacity < 2)
    return FaultData(150+1, wCapacity);

  uchar bTypeArray = PopChar39();
  if (bTypeArray != 0x01) // array
    return FaultData(150+2, bTypeArray);

  uchar bCount = PopChar39();

#ifdef BUFFER_RECORD_40
  MonitorString("\n count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  uchar i;
  for (i=0; i<bCount; i++)
  {
    wCapacity = GetPopCapacity39();
    if (wCapacity < 2 + 2+12 + 4*(1+4))
      return FaultData(150+3, wCapacity);

    uchar bTypeStructure = PopChar39();
    if (bTypeStructure != 0x02) // structure
      return FaultData(150+4, bTypeStructure);

    uchar bSizeStructure = PopChar39();
    if (bSizeStructure != 5) // structure size
      return FaultData(150+5, bSizeStructure);

    uchar bTypeString = PopChar39();
    if (bTypeString != 0x09) // string
      return FaultData(150+6, bTypeString);

    uchar bSizeString = PopChar39();
    if (bSizeString != 12) // string size
      return FaultData(150+7, bSizeString);

    time tm = PopTimeDate39();

    ulong mdwValue[4];

    uchar c;
    for (c=0; c<4; c++)
    {
      uchar bTypeLong32 = PopChar39();
      if (bTypeLong32 != 0x06) // double-long-unsigned 32
        return FaultData(150+8, bTypeLong32);

       mdwValue[c] = PopLong39();
    }

#if BUFFER_RECORD_40
    MonitorString("\n record ");
    MonitorTime(tm);
    MonitorString(" "); MonitorLongDec(mdwValue[0]);
    MonitorString(" "); MonitorLongDec(mdwValue[1]);
    MonitorString(" "); MonitorLongDec(mdwValue[2]);
    MonitorString(" "); MonitorLongDec(mdwValue[3]);
#endif
  }

  return true;
}



bool    FinishRecordProfile39(void) {
  InitPop39();

  if (GetPopCapacity39() < 2)
    return Fault(150+1);

  if (PopChar39() != 0x01) // array
    return Fault(150+2);

  uchar bCount = PopChar39();

#ifdef BUFFER_RECORD_40
  MonitorString("\n count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  InitProfile39();

  uchar i;
  for (i=0; i<bCount; i++)
  {
    if (GetPopCapacity39() < 2 + 2+12 + 4*(1+4))
      return Fault(150+3);

    if (PopChar39() != 0x02) // structure
      return Fault(150+4);

    if (PopChar39() != 5) // structure size
      return Fault(150+5);

    if (PopChar39() != 0x09) // string
      return Fault(150+6);

    if (PopChar39() != 12) // string size
      return Fault(150+7);

    time tm = PopTimeDate39();

    ulong mdwValue[4];

    uchar c;
    for (c=0; c<4; c++)
    {
      if (PopChar39() != 0x06) // double-long-unsigned 32
        return Fault(150+8);

      mdwValue[c] = PopLong39();
    }

    AddProfile39(tm, mdwValue);
  }

  if (IsProfileOveflow39())
    return Fault(150+9);
  else
    return true;
}
