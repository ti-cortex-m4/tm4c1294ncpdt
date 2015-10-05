/*------------------------------------------------------------------------------
PORTS_COMMON!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_serial0.h"
#include "../memory/mem_serial1.h"
#include "../memory/mem_serial2.h"
#include "../memory/mem_serial3.h"
#include "../isr/serial0.h"
#include "../isr/serial1.h"
#include "../isr/serial2.h"
#include "../isr/serial3.h"
#include "../kernel/crc-16.h"
#include "../kernel/crc_s.h"
#include "../kernel/crc_v.h"
#include "../kernel/crc_els.h"
#include "ports.h"



void    Answer(uint  wSize, serial  seT)
{
  switch (ibPort)
  {
    case 0:  Answer0(wSize, seT);  break;
    case 1:  Answer1(wSize, seT);  break;
    case 2:  Answer2(wSize, seT);  break;
    case 3:  Answer3(wSize, seT);  break;
    default: ASSERT(false);
  }
}



uchar   InBuff(uint  i)
{
  switch (ibPort)
  {
    case 0:  return( mpbInBuff0[i] );
    case 1:  return( mpbInBuff1[i] );
    case 2:  return( mpbInBuff2[i] );
    case 3:  return( mpbInBuff3[i] );
    default: ASSERT(false); return 0;
  }
}


uint    InBuffIntBig(uint  i)
{
  return InBuff(i)*0x100 + InBuff(i+1);
}


uint    InBuffIntLtl(uint  i)
{
  return InBuff(i) + InBuff(i+1)*0x100;
}



uint    CountInBuff(void)
{
  switch (ibPort)
  {
    case 0:  return(cwInBuff0);
    case 1:  return(cwInBuff1);
    case 2:  return(cwInBuff2);
    case 3:  return(cwInBuff3);
    default: ASSERT(false); return 0;
  }
}


uint    IndexInBuff(void)
{
  switch (ibPort)
  {
    case 0:  return(iwInBuff0);
    case 1:  return(iwInBuff1);
    case 2:  return(iwInBuff2);
    case 3:  return(iwInBuff3);
    default: ASSERT(false); return 0;
  }
}



uchar   OutBuff(uint  i)
{
  switch (ibPort)
  {
    case 0:  return( mpbOutBuff0[i] );
    case 1:  return( mpbOutBuff1[i] );
    case 2:  return( mpbOutBuff2[i] );
    case 3:  return( mpbOutBuff3[i] );
    default: ASSERT(false); return 0;
  }
}



void    MakeCRC16OutBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  MakeCRC16(mpbOutBuff0 + bOffset, wSize);  break;
    case 1:  MakeCRC16(mpbOutBuff1 + bOffset, wSize);  break;
    case 2:  MakeCRC16(mpbOutBuff2 + bOffset, wSize);  break;
    case 3:  MakeCRC16(mpbOutBuff3 + bOffset, wSize);  break;
    default: ASSERT(false);
  }
}


void    MakeCRC16InBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  MakeCRC16(mpbInBuff0 + bOffset, wSize);  break;
    case 1:  MakeCRC16(mpbInBuff1 + bOffset, wSize);  break;
    case 2:  MakeCRC16(mpbInBuff2 + bOffset, wSize);  break;
    case 3:  MakeCRC16(mpbInBuff3 + bOffset, wSize);  break;
    default: ASSERT(false);
  }
}



#ifndef SKIP_S

void    MakeCrcSOutBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  MakeCrcS(mpbOutBuff0 + bOffset, wSize);  break;
    case 1:  MakeCrcS(mpbOutBuff1 + bOffset, wSize);  break;
    case 2:  MakeCrcS(mpbOutBuff2 + bOffset, wSize);  break;
    case 3:  MakeCrcS(mpbOutBuff3 + bOffset, wSize);  break;
    default: ASSERT(false);
  }
}


void    MakeCrcSInBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  MakeCrcS(mpbInBuff0 + bOffset, wSize);  break;
    case 1:  MakeCrcS(mpbInBuff1 + bOffset, wSize);  break;
    case 2:  MakeCrcS(mpbInBuff2 + bOffset, wSize);  break;
    case 3:  MakeCrcS(mpbInBuff3 + bOffset, wSize);  break;
    default: ASSERT(false);
  }
}

#endif



void    MakeCRCElsInBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  MakeCrcEls(mpbInBuff0 + bOffset, wSize);  break;
    case 1:  MakeCrcEls(mpbInBuff1 + bOffset, wSize);  break;
    case 2:  MakeCrcEls(mpbInBuff2 + bOffset, wSize);  break;
    case 3:  MakeCrcEls(mpbInBuff3 + bOffset, wSize);  break;
    default: ASSERT(false);
  }
}



#ifndef SKIP_V

uchar   MakeCrcVOutBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  return MakeCrcV(mpbOutBuff0 + bOffset, wSize);
    case 1:  return MakeCrcV(mpbOutBuff1 + bOffset, wSize);
    case 2:  return MakeCrcV(mpbOutBuff2 + bOffset, wSize);
    case 3:  return MakeCrcV(mpbOutBuff3 + bOffset, wSize);
    default: ASSERT(false); return 0;
  }
}


uchar   MakeCrcVInBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  return MakeCrcV(mpbInBuff0 + bOffset, wSize);
    case 1:  return MakeCrcV(mpbInBuff1 + bOffset, wSize);
    case 2:  return MakeCrcV(mpbInBuff2 + bOffset, wSize);
    case 3:  return MakeCrcV(mpbInBuff3 + bOffset, wSize);
    default: ASSERT(false); return 0;
  }
}

#endif
