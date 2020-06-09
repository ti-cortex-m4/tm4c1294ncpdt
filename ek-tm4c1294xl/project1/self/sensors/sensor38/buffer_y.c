/*------------------------------------------------------------------------------
buffer_y*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "include38.h"
#include "buffer_x.h"
#include "buffer_z.h"
#include "buffer_y.h"



void    StartBufferY(void) {
  InitPushX();
}


void    AddBufferY(uint  iwStart, uint  cwSize) {
#ifdef MONITOR_38
  MonitorX();

  MonitorString("\n AddToBuffer: Start="); MonitorIntDec(iwStart);
  MonitorString("\n");
#endif

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    uchar b = PopChar();

#ifdef MONITOR_38
    MonitorCharHex(b);
    if (i % 16 == 16-1) MonitorString("\n");
#endif

    PushCharX(b);
  }

#ifdef MONITOR_38
  MonitorString("\n");
#endif
}



buff_y  GetBufferYError(char  bError)
{
  buff_y by;

  by.bError = bError;
  by.ddwValue = 0;
  by.tiValue = tiZero;
  by.fFirst = false;

  return by;
}


buff_y  FinishBufferY(void) {
  buff_y by;
  by.bError = 0;
  by.ddwValue = 0;
  by.tiValue = tiZero;
  by.fFirst = false;


  InitPopX();

  if (GetPopCapacity() < 2)
    return GetBufferYError(1);

  if (PopCharX() != 1) // array
    return GetBufferYError(2);

  uchar bCount = PopCharX();

#ifdef MONITOR_38
  MonitorString("\n Count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  InitBufferZ();

  uchar i;
  for (i=0; i<bCount; i++)
  {
    if (GetPopCapacity() < 2 + 2+12 + 1+8)
      return GetBufferYError(3);

    if (PopCharX() != 0x02) // structure
      return GetBufferYError(4);

    if (PopCharX() != 2) // structure size
      return GetBufferYError(5);

    if (PopCharX() != 0x09) // string
      return GetBufferYError(6);

    if (PopCharX() != 12) // string size
      return GetBufferYError(7);

    time ti = PopTimeDateX();

    if (PopCharX() != 0x15) // unsigned long 64
      return GetBufferYError(8);

    uint64_t ddw = PopLong64X();

    if (by.fFirst == false) {
      by.bError = 0;
      by.ddwValue = ddw;
      by.tiValue = ti;
      by.fFirst = true;
    }

#ifdef MONITOR_38
    MonitorString("\n");
    MonitorTime(ti);
    MonitorLongDec(ddw / 1000000);
    MonitorLongDec(ddw % 1000000);
#endif

    AddBufferZ(ti, ddw);
  }

  return by;
}
