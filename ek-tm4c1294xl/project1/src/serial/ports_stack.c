/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_serial0.h"
#include        "../memory/mem_serial1.h"
#include        "../memory/mem_serial2.h"
#include        "../memory/mem_serial3.h"
#include        "../display/lines.h"
#include        "ports.h"



static char const       szHex[0x10]  = "0123456789ABCDEF";



void    InitPush(uchar  ibPush) {
  switch (ibPort) {
    case 0: iwPush0 = ibPush; break;
    case 1: iwPush1 = ibPush; break;
    case 2: iwPush2 = ibPush; break;
    case 3: iwPush3 = ibPush; break;
    default: ASSERT(false);
  }
}


void    InitPushCRC(void) {
	InitPush(5);
}


void    InitPushPtr(void) {
	InitPush(bHEADER);
}


void    InitPushUni(void) {
	InitPush(6);
}



void    Push(void  *pbData, uint  wSize) {
  switch (ibPort) {
    case 0: 
      if (iwPush0+wSize < sizeof(mpbOutBuff0)-bMARGIN) {
        memcpy(&mpbOutBuff0[ iwPush0 ], pbData, wSize);
        iwPush0 += wSize;
      }
      break;

    case 1:
      if (iwPush1+wSize < sizeof(mpbOutBuff1)-bMARGIN) {
        memcpy(&mpbOutBuff1[ iwPush1 ], pbData, wSize);
        iwPush1 += wSize;
      }
      break;

    case 2:
      if (iwPush2+wSize < sizeof(mpbOutBuff2)-bMARGIN) {
        memcpy(&mpbOutBuff2[ iwPush2 ], pbData, wSize);
        iwPush2 += wSize;
      }
      break;

    case 3:
      if (iwPush3+wSize < sizeof(mpbOutBuff3)-bMARGIN) {
        memcpy(&mpbOutBuff3[ iwPush3 ], pbData, wSize);
        iwPush3 += wSize;
      }
      break;

    default: ASSERT(false);
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


void    PushFloat(float  fl)
{
  static combo32 co;
  co.reBuff = fl;

  PushChar(co.mpbBuff[3]);
  PushChar(co.mpbBuff[2]);
  PushChar(co.mpbBuff[1]);
  PushChar(co.mpbBuff[0]);
}


void    PushDouble(double  db)
{
  static combo64 co;
  co.dbBuff = db;

  PushChar(co.mpbBuff[7]);
  PushChar(co.mpbBuff[6]);
  PushChar(co.mpbBuff[5]);
  PushChar(co.mpbBuff[4]);
  PushChar(co.mpbBuff[3]);
  PushChar(co.mpbBuff[2]);
  PushChar(co.mpbBuff[1]);
  PushChar(co.mpbBuff[0]);
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


void    PushBuffInt(uint  *pwData, uint  wSize)
{
  while (wSize-- > 0)
    PushInt(*pwData++);
}


void    PushBuffLong(ulong  *pdwData, uint  wSize)
{
  while (wSize-- > 0)
    PushLong(*pdwData++);
}



void    PushIntAsString(uint  wT)
{
	PushChar(szHex[(wT % 100000) / 10000]);
	PushChar(szHex[(wT % 10000) / 1000]);
	PushChar(szHex[(wT % 1000) / 100]);
	PushChar(szHex[(wT % 100) / 10]);
	PushChar(szHex[wT % 10]);
}



void	PushCharHex2Txt(uchar  bT)
{
  PushChar(szDigits[ bT / 0x10 ]);
  PushChar(szDigits[ bT % 0x10 ]);
}


void	PushCharDec2Txt(uchar  bT)
{
  PushChar(szDigits[ bT / 10 ]);
  PushChar(szDigits[ bT % 10 ]);
}



uchar   SkipChar(void) {
  switch (ibPort) {
    case 0: return mpbOutBuff0[ iwPush0++ ];
    case 1: return mpbOutBuff1[ iwPush1++ ];
    case 2: return mpbOutBuff2[ iwPush2++ ];
    case 3: return mpbOutBuff3[ iwPush3++ ];
    default: ASSERT(false); return 0;
  }
}


void    Skip(uint  wSize) {
  switch (ibPort) {
    case 0: iwPush0 += wSize; break;
    case 1: iwPush1 += wSize; break;
    case 2: iwPush2 += wSize; break;
    case 3: iwPush3 += wSize; break;
    default: ASSERT(false);
  }
}



void    InitPop(uint  i) {
  switch (ibPort) {
    case 0: iwPop0 = i; break;
    case 1: iwPop1 = i; break;
    case 2: iwPop2 = i; break;
    case 3: iwPop3 = i; break;
    default: ASSERT(false);
  }
}



void    Pop(void  *pbData, uint  wSize) {
  switch (ibPort) {
    case 0: memcpy(pbData, &mpbInBuff0[ iwPop0 ], wSize); iwPop0 += wSize; break;
    case 1: memcpy(pbData, &mpbInBuff1[ iwPop1 ], wSize); iwPop1 += wSize; break;
    case 2: memcpy(pbData, &mpbInBuff2[ iwPop2 ], wSize); iwPop2 += wSize; break;
    case 3: memcpy(pbData, &mpbInBuff3[ iwPop3 ], wSize); iwPop3 += wSize; break;
    default: ASSERT(false);
  }
}


uchar   PopChar(void) {
  switch (ibPort) {
    case 0: return mpbInBuff0[ iwPop0++ ];
    case 1: return mpbInBuff1[ iwPop1++ ];
    case 2: return mpbInBuff2[ iwPop2++ ];
    case 3: return mpbInBuff3[ iwPop3++ ];
    default: ASSERT(false); return 0;
  }
}
