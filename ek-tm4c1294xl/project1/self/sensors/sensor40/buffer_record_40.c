/*------------------------------------------------------------------------------
buffer_record_40.c


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
#include "buffer_record_40.h"



void    InitRecord40(void) {
  InitPush40();
}



void    AddRecord40(uint  iwStart) {
#ifdef BUFFER_ARRAY_40
  MonitorString("\n AddRecord40 "); MonitorIntDec(iwStart);
#endif

  if (IsPushOverflow40()) {
    Error40(150+0);
    return;
  }

  uint cwSize = IndexInBuff()-iwStart-3;

#ifdef BUFFER_ARRAY_40
  MonitorArray40();
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



bool    FinishRecord40_Monitor(void) {
#if BUFFER_RECORD_40
  MonitorString("\n FinishRecord40_Monitor");
#endif

  InitPop40();

  uint wCapacity = GetPopCapacity40();
  if (wCapacity < 2)
    return FaultData(150+1, wCapacity);

  uchar bType = PopChar40();
  if (bType != 0x01) // array
    return FaultData(150+2, bType);

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

    bType = PopChar40();
    if (bType != 0x02) // structure
      return FaultData(150+4, bType);

    uchar bSize = PopChar40();
    if (bSize != 5) // structure size
      return FaultData(150+5, bSize);

    bType = PopChar40();
    if (bType != 0x09) // string
      return FaultData(150+6, bType);

    bSize = PopChar40();
    if (bSize != 12) // string size
      return FaultData(150+7, bSize);

    time tm = PopTimeDate40();

    ulong mdwValue[4];

    uchar c;
    for (c=0; c<4; c++)
    {
      bType = PopChar40();
      if (bType != 0x06) // double-long-unsigned 32
        return FaultData(150+8, bType);

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



bool    FinishRecord40_AddProfile40(void) {
#if BUFFER_RECORD_40
  MonitorString("\n FinishRecord40_AddProfile40");
#endif

  InitPop40();

  uint wCapacity = GetPopCapacity40();
  if (wCapacity < 2)
    return FaultData(150+1, wCapacity);

  uchar bType = PopChar40();
  if (bType != 0x01) // array
    return FaultData(150+2, bType);

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
