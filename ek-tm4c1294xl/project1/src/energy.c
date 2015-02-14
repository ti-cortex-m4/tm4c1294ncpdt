/*------------------------------------------------------------------------------
ENERGY.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "engine.h"
#include        "memory/mem_factors.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_energy_spec.h"
#include        "memory/mem_groups.h"
#include        "memory/mem_tariffs.h"
#include        "memory/mem_realtime.h"
#include        "memory/mem_graph3.h"
#include        "digitals/digitals.h"
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



ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCanal, uchar  ibTariff) {
  return( &mpimT[ibCanal].mpdwImp[ibTariff] );
}



ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCanal) {
uchar   i;

  dwBuffC = 0;
  for (i=0; i<bTARIFFS; i++)
    dwBuffC += *PGetCanImp(mpimT,ibCanal,i);

  return( &dwBuffC );
}


/*
// рассчитать групповое значение на основе канального массива unsigned int (трЄхминутна€ мощность)
real    *PGetGrpMntInt2Real(uint  *mpwT, uchar  ibGroup, uchar  bMul)
{
uchar   i,j;

  reBuffA = 0;
  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    j = GetGroupsNodeCanal(ibGroup,i);
    reBuffB = *PGetCanReal(mpreValueEngMnt,j) * *PGetCanInt(mpwT,j);

    if (GetGroupsNodeSign(ibGroup,i) == 0)
      reBuffA += reBuffB;
    else
      reBuffA -= reBuffB;
  }

  reBuffA *= bMul;
  return( &reBuffA );
}


// рассчитать групповое значение на основе канального массива unsigned int (трЄхминутна€ мощность)
real    *PGetCanMntInt2Real(uint  *mpwT, uchar  ibCanal, uchar  bMul)
{
  reBuffA = *PGetCanReal(mpreValueEngMnt,ibCanal) * *PGetCanInt(mpwT,ibCanal);

  reBuffA *= bMul;
  return( &reBuffA );
}



// рассчитать групповое значение на основе канального массива unsigned int (получасова€ мощность)
real    *PGetGrpHouInt2Real(uint  *mpwT, uchar  ibGroup, uchar  bMul)
{
uchar   i,j;

  reBuffA = 0;
  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    j = GetGroupsNodeCanal(ibGroup,i);

    if (*PGetCanInt(mpwT,j) == 0xFFFF)
      reBuffB = 0;
    else
      reBuffB = *PGetCanReal(mpreValueEngHou,j) * *PGetCanInt(mpwT,j);

    if (GetGroupsNodeSign(ibGroup,i) == 0)
      reBuffA += reBuffB;
    else
      reBuffA -= reBuffB;
  }

  reBuffA *= bMul;
  return( &reBuffA );
}


// рассчитать канальное значение на основе канального массива unsigned int (получасова€ мощность)
real    *PGetCanHouInt2Real(uint  *mpwT, uchar  ibCanal, uchar  bMul)
{
  if (*PGetCanInt(mpwT,ibCanal) == 0xFFFF)
    reBuffA = 0;
  else
    reBuffA = *PGetCanReal(mpreValueEngHou,ibCanal) * *PGetCanInt(mpwT,ibCanal);

  reBuffA *= bMul;
  return( &reBuffA );
}


real    *PGetPowGrpHouCurr(uchar  ibGroup, uchar  bMul)
{
uchar   i,j;

  j = (tiCurr.bMinute % 30) / 3;
  if (j == 0) j = 10;

  reBuffX = 0;
  for (i=1; i<=j; i++)
    reBuffX += *PGetGrpMntInt2Real(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], ibGroup, bMul);

  reBuffA = 10*reBuffX/j;

  return( &reBuffA );
}


real    *PGetPowCanHouCurr(uchar  ibCanal, uchar  bMul)
{
uchar   i,j;

  j = (tiCurr.bMinute % 30) / 3;
  if (j == 0) j = 10;

  reBuffX = 0;
  for (i=1; i<=j; i++)
    reBuffX += *PGetCanMntInt2Real(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], ibCanal, bMul);

  reBuffA = 10*reBuffX/j;

  return( &reBuffA );
}



// рассчитать групповое значение на основе канального массива impulse (суточна€ и мес€чна€ энерги€)
real    *PGetGrpImp2RealEng(impulse  *mpimT, uchar  ibGroup, uchar  bMask)
{
uchar   i,j;

  reBuffA = 0;
  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    j = GetGroupsNodeCanal(ibGroup,i);

    dwBuffC = 0;

    if ((bMask & 0x01) != 0)
      dwBuffC += *PGetCanImp(mpimT,j,0);
    if ((bMask & 0x02) != 0)
      dwBuffC += *PGetCanImp(mpimT,j,1);
    if ((bMask & 0x04) != 0)
      dwBuffC += *PGetCanImp(mpimT,j,2);
    if ((bMask & 0x08) != 0)
      dwBuffC += *PGetCanImp(mpimT,j,3);

    reBuffB = *PGetCanReal(mpreValueEngHou,j) * dwBuffC;

    if (GetGroupsNodeSign(ibGroup,i) == 0)
      reBuffA += reBuffB;
    else
      reBuffA -= reBuffB;
  }

  return( &reBuffA );
}



// рассчитать канальное значение на основе канального массива impulse (суточна€ и мес€чна€ энерги€)
real    *PGetCanImp2RealEng(impulse  *mpimT, uchar  ibCanal, uchar  bMask)
{
  dwBuffC = 0;

  if ((bMask & 0x01) != 0)
    dwBuffC += *PGetCanImp(mpimT,ibCanal,0);
  if ((bMask & 0x02) != 0)
    dwBuffC += *PGetCanImp(mpimT,ibCanal,1);
  if ((bMask & 0x04) != 0)
    dwBuffC += *PGetCanImp(mpimT,ibCanal,2);
  if ((bMask & 0x08) != 0)
    dwBuffC += *PGetCanImp(mpimT,ibCanal,3);

  reBuffA = *PGetCanReal(mpreValueEngHou,ibCanal) * dwBuffC;

  return( &reBuffA );
}



// рассчитывает импульсы дл€ выбранного интервала
void    MakeImpSpec(impulse  *mpimT)
{
uchar   j;

  j = mpibEngPrevTariff[ tiAlt.bHour*2 + tiAlt.bMinute/30 ];

  dwBuffC  = *PGetCanImp(mpimT,ibCan,j);

  if (*PGetCanInt(mpwImpHouCanSpec, ibCan) != 0xFFFF)
    dwBuffC += *PGetCanInt(mpwImpHouCanSpec, ibCan);

  mpimT[ibCan].mpdwImp[j] = dwBuffC;
}
// требует предварительной установки переменной tiAlt


// рассчитывает импульсы дл€ выбранного интервала: во избежание двойного сложени€
void    MakeImpSpec_Winter(impulse  *mpimT)
{
uchar   j;

  j = mpibEngPrevTariff[ tiAlt.bHour*2 + tiAlt.bMinute/30 ];

  dwBuffC  = *PGetCanImp(mpimT,ibCan,j);

  dwBuffC -= *PGetCanInt(mpwImpHouCanSpec, ibCan);

  mpimT[ibCan].mpdwImp[j] = dwBuffC;
}
// требует предварительной установки переменной tiAlt
*/


// добавл€ем к канальному массиву impulse (по текущему тарифу дл€ энергии)
void    AddCanImpEng(impulse  *mpimT, uchar  ibCanal)
{
uchar   i;

  i = tiPrev.bHour*2 + tiPrev.bMinute/30;
  mpimT[ibCanal].mpdwImp[ mpibEngCurrTariff[i] ] += wBuffD;
}



// рассчитать показани€ счЄтчиков по приращению импульсов
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



void    MakeImpulse(void)
{
uchar  ibCan;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (mpboUsedNodes[ibCan] == false) continue;

    if (GetDigitalDevice(ibCan) == 0)
    {
      wBuffD = *PGetCanInt(mpwImpCurrMntCan,ibCan);
      mpwImpHouCan[ibSoftHou][ibCan] += wBuffD;

      AddCanImpEng(mpimDayCan[ibSoftDay], ibCan);
      AddCanImpEng(mpimMonCan[ibSoftMon], ibCan);
      AddCanImpEng(mpimAbsCan,            ibCan);
    }
  }
}


void    MakeImpulseSpec(time  *ptiOldDay, time  *ptiOldMon)
{
uchar  ibCan;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (mpboUsedNodes[ibCan] == false) continue;

    if (GetDigitalDevice(ibCan) == 0)
    {
      wBuffD = *PGetCanInt(mpwImpCurrMntCan,ibCan);
      mpwImpHouCan[ibSoftHou][ibCan] += wBuffD;

      AddCanImpEng(mpimDayCan[ibSoftDay], ibCan);
      AddCanImpEng(mpimMonCan[ibSoftMon], ibCan);
      AddCanImpEng(mpimAbsCan,            ibCan);

      if ((ptiOldDay->bYear  == tiCurr.bYear)  &&
          (ptiOldDay->bMonth == tiCurr.bMonth) &&
          (ptiOldDay->bDay   == tiCurr.bDay))
        AddCanImpEng(mpimDayCanSpec, ibCan);

      if ((ptiOldMon->bYear  == tiCurr.bYear)  &&
          (ptiOldMon->bMonth == tiCurr.bMonth))
        AddCanImpEng(mpimMonCanSpec, ibCan);
    }
  }
}
