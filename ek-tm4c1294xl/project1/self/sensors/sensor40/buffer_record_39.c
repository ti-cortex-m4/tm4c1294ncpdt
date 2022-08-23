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
#include "buffer_array_40.h"
#include "buffer_profile_40.h"
#include "buffer_record_39.h"



void    InitRecord40(void) {
  InitPush40();
}



void    AddRecord40(uint  iwStart) {
  if (IsPushOverflow40()) {
    Error40(150+0);
    return;
  }

  uint cwSize = IndexInBuff()-iwStart-3;

#ifdef BUFFER_ARRAY_40
  MonitorArray40();

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

    PushChar40(b);
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



bool    FinishRecord40(void) {
#if BUFFER_RECORD_40
  MonitorString("\n FinishRecord40");
#endif

  InitPop40();

  uint wCapacity = GetPopCapacity40();
  if (wCapacity < 2)
    return FaultData(150+1, wCapacity);

  uchar bTypeArray = PopChar40();
  if (bTypeArray != 0x01) // array
    return FaultData(150+2, bTypeArray);

  uchar bCount = PopChar40();

#ifdef BUFFER_RECORD_40
  MonitorString("\n count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  uchar i;
  for (i=0; i<bCount; i++)
  {
    wCapacity = GetPopCapacity40();
    if (wCapacity < 2 + 2+12 + 4*(1+4))
      return FaultData(150+3, wCapacity);

    uchar bTypeStructure = PopChar40();
    if (bTypeStructure != 0x02) // structure
      return FaultData(150+4, bTypeStructure);

    uchar bSizeStructure = PopChar40();
    if (bSizeStructure != 5) // structure size
      return FaultData(150+5, bSizeStructure);

    uchar bTypeString = PopChar40();
    if (bTypeString != 0x09) // string
      return FaultData(150+6, bTypeString);

    uchar bSizeString = PopChar40();
    if (bSizeString != 12) // string size
      return FaultData(150+7, bSizeString);

    time tm = PopTimeDate40();

    ulong mdwValue[4];

    uchar c;
    for (c=0; c<4; c++)
    {
      uchar bTypeLong32 = PopChar40();
      if (bTypeLong32 != 0x06) // double-long-unsigned 32
        return FaultData(150+8, bTypeLong32);

       mdwValue[c] = PopLong40();
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



bool    FinishRecordProfile40(void) {
#if BUFFER_RECORD_40
  MonitorString("\n FinishRecordProfile40");
#endif

  InitPop40();

  if (GetPopCapacity40() < 2)
    return Fault(150+1);

  if (PopChar40() != 0x01) // array
    return Fault(150+2);

  uchar bCount = PopChar40();

#ifdef BUFFER_RECORD_40
  MonitorString("\n count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  InitProfile40();

  uchar i;
  for (i=0; i<bCount; i++)
  {
    if (GetPopCapacity40() < 2 + 2+12 + 4*(1+4))
      return Fault(150+3);

    if (PopChar40() != 0x02) // structure
      return Fault(150+4);

    if (PopChar40() != 5) // structure size
      return Fault(150+5);

    if (PopChar40() != 0x09) // string
      return Fault(150+6);

    if (PopChar40() != 12) // string size
      return Fault(150+7);

    time tm = PopTimeDate40();

    ulong mdwValue[4];

    uchar c;
    for (c=0; c<4; c++)
    {
      if (PopChar40() != 0x06) // double-long-unsigned 32
        return Fault(150+8);

      mdwValue[c] = PopLong40();
    }

    AddProfile40(tm, mdwValue);
  }

  if (IsProfileOveflow40())
    return Fault(150+9);
  else
    return true;
}
