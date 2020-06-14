/*------------------------------------------------------------------------------
PORTS2!C


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
#include "ports.h"



void    SetOutBuff(uint  i, uchar  bT)
{
  switch (ibPort)
  {
    case 0:  mpbOutBuff0[i] = bT;  break;
    case 1:  mpbOutBuff1[i] = bT;  break;
    case 2:  mpbOutBuff2[i] = bT;  break;
    case 3:  mpbOutBuff3[i] = bT;  break;
    default: ASSERT(false);
  }
}


void    SetInBuff(uint  i, uchar  bT)
{
  switch (ibPort)
  {
    case 0:  mpbInBuff0[i] = bT;  break;
    case 1:  mpbInBuff1[i] = bT;  break;
    case 2:  mpbInBuff2[i] = bT;  break;
    case 3:  mpbInBuff3[i] = bT;  break;
    default: ASSERT(false);
  }
}


void    SetIndexInBuff(uint  wT)
{
  switch (ibPort)
  {
    case 0:  iwInBuff0 = wT;  break;
    case 1:  iwInBuff1 = wT;  break;
    case 2:  iwInBuff2 = wT;  break;
    case 3:  iwInBuff3 = wT;  break;
    default: ASSERT(false);
  }
}


void    SetCountInBuff(uint  wT)
{
  switch (ibPort)
  {
    case 0:  cwInBuff0 = wT;  break;
    case 1:  cwInBuff1 = wT;  break;
    case 2:  cwInBuff2 = wT;  break;
    case 3:  cwInBuff3 = wT;  break;
    default: ASSERT(false);
  }
}


void    InputMode(void)
{
  switch (ibPort)
  {
    case 0:  InputMode0();  break;
    case 1:  InputMode1();  break;
    case 2:  InputMode2();  break;
    case 3:  InputMode3();  break;
    default: ASSERT(false);
  }
}



uchar*  OutBuffPtr(uchar  i)
{
  switch (ibPort)
  {
    case 0: return &mpbOutBuff0[i];
    case 1: return &mpbOutBuff1[i];
    case 2: return &mpbOutBuff2[i];
    case 3: return &mpbOutBuff3[i];
    default: ASSERT(false); return 0;
  }
}


uchar*  InBuffPtr(uchar  i)
{
  switch (ibPort)
  {
    case 0: return &mpbInBuff0[i];
    case 1: return &mpbInBuff1[i];
    case 2: return &mpbInBuff2[i];
    case 3: return &mpbInBuff3[i];
    default: ASSERT(false); return 0;
  }
}
