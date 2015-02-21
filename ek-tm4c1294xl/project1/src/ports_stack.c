/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "ports.h"
#include        "memory/mem_serial0.h"



void    InitPush(uchar  ibPush) {
  switch (ibPort) {
    case 0: iwPush0 = ibPush; break;
  }
}


void    InitPushCRC(void) {
	InitPush(5);
}


void    InitPushPtr(void) {
	InitPush(bHEADER);
}


void    Push(void  *pbData, uint  wSize) {
  switch (ibPort) {
    case 0: 
      if (iwPush0+wSize < sizeof(mpbOutBuff0)-bMARGIN) {
        memcpy(&mpbOutBuff0[ iwPush0 ], pbData, wSize);
        iwPush0 += wSize;
      }
      break;
  }
}


void    PushChar(uchar  bT) {
  Push(&bT, sizeof(uchar));
}


void    PushInt(uint  wT) {
	PushChar(wT / 0x100);
	PushChar(wT % 0x100);
}


void    PushLong(ulong  dwT) {
	PushInt(dwT / 0x10000);
	PushInt(dwT % 0x10000);
}


void    PushReal(real  reT)
{
  Push(&reT, sizeof(real));
}


void    PushTime(time  *pti)
{
  Push(pti, sizeof(time));
}



uchar   SkipChar(void) {
  switch (ibPort) {
    case 0: return mpbOutBuff0[ iwPush0++ ];
  }

  return 0; // TODO
}


void    Skip(uint  wSize) {
  switch (ibPort) {
    case 0: iwPush0 += wSize; break;
  }
}



void    InitPop(uint  i) {
  switch (ibPort) {
    case 0: iwPop0 = i; break;
  }
}



void    Pop(void  *pbData, uint  wSize) {
  switch (ibPort) {
    case 0: memcpy(pbData, &mpbInBuff0[ iwPop0 ], wSize); iwPop0 += wSize; break;
  }
}


uchar   PopChar(void) {
  switch (ibPort) {
    case 0: return mpbInBuff0[ iwPop0++ ];
  }

  return 0; // TODO
}
