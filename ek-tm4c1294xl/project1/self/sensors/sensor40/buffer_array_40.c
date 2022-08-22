/*------------------------------------------------------------------------------
buffer_array_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "include40.h"
#include "error40.h"
#include "buffer_array_40.h"



static uchar                mpbBuff[4096];

static uint                 iwPush, iwPop;



void    MonitorArray40(void) {
#ifdef BUFFER_ARRAY_40
  MonitorString("\n MonitorArray40");
  MonitorArrayHex(mpbBuff, iwPush);
#endif
}



void    InitPush40(void) {
  memset(&mpbBuff, 0xFF, sizeof(mpbBuff));
  iwPush = 0;
}


void    PushChar40(uchar  b) {
  if (iwPush < sizeof(mpbBuff)-1)
    mpbBuff[iwPush++] = b;
  else  
    ErrorData40(144+0, iwPush);
}


bool    IsPushOverflow40(void)
{
  return iwPush >= sizeof(mpbBuff)-1;
}



void    InitPop40(void) {
  MonitorArray40();

  iwPop = 0;
}


uint    GetPopCapacity40(void) {
  return sizeof(mpbBuff) - iwPop;
}


uchar   PopChar40(void) {
  return mpbBuff[iwPop++];
}


uint    PopInt40(void) {
  return PopChar40()*0x100 + PopChar40();
}


ulong   PopLong40(void) {
  return PopInt40()*0x10000 + PopInt40();
}


uint64_t PopLongLong40(void) {
  return PopLong40()*0x100000000 + PopLong40();
}


time    PopTimeDate40(void)
{
  time tm;
  tm.bYear   = PopInt40() - 2000;
  tm.bMonth  = PopChar40();
  tm.bDay    = PopChar40();

  PopChar40();

  tm.bHour   = PopChar40();
  tm.bMinute = PopChar40();
  tm.bSecond = PopChar40();

  PopChar40();
  PopChar40();
  PopChar40();
  PopChar40();

  return tm;
}

