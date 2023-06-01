/*------------------------------------------------------------------------------
bcd_time.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "bcd_time.h"



time    BcdTimeToTime(ulong  dw)
{
  time tm;

  tm.bSecond = 0x3F & (dw);
  tm.bMinute = 0x3F & (dw >> 6);
  tm.bHour   = 0x1F & (dw >> 6+6);

  tm.bDay    = 0x1F & (dw >> 6+6+5);
  tm.bMonth  = 0x0F & (dw >> 6+6+5+5);
  tm.bYear  = (0x3F & (dw >> 6+6+5+5+4)) + 20;

  return tm;  
}


ulong   TimeToBcdTime(time  tm)
{
  ulong dw = 0;

  dw |= (tm.bSecond      & 0x3F);
  dw |= (tm.bMinute      & 0x3F) << 6;
  dw |= (tm.bHour        & 0x1F) << 6+6;

  dw |= (tm.bDay         & 0x1F) << 6+6+5;
  dw |= (tm.bMonth       & 0x0F) << 6+6+5+5;
  dw |= ((tm.bYear - 20) & 0x3F) << 6+6+5+5+4;

  return dw;
}
