/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_serial0.h"
#include        "ports.h"



static char const       szHex[0x10]  = "0123456789ABCDEF";



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


void    PushString(char  *psz)
{
  while (true)
  {
    if (!*psz) break;
    PushChar(*psz++);
  }
}


void    PushIntAsString(uint  wT)
{
	PushChar(szHex[(wT % 100000) / 10000]);
	PushChar(szHex[(wT % 10000) / 1000]);
	PushChar(szHex[(wT % 1000) / 100]);
	PushChar(szHex[(wT % 100) / 10]);
	PushChar(szHex[wT % 10]);
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
