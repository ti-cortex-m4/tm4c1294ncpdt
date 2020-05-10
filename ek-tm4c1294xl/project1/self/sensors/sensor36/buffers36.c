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

  uint i = 0;
  MonitorCharHex(mpbBuff1[i++]);
  MonitorCharHex(mpbBuff1[i++]);
  MonitorString("\n\n");

  while (i<iwBuff1) {

    uchar k;
    for (k=0; k<2; k++)
      MonitorCharHex(mpbBuff1[i++]);

    MonitorString("\n");

    for (k=0; k<14; k++)
      MonitorCharHex(mpbBuff1[i++]);

    MonitorString("\n");

    for (k=0; k<9; k++)
      MonitorCharHex(mpbBuff1[i++]);

    MonitorString("\n\n");
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
