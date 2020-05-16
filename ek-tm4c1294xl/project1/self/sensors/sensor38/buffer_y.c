/*------------------------------------------------------------------------------
buffer_y.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../time/timedate.h"
#include "buffer_x.h"
#include "buffer_y.h"



void    StartBufferY(void) {
  InitPushX();
}


void    AddBufferY(uint  iwStart, uint  cwSize) {
  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    PushCharX(PopChar());
  }
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
  buff_y  by;
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

    MonitorString("\n");
    MonitorTime(ti);
    MonitorLongDec(ddw / 1000000);
    MonitorLongDec(ddw % 1000000);
  }

  return by;
}