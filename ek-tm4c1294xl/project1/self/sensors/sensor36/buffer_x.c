/*------------------------------------------------------------------------------
buffers_x.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "buffers_x.h"



uchar                       mpbBuffX[3000]; // TODO check overflow

uint                        iwPushX, iwPopX;



void    InitPushX(void) {
  memset(&mpbBuffX, 0xFF, sizeof(mpbBuffX));
  iwPushX = 0;
}


void    PushCharX(uchar  b) {
  mpbBuffX[iwPushX++] = b;
}



void    InitPopX(void) {
  iwPopX = 0;
}


uchar   PopCharX(void) {
  return mpbBuffX[iwPopX++];
}


uint    PopIntBigX(void) {
  return PopCharX()*0x100 + PopCharX();
}


ulong   PopLongBigX(void) {
  return PopIntBigX()*0x10000 + PopIntBigX();
}


time    PopTimeDateX(void)
{
  time ti;
  ti.bYear   = PopIntBigX() - 2000;
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


uint64_t PopULong64X(void)
{
  return PopLongBig()*0x100000000 + PopLongBigX();
}

