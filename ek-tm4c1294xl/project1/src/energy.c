/*------------------------------------------------------------------------------
ENERGY.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "engine.h"



// прочитать из канального массива unsigned int
uint    *PGetCanInt(uint  *mpwT, uchar  ibCanal)
{
  return( &mpwT[ibCanal] );
}


// записать в канальный массив unsigned int
void    SetCanInt(uint  *mpwT, uchar  ibCanal, uint  wT)
{
  mpwT[ibCanal] = wT;
}



// прочитать из канального массива unsigned int
ulong   *PGetCanLong(ulong  *mpdwT, uchar  ibCanal)
{
  return( &mpdwT[ibCanal] );
}


// записать в канальный массив unsigned int из dwBuffC
void    SetCanLong(ulong  *mpdwT, uchar  ibCanal)
{
  mpdwT[ibCanal] = dwBuffC;
}



// прочитать из канального массива real
real    *PGetCanReal(real  *mpreT, uchar  ibCanal)
{
  return( &mpreT[ibCanal] );
}


// записать в канальный массив real из reBuffA
void    SetCanReal(real  *mpreT, uchar  ibCanal)
{
  mpreT[ibCanal] = reBuffA;
}



// прочитать из канального массива impulse (по заданному тарифу)
ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCanal, uchar  ibTariff)
{
  return( &mpimT[ibCanal].mpdwImp[ibTariff] );
}


// прочитать из канального массива impulse (по всем тарифам)
ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCanal)
{
uchar   i;

  dwBuffC = 0;
  for (i=0; i<bTARIFFS; i++)
    dwBuffC += *PGetCanImp(mpimT,ibCanal,i);

  return( &dwBuffC );
}
