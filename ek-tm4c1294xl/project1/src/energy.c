/*------------------------------------------------------------------------------
ENERGY.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "engine.h"
#include        "mem_canals.h"
#include        "memory/mem_energy.h"
#include        "mem_realtime.h"
#include        "memory/mem_graph3.h"
#include        "sensors.h"



uint    *PGetCanInt(uint  *mpwT, uchar  ibCanal) {
  return( &mpwT[ibCanal] );
}


void    SetCanInt(uint  *mpwT, uchar  ibCanal, uint  wT) {
  mpwT[ibCanal] = wT;
}



ulong   *PGetCanLong(ulong  *mpdwT, uchar  ibCanal) {
  return( &mpdwT[ibCanal] );
}


void    SetCanLong(ulong  *mpdwT, uchar  ibCanal) {
  mpdwT[ibCanal] = dwBuffC;
}



real    *PGetCanReal(real  *mpreT, uchar  ibCanal) {
  return( &mpreT[ibCanal] );
}


void    SetCanReal(real  *mpreT, uchar  ibCanal) {
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



// рассчитать показания счётчиков по приращению импульсов
real    *PGetCounterOld(uchar  ibCanal)
{
  if (GetDigitalDevice(ibCanal) == 19)
  {
    reBuffA = mpdwBase[ibCanal] * *PGetCanReal(mpreValueCntHou,ibCanal);
    reBuffA += *PGetCanReal(mpreCount,ibCanal);
  }
  else
  {
    reBuffA  = *PGetCanInt(mpwImpMntCan[ibSoftMnt],ibCanal) * *PGetCanReal(mpreValueCntMnt,ibCanal);
    reBuffA += *PGetCanImpAll(mpimAbsCan,ibCanal)           * *PGetCanReal(mpreValueCntHou,ibCanal);
    reBuffA += *PGetCanReal(mpreCount,ibCanal);
  }

  return( &reBuffA );
}
