/*------------------------------------------------------------------------------
buffer_y.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "buffer_x.h"
#include "buffer_y.h"



void    StartBufferY(void) {
  InitPushX();

  byValue.uint64_t = 0;
  byValue.tiValue = tiZero;
  byValue.fValid = false;
}


void    AddBufferY(uint  iwStart, uint  cwSize) {
  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    PushCharX(PopChar());
  }
}


buff_y  FinishBufferY(void) {
  buff_y  byValue;
  byValue.ddwValue = 0;
  byValue.tiValue = tiZero;
  byValue.fValid = false;


  InitPopX();

  if (GetPopCapacity() < 2)
    return 1;

  if (PopCharX() != 1) // array
    return 2;

  uchar bCount = PopCharX();

  uchar i;
  for (i=0; i<bCount; i++)
  {
    if (GetPopCapacity() < 2 + 2+12 + 1+8)
      return 3;

    if (PopCharX() != 0x02) // structure
      return 4;

    if (PopCharX() != 2) // structure size
      return 5;

    if (PopCharX() != 0x09) // string
      return 6;

    if (PopCharX() != 12) // string size
      return 7;

    time ti = PopTimeDateX();

    if (PopCharX() != 0x15) // unsigned long 64
      return 8;

    uint64_t ddw = PopLong64X();

    if (byValue.fValid == false) {
      byValue.ddwValue = ddw;
      byValue.tiValue = ti;
      byValue.fValid = true;
    }

    MonitorString("\n");
    MonitorTime(ti);
    MonitorLongDec(ddw / 1000000);
    MonitorLongDec(ddw % 1000000);
  }

  return byValue;
}
