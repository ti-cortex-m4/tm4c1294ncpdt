/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_serial0.h"
#include "../memory/mem_serial1.h"
#include "../memory/mem_serial2.h"
#include "../memory/mem_serial3.h"
#include "../kernel/parity.h"
#include "../display/lines.h"
#include "ports.h"



static char const       szHex[0x10]  = "0123456789ABCDEF";



void    InitPush(uint  iwPush)
{
  switch (ibPort) {
    case 0: iwPush0 = iwPush; break;
    case 1: iwPush1 = iwPush; break;
    case 2: iwPush2 = iwPush; break;
    case 3: iwPush3 = iwPush; break;
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


void    InitPushPck(void) {
  InitPush(bPACKET_HEADER);
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


uchar   PushChar(uchar  b)
{
  Push(&b, sizeof(uchar));
  return sizeof(uchar);
}


uchar   PushBool(bool  f)
{
  f ? PushChar(0xFF) : PushChar(0x00);
  return sizeof(uchar);
}


uchar   PushInt(uint  w)
{
  PushChar(w / 0x100);
  PushChar(w % 0x100);

  return sizeof(uint);
}


void    PushIntArray(uint  *mpw, uint  wSize)
{
  uint i;
  for (i=0; i<wSize; i++)
  {
    PushInt(mpw[i]);
  }
}


uchar   PushLong(ulong  dw)
{
  PushInt(dw / 0x10000);
  PushInt(dw % 0x10000);

  return sizeof(ulong);
}


uchar    PushFloat(float  fl)
{
  static combo32 co;
  co.flBuff = fl;

  PushChar(co.mpbBuff[3]);
  PushChar(co.mpbBuff[2]);
  PushChar(co.mpbBuff[1]);
  PushChar(co.mpbBuff[0]);

  return sizeof(float);
}


uchar   PushDouble(double  db)
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

  return sizeof(double);
}


uchar   PushFloatOrDouble(double  db, bool  fDouble)
{
  if (fDouble)
  {
    PushDouble(db);
    return sizeof(double);
  }
  else
  {
    PushFloat((float)db);
    return sizeof(float);
  }
}


uchar   PushTime(time  ti)
{
  Push(&ti, sizeof(time));

  return sizeof(time);
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



void    PushLongAsString(ulong  dw)
{
  PushChar(szHex[(dw % 1000000) / 100000]);
  PushChar(szHex[(dw % 100000) / 10000]);
  PushChar(szHex[(dw % 10000) / 1000]);
  PushChar(szHex[(dw % 1000) / 100]);
  PushChar(szHex[(dw % 100) / 10]);
  PushChar(szHex[dw % 10]);
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



void	PushChar1Bcc(uchar  bT)
{
  bT &= 0x7F;

  if (EvenParity(bT)) bT |= 0x80;

  PushChar(bT);
}


void	PushChar2Bcc(uchar  bT)
{
  PushChar1Bcc(szDigits[ bT / 10 ]);
  PushChar1Bcc(szDigits[ bT % 10 ]);
}



uchar	PopChar0Bcc(void)
{
  return(PopChar() & 0x7F);
}


uchar	PopChar1Bcc(void)
{
  switch (PopChar0Bcc())
  {
	case '0': return(0);
	case '1': return(1);
	case '2': return(2);
	case '3': return(3);
	case '4': return(4);
	case '5': return(5);
	case '6': return(6);
	case '7': return(7);
	case '8': return(8);
	case '9': return(9);

	default:  return(0);
  }
}


uchar	PopChar2Bcc(void)
{
  return(PopChar1Bcc()*10 + PopChar1Bcc());
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


ulong   PopLong(void)
{
  static combo32 co;

  co.mpbBuff[3] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[0] = PopChar();

  return co.dwBuff;
}


float   PopFloat(void)
{
  static combo32 co;

  co.mpbBuff[3] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[0] = PopChar();

  return co.flBuff;
}


double  PopDouble(void)
{
  static combo64 co;

  co.mpbBuff[7] = PopChar();
  co.mpbBuff[6] = PopChar();
  co.mpbBuff[5] = PopChar();
  co.mpbBuff[4] = PopChar();
  co.mpbBuff[3] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[0] = PopChar();

  return co.dbBuff;
}
