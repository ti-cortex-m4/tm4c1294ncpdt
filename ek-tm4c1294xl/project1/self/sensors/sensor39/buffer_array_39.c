/*------------------------------------------------------------------------------
buffer_array_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "buffer_array_39.h"



static uchar                mpbBuff[4096];

static uint                 iwPush, iwPop;



void    MonitorArray39(void) {
#ifdef ARRAY_39
  MonitorString("\n ReadFromBuffer");
  MonitorArrayHex(mpbBuff, iwPush);
#endif
}



void    InitPush39(void) {
  memset(&mpbBuff, 0xFF, sizeof(mpbBuff));
  iwPush = 0;
}


void    PushChar39(uchar  b) {
  mpbBuff[iwPush++] = b;
}



void    InitPop39(void) {
  MonitorArray39();

  iwPop = 0;
}


uint    GetPopCapacity39(void) {
  return sizeof(mpbBuff) - iwPop;
}


uchar   PopChar39(void) {
  return mpbBuff[iwPop++];
}


uint    PopIntX(void) {
  return PopChar39()*0x100 + PopChar39();
}


ulong   PopLongX(void) {
  return PopIntX()*0x10000 + PopIntX();
}


uint64_t PopLong6439(void) {
  return PopLongX()*0x100000000 + PopLongX();
}


time    PopTimeDate39(void)
{
  time ti;
  ti.bYear   = PopIntX() - 2000;
  ti.bMonth  = PopChar39();
  ti.bDay    = PopChar39();

  PopChar39();

  ti.bHour   = PopChar39();
  ti.bMinute = PopChar39();
  ti.bSecond = PopChar39();

  PopChar39();
  PopChar39();
  PopChar39();
  PopChar39();

  return ti;
}

