/*------------------------------------------------------------------------------
buffers36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "buffers36.h"



void    PrintInBuff(uint  iwStart, uint  cwSize) {
  MonitorString("\n buffer size "); MonitorIntDec(cwSize);
  MonitorString("\n ");

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    MonitorCharHex(PopChar());
  }
}
