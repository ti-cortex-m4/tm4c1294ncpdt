/*------------------------------------------------------------------------------
buffers36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "buffers36.h"


uchar                       mpbBuff1[3000];

uint                        iwBuff1;



void    StartBuffer1(void) {
  memset(&mpbBuff1, 0xFF, sizeof(mpbBuff1));
  iwBuff1 = 0;
}

void    AddBuffer1(uint  iwStart, uint  cwSize) {
  MonitorString("\n buffer size "); MonitorIntDec(cwSize); MonitorString("\n ");
  if (cwSize > 5000) return;

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    uchar b = PopChar();
    mpbBuff1[iwBuff1++] = b;
    MonitorCharHex(b);
  }
}

void    FinishBuffer1(void) {
  MonitorString("\n finish size "); MonitorIntDec(iwBuff1); MonitorString("\n ");

  uint i;
  for (i=0; i<iwBuff1; i++) {
    MonitorCharHex(mpbBuff1[i]);
  }
}




void    PrintInBuff(uint  iwStart, uint  cwSize) {
  MonitorString("\n buffer size "); MonitorIntDec(cwSize);
  MonitorString("\n ");

  if (cwSize > 5000) return;

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    MonitorCharHex(PopChar());
  }
}
