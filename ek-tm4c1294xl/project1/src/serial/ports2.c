/*------------------------------------------------------------------------------
PORTS2.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_serial0.h"
#include        "../memory/mem_serial1.h"
#include        "../memory/mem_serial2.h"
#include        "../memory/mem_serial3.h"
#include        "ports.h"


/*
uchar   GetOutBuff(uint  i)
{
  switch (ibPort)
  {
    case 0:  return( mpbOutBuff0[i] );  break;
    case 1:  return( mpbOutBuff1[i] );  break;
    case 2:  return( mpbOutBuff2[i] );  break;
    case 3:  return( mpbOutBuff3[i] );  break;
  }
}


void    SetOutBuff(uint  i, uchar  bT)
{
  switch (ibPort)
  {
    case 0:  mpbOutBuff0[i] = bT;  break;
    case 1:  mpbOutBuff1[i] = bT;  break;
    case 2:  mpbOutBuff2[i] = bT;  break;
    case 3:  mpbOutBuff3[i] = bT;  break;
  }
}



uchar   GetInBuff(uint  i)
{
  switch (ibPort)
  {
    case 0:  return( mpbInBuff0[i] );  break;
    case 1:  return( mpbInBuff1[i] );  break;
    case 2:  return( mpbInBuff2[i] );  break;
    case 3:  return( mpbInBuff3[i] );  break;
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
  }
}
*/

void    SetCountInBuff(uint  wT)
{
  switch (ibPort)
  {
    case 0:  cwInBuff0 = wT;  break;
    case 1:  cwInBuff1 = wT;  break;
    case 2:  cwInBuff2 = wT;  break;
    case 3:  cwInBuff3 = wT;  break;
  }
}

/*
void    InputMode(void)
{
  switch (ibPort)
  {
    case 0:  InputMode0();  break;
    case 1:  InputMode1();  break;
    case 2:  InputMode2();  break;
    case 3:  InputMode3();  break;
  }
}
*/
