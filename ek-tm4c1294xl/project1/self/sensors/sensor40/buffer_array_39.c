/*------------------------------------------------------------------------------
buffer_array_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "error40.h"
#include "buffer_array_39.h"



static uchar                mpbBuff[4096];

static uint                 iwPush, iwPop;



void    MonitorArray39(void) {
#ifdef BUFFER_ARRAY_39
  MonitorString("\n MonitorArray39");
  MonitorArrayHex(mpbBuff, iwPush);
#endif
}



void    InitPush39(void) {
  memset(&mpbBuff, 0xFF, sizeof(mpbBuff));
  iwPush = 0;
}


void    PushChar39(uchar  b) {
  if (iwPush < sizeof(mpbBuff)-1)
    mpbBuff[iwPush++] = b;
  else  
    Error40(145+0);
}


bool    IsPushOverflow39(void)
{
  return iwPush >= sizeof(mpbBuff)-1;
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


uint    PopInt39(void) {
  return PopChar39()*0x100 + PopChar39();
}


ulong   PopLong39(void) {
  return PopInt39()*0x10000 + PopInt39();
}


uint64_t PopLongLong39(void) {
  return PopLong39()*0x100000000 + PopLong39();
}


time    PopTimeDate39(void)
{
  time tm;
  tm.bYear   = PopInt39() - 2000;
  tm.bMonth  = PopChar39();
  tm.bDay    = PopChar39();

  PopChar39();

  tm.bHour   = PopChar39();
  tm.bMinute = PopChar39();
  tm.bSecond = PopChar39();

  PopChar39();
  PopChar39();
  PopChar39();
  PopChar39();

  return tm;
}

