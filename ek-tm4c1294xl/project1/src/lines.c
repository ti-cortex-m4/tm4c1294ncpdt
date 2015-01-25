/*------------------------------------------------------------------------------
LINES.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "keyboard.h"
#include        "display.h"
#include        "engine.h"



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
  dwBuffC = 0;

  while (ibBeg <= ibEnd)
    dwBuffC = dwBuffC*10 + ToChar( szHi[ibBeg++] );

  return(dwBuffC);
}


ulong   GetLong(uchar  ibBeg, uchar  ibEnd)
{
  dwBuffC = 0;

  while (ibBeg <= ibEnd)
    dwBuffC = dwBuffC*10 + ToChar( szLo[ibBeg++] );

  return(dwBuffC);
}


uint    GetInt(uchar  ibBeg, uchar  ibEnd)
{
  wBuffD = 0;

  while (ibBeg <= ibEnd)
    wBuffD = wBuffD*10 + ToChar( szLo[ibBeg++] );

  return(wBuffD);
}


uchar   GetChar(uchar  ibBeg, uchar  ibEnd)
{
  wBuffD = GetInt(ibBeg,ibEnd);
  
  if (wBuffD / 0x100 == 0) 
    return(wBuffD % 0x100);
  else 
    return(0xFF);
}            


real    *PGetReal(uchar  ibBeg, uchar  ibEnd)
{
  reBuffB = 0;

  while (ibBeg <= ibEnd)
    reBuffB = reBuffB*10 + ToChar( szLo[ibBeg++] );

  return( &reBuffB );
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
