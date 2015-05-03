/*------------------------------------------------------------------------------
LINES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../keyboard/keyboard.h"
#include "../engine.h"
#include "display.h"



//                                         0123456789ABCDEF
uchar const             szDigits[0x10]  = "0123456789ABCDEF";



void    ShiftHi(uchar  ibBeg, uchar  ibEnd)
{
  while (ibBeg < ibEnd)
  {
    szHi[ibBeg] = szHi[ibBeg+1];
    ibBeg++;
  }

  szHi[ibBeg] = szDigits[bKey];  
}


void    ShiftLo(uchar  ibBeg, uchar  ibEnd)
{
  while (ibBeg < ibEnd)
  {
    szLo[ibBeg] = szLo[ibBeg+1];
    ibBeg++;
  }

  szLo[ibBeg] = szDigits[bKey];  
}



uchar   ToChar(uchar  chT)
{
  if ((chT >= '0') && (chT <= '9')) 
    return(chT - '0');
  else
    return(0);
}



ulong   GetLongHi(uchar  ibBeg, uchar  ibEnd)
{
ulong	dw;

  dw = 0;

  while (ibBeg <= ibEnd)
    dw = dw*10 + ToChar( szHi[ibBeg++] );

  return dw;
}


ulong   GetLongLo(uchar  ibBeg, uchar  ibEnd)
{
ulong	dw;

  dw = 0;

  while (ibBeg <= ibEnd)
    dw = dw*10 + ToChar( szLo[ibBeg++] );

  return dw;
}


uint    GetIntLo(uchar  ibBeg, uchar  ibEnd)
{
uint  w;

  w = 0;

  while (ibBeg <= ibEnd)
    w = w*10 + ToChar( szLo[ibBeg++] );

  return(w);
}


uchar   GetCharLo(uchar  ibBeg, uchar  ibEnd)
{
uint  w;

  w = GetIntLo(ibBeg,ibEnd);
  
  if (w / 0x100 == 0)
    return(w % 0x100);
  else 
    return(0xFF);
}            


real    GetRealLo(uchar  ibBeg, uchar  ibEnd)
{
real re;

  re = 0;

  while (ibBeg <= ibEnd)
    re = re*10 + ToChar( szLo[ibBeg++] );

  return re;
}



void    Hi(uchar  i, uchar  bT)
{
  szHi[i++] = szDigits[bT / 0x10];
  szHi[i]   = szDigits[bT % 0x10];
}


void    Lo(uchar  i, uchar  bT)
{
  szLo[i++] = szDigits[bT / 0x10];
  szLo[i]   = szDigits[bT % 0x10];
}



uchar   FromBCD(uchar  bT)
{
  return( (bT/16)*10 + (bT%16) );
}


uchar   ToBCD(uchar  bT)
{
  return( (bT/10)*16 + bT%10 );
}
