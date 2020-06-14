/*------------------------------------------------------------------------------
PORTS_PUSH!H


------------------------------------------------------------------------------*/

#include "../main.h"
#include <stdio.h>
#include "../memory/mem_serial0.h"
#include "../memory/mem_serial1.h"
#include "../memory/mem_serial2.h"
#include "../memory/mem_serial3.h"
#include "../kernel/parity.h"
#include "../display/lines.h"
#include "ports.h"
#include "ports_push.h"



extern int usprintf(char * restrict s, const char * restrict format, ...);



static char const       szHex[0x10]  = "0123456789ABCDEF";

static uint             cwPushSize;



uint    GetPushSize(void)
{
  return cwPushSize;
}



void    InitPush(uint  iwPush)
{
  cwPushSize = 0;

  switch (ibPort) {
    case 0: iwPush0 = iwPush; break;
    case 1: iwPush1 = iwPush; break;
    case 2: iwPush2 = iwPush; break;
    case 3: iwPush3 = iwPush; break;
    default: ASSERT(false);
  }
}


uint    GetPush(void) {
  switch (ibPort) {
    case 0: return iwPush0;
    case 1: return iwPush1;
    case 2: return iwPush2;
    case 3: return iwPush3;
    default: ASSERT(false); return 0;
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



uint    Push(void  *pbData, uint  wSize) {
  cwPushSize += wSize;

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

  return wSize;
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


uint    PushBoolArray(bool  *mpf, uchar  bCount)
{
  uint wSize = 0;

  uchar i;
  for (i=0; i<bCount; i++)
  {
    wSize += PushBool(mpf[i]);
  }

  return wSize;
}


uchar   PushIntBig(uint  w)
{
  PushChar(w / 0x100);
  PushChar(w % 0x100);

  return sizeof(uint);
}


uchar   PushIntLtl(uint  w)
{
  PushChar(w % 0x100);
  PushChar(w / 0x100);

  return sizeof(uint);
}


uint    PushIntBigArray(uint  *mpw, uint  wCount)
{
  uint wSize = 0;

  uint i;
  for (i=0; i<wCount; i++)
  {
    wSize += PushIntBig(mpw[i]);
  }

  return wSize;
}


uchar   PushLongBig(ulong  dw)
{
  PushIntBig(dw / 0x10000);
  PushIntBig(dw % 0x10000);

  return sizeof(ulong);
}


uchar   PushLongLtl(ulong  dw)
{
  PushIntLtl(dw % 0x10000);
  PushIntLtl(dw / 0x10000);

  return sizeof(ulong);
}


uint    PushLongBigArray(ulong  *mpdw, uint  wCount)
{
  uint wSize = 0;

  uint i;
  for (i=0; i<wCount; i++)
  {
    wSize += PushLongBig(mpdw[i]);
  }

  return wSize;
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


uchar   GetFloatOrDoubleSize(bool  fDouble)
{
  if (fDouble)
  {
    return sizeof(double);
  }
  else
  {
    return sizeof(float);
  }
}


uchar   PushTime(time  ti)
{
  Push(&ti, sizeof(time));

  return sizeof(time);
}


uint    PushString(char  *psz)
{
  uint wSize = 0;

  while (true)
  {
    if (!*psz) break;
    PushChar(*psz++);
    wSize++;
  }

  return wSize;
}


void    PushBuffInt(uint  *pwData, uint  wSize)
{
  while (wSize-- > 0)
    PushIntBig(*pwData++);
}


void    PushBuffLong(ulong  *pdwData, uint  wSize)
{
  while (wSize-- > 0)
    PushLongBig(*pdwData++);
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


uchar   PushCharDec2Txt(uchar  bT)
{
  PushChar(szDigits[ bT / 10 ]);
  PushChar(szDigits[ bT % 10 ]);

  return 2;
}



uchar   PushFloat3(float  fl)
{
static char mbT[15*2];

  memset(&mbT, 0, sizeof(mbT));
  uchar n = sprintf(mbT, "%.3f", fl);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbT[i]);
  }

  return n;
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



uchar   PushNumberBcc(ulong  dwT)
{
static char mbT[10*2];

  memset(&mbT, 0, sizeof(mbT));
  uchar n = usprintf(mbT, "%u" ,dwT);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar1Bcc(mbT[i]);
  }

  return n;
}


void    PushStringBcc(char  *psz)
{
  while (true)
  {
    if (!*psz) break;
    PushChar1Bcc(*psz++);
  }
}
