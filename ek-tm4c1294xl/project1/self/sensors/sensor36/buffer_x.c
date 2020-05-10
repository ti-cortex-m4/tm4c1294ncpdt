/*------------------------------------------------------------------------------
buffers36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "buffers_x.h"



uchar                       mpbBuffX[3000]; // TODO check overflow

uint                        iwBuff1;



void    StartBuffer1(void) {
  memset(&mpbBuffX, 0xFF, sizeof(mpbBuffX));
  iwBuff1 = 0;
}

void    AddBuffer1(uint  iwStart, uint  cwSize) {
  MonitorString("\n buffer size "); MonitorIntDec(cwSize); MonitorString("\n ");
  if (cwSize > 5000) return;

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    uchar b = PopChar();
    mpbBuffX[iwBuff1++] = b;
    MonitorCharHex(b);
  }
}


uchar   PopCharX(void) {
  return mpbBuffX[ iwPopDLMS++ ];
}


time    PopTimeDateX(void)
{
  time ti;
  ti.bYear   = PopIntBigX() - 2000;
  ti.bMonth  = PopCharX();
  ti.bDay    = PopCharX();

  PopChar();

  ti.bHour   = PopCharX();
  ti.bMinute = PopCharX();
  ti.bSecond = PopCharX();

  PopCharX();
  PopCharX();
  PopCharX();
  PopCharX();

  return ti;
}


uint64_t PopULong64X(void)
{
  return PopLongBigX()*0x100000000 + PopLongBigX();
}


