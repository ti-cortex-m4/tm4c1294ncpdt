/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "ports.h"
#include        "mem_serial0.h"



void    InitPush(void) {
  switch (ibPort) {
    case 0: iwPush0 = 0; break;
  }
}


void    InitPushCRC(void) {
  switch (ibPort) {
    case 0: iwPush0 = 5; break;
  }
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
  Push(&wT, sizeof(uint));
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
