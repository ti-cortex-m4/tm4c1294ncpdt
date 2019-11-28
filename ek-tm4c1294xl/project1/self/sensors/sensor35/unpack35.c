/*------------------------------------------------------------------------------
unpack35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "unpack35.h"



void    Unpack35(void)
{
  uchar i,j;

  i = 1;
  j = 1;

  while (i < IndexInBuff()) {
    if ((InBuff(i) == 0xDB) && (InBuff(i+1) == 0xDD)) {
#ifdef MONITOR_35
      MonitorString("\n unpack 0xDB at "); MonitorCharDec(i);
#endif
      SetInBuff(j, 0xDB);
      i++; i++;
      j++;
    } else if ((InBuff(i) == 0xDB) && (InBuff(i+1) == 0xDC)) {
#ifdef MONITOR_35
      MonitorString("\n unpack 0xC0 at "); MonitorCharDec(i);
#endif
      SetInBuff(j, 0xC0);
      i++; i++;
      j++;
    } else {
      SetInBuff(j, InBuff(i));
      i++;
      j++;
    }
  }

  SetIndexInBuff(j);
}
