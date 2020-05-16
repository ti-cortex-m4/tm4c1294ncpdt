/*------------------------------------------------------------------------------
buffers_x.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include38.h"
#include "buffer_x.h"



uchar                       mpbBuffX[3000]; // TODO check overflow

uint                        iwPushX, iwPopX;



void    MonitorX(void) {
#ifdef MONITOR_38
  MonitorString("\n ReadFromBuffer");
  MonitorArrayHex(mpbBuffX, iwPushX);
#endif
}



void    InitPushX(void) {
  memset(&mpbBuffX, 0xFF, sizeof(mpbBuffX));
  iwPushX = 0;
}


void    PushCharX(uchar  b) {
  mpbBuffX[iwPushX++] = b;
}



void    InitPopX(void) {
  MonitorX();

  iwPopX = 0;
}


uint    GetPopCapacity(void) {
  return sizeof(mpbBuffX) - iwPopX;
}


uchar   PopCharX(void) {
  return mpbBuffX[iwPopX++];
}


uint    PopIntX(void) {
  return PopCharX()*0x100 + PopCharX();
}


ulong   PopLongX(void) {
  return PopIntX()*0x10000 + PopIntX();
}


uint64_t PopLong64X(void) {
  return PopLongX()*0x100000000 + PopLongX();
}


time    PopTimeDateX(void)
{
  time ti;
  ti.bYear   = PopIntX() - 2000;
  ti.bMonth  = PopCharX();
  ti.bDay    = PopCharX();

  PopCharX();

  ti.bHour   = PopCharX();
  ti.bMinute = PopCharX();
  ti.bSecond = PopCharX();

  PopCharX();
  PopCharX();
  PopCharX();
  PopCharX();

  return ti;
}

