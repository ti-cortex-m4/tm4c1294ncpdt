/*------------------------------------------------------------------------------
PORTS_POP!H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_serial0.h"
#include "../memory/mem_serial1.h"
#include "../memory/mem_serial2.h"
#include "../memory/mem_serial3.h"
#include "../kernel/parity.h"
#include "../display/lines.h"
#include "ports.h"
#include "ports_pop.h"



static uint             cwPopSize;



uint    GetPopSize(void)
{
  return cwPopSize;
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
  cwPopSize = i;

  switch (ibPort) {
    case 0: iwPop0 = i; break;
    case 1: iwPop1 = i; break;
    case 2: iwPop2 = i; break;
    case 3: iwPop3 = i; break;
    default: ASSERT(false);
  }
}



void    Pop(void  *pbData, uint  wSize) {
  cwPopSize += wSize;

  switch (ibPort) {
    case 0: memcpy(pbData, &mpbInBuff0[ iwPop0 ], wSize); iwPop0 += wSize; break;
    case 1: memcpy(pbData, &mpbInBuff1[ iwPop1 ], wSize); iwPop1 += wSize; break;
    case 2: memcpy(pbData, &mpbInBuff2[ iwPop2 ], wSize); iwPop2 += wSize; break;
    case 3: memcpy(pbData, &mpbInBuff3[ iwPop3 ], wSize); iwPop3 += wSize; break;
    default: ASSERT(false);
  }
}


uchar   PopChar(void) {
  cwPopSize++;

  switch (ibPort) {
    case 0: return mpbInBuff0[ iwPop0++ ];
    case 1: return mpbInBuff1[ iwPop1++ ];
    case 2: return mpbInBuff2[ iwPop2++ ];
    case 3: return mpbInBuff3[ iwPop3++ ];
    default: ASSERT(false); return 0;
  }
}


uint    PopIntBig(void)
{
  return PopChar()*0x100 + PopChar();
}


uint    PopIntLtl(void)
{
  uchar b = PopChar();
  return b + PopChar()*0x100;
}


ulong   PopLongBig(void)
{
  static combo32 co;

  co.mpbBuff[3] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[0] = PopChar();

  return co.dwBuff;
}


ulong   PopLongLtl(void)
{
  static combo32 co;

  co.mpbBuff[0] = PopChar();
  co.mpbBuff[1] = PopChar();
  co.mpbBuff[2] = PopChar();
  co.mpbBuff[3] = PopChar();

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


time    PopTime(void)
{
  time ti;

  ti.bSecond = PopChar();
  ti.bMinute = PopChar();
  ti.bHour   = PopChar();
  ti.bDay    = PopChar();
  ti.bMonth  = PopChar();
  ti.bYear   = PopChar();

  return ti;
}
