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



void    InitBuffRecord39(void) {
  InitPushX();
}


void    AddBuffRecord39(uint  iwStart, uint  cwSize) {
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

    PushCharX(b);
  }

#ifdef BUFF_RECORD_39
  MonitorString("\n");
#endif
}



record39 GetBufferYError(char  bError)
{
  record39 r;

  r.bError = bError;
  r.ddwValue = 0;
  r.tiValue = tiZero;
  r.fFirst = false;

  return r;
}


record39 FinishBuffRecord39(void) {
  record39 r;
  r.bError = 0;
  r.ddwValue = 0;
  r.tiValue = tiZero;
  r.fFirst = false;


  InitPopX();

  if (GetPopCapacity() < 2)
    return GetBufferYError(1);

  if (PopCharX() != 1) // array
    return GetBufferYError(2);

  uchar bCount = PopCharX();

#ifdef BUFF_RECORD_39
  MonitorString("\n Count="); MonitorCharDec(bCount); MonitorString("\n");
#endif

  InitBuffPrf39();

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

    if (r.fFirst == false) {
      r.bError = 0;
      r.ddwValue = ddw;
      r.tiValue = ti;
      r.fFirst = true;
    }

#ifdef BUFF_RECORD_39
    MonitorString("\n");
    MonitorTime(ti);
    MonitorLongDec(ddw / 1000000);
    MonitorLongDec(ddw % 1000000);
#endif

    AddBuffPrf39(ti, ddw);
  }

  return r;
}
