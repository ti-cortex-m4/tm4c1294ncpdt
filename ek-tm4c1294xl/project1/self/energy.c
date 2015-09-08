/*------------------------------------------------------------------------------
ENERGY.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_factors.h"
#include "memory/mem_energy.h"
#include "memory/mem_energy_spec.h"
#include "memory/mem_groups.h"
#include "memory/mem_tariffs.h"
#include "memory/mem_realtime.h"
#include "memory/mem_current.h"
#include "digitals/digitals.h"
#include "digitals/sensors.h"
#include "groups.h"
#include "energy.h"



ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCanal, uchar  ibTariff) {
  return( &mpimT[ibCanal].mpdwImp[ibTariff] );
}



ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCanal)
{
uchar   i;
static ulong   dw;

  dw = 0;
  for (i=0; i<bTARIFFS; i++)
    dw += *PGetCanImp(mpimT,ibCanal,i);

  return( &dw );
}



// рассчитывает групповое значение на основе канального массива uint (трЄхминутна€ мощность)
float   GetGrpMntInt2Real(uint  *mpwT, uchar  ibGrp, uchar  bMultiplier)
{
float   reA, reB;

  reA = 0;

  uchar i;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    uchar c = GetGroupsNodeCanal(ibGrp,i);
    reB = mpdbValueEngMnt[c] * mpwT[c];

    if (GetGroupsNodeSign(ibGrp,i) == 0)
      reA += reB;
    else
      reA -= reB;
  }

  reA *= bMultiplier;
  return reA;
}


// рассчитывает групповое значение на основе канального массива uint (трЄхминутна€ мощность)
float   GetCanMntInt2Real(uint  *mpwT, uchar  ibCan, uchar  bMultiplier)
{
float   re;

  re = mpdbValueEngMnt[ibCan] * mpwT[ibCan];

  re *= bMultiplier;
  return re;
}



// рассчитывает групповое значение на основе канального массива uint (получасова€ мощность)
float    GetGrpHouInt2Real(uint  *mpwT, uchar  ibGroup, uchar  bMultiplier)
{
float   reA, reB;

  reA = 0;

  uchar i;
  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    uchar c = GetGroupsNodeCanal(ibGroup,i);

    if (mpwT[c] == 0xFFFF)
      reB = 0;
    else
      reB = mpdbValueEngHou[c] * mpwT[c];

    if (GetGroupsNodeSign(ibGroup,i) == 0)
      reA += reB;
    else
      reA -= reB;
  }

  reA *= bMultiplier;
  return reA;
}


// рассчитывает канальное значение на основе канального массива uint (получасова€ мощность)
float   GetCanHouInt2Real(uint  *mpwT, uchar  ibCan, uchar  bMultiplier)
{
float   re;

  if (mpwT[ibCan] == 0xFFFF)
    re = 0;
  else
    re = mpdbValueEngHou[ibCan] * mpwT[ibCan];

  re *= bMultiplier;
  return re;
}



float   GetGrpImp2FloatEng(impulse  *mpimT, uchar  ibGrp, uchar  bMask)
{
float   flA, flB;
ulong   dw;

  flA = 0;

  uchar i;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    uchar c = GetGroupsNodeCanal(ibGrp,i);

    dw = 0;

    if ((bMask & 0x01) != 0)
      dw += *PGetCanImp(mpimT,c,0);
    if ((bMask & 0x02) != 0)
      dw += *PGetCanImp(mpimT,c,1);
    if ((bMask & 0x04) != 0)
      dw += *PGetCanImp(mpimT,c,2);
    if ((bMask & 0x08) != 0)
      dw += *PGetCanImp(mpimT,c,3);

    flB = (float)mpdbValueEngHou[c] * dw;

    if (GetGroupsNodeSign(ibGrp,i) == 0)
      flA += flB;
    else
      flA -= flB;
  }

  return flA;
}


double  GetGrpImp2DoubleEng(impulse  *mpimT, uchar  ibGrp, uchar  bMask)
{
double  dbA, dbB;
ulong   dw;

  dbA = 0;

  uchar i;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    uchar c = GetGroupsNodeCanal(ibGrp,i);

    dw = 0;

    if ((bMask & 0x01) != 0)
      dw += *PGetCanImp(mpimT,c,0);
    if ((bMask & 0x02) != 0)
      dw += *PGetCanImp(mpimT,c,1);
    if ((bMask & 0x04) != 0)
      dw += *PGetCanImp(mpimT,c,2);
    if ((bMask & 0x08) != 0)
      dw += *PGetCanImp(mpimT,c,3);

    dbB = (double)mpdbValueEngHou[c] * dw;

    if (GetGroupsNodeSign(ibGrp,i) == 0)
      dbA += dbB;
    else
      dbA -= dbB;
  }

  return dbA;
}


float   GetCanImp2FloatEng(impulse  *mpimT, uchar  ibCan, uchar  bMask)
{
float   fl;
ulong   dw;

  dw = 0;

  if ((bMask & 0x01) != 0)
    dw += *PGetCanImp(mpimT,ibCan,0);
  if ((bMask & 0x02) != 0)
    dw += *PGetCanImp(mpimT,ibCan,1);
  if ((bMask & 0x04) != 0)
    dw += *PGetCanImp(mpimT,ibCan,2);
  if ((bMask & 0x08) != 0)
    dw += *PGetCanImp(mpimT,ibCan,3);

  fl = (float)mpdbValueEngHou[ibCan] * dw;

  return fl;
}


double  GetCanImp2DoubleEng(impulse  *mpimT, uchar  ibCan, uchar  bMask)
{
double  db;
ulong   dw;

  dw = 0;

  if ((bMask & 0x01) != 0)
    dw += *PGetCanImp(mpimT,ibCan,0);
  if ((bMask & 0x02) != 0)
    dw += *PGetCanImp(mpimT,ibCan,1);
  if ((bMask & 0x04) != 0)
    dw += *PGetCanImp(mpimT,ibCan,2);
  if ((bMask & 0x08) != 0)
    dw += *PGetCanImp(mpimT,ibCan,3);

  db = (double)mpdbValueEngHou[ibCan] * dw;

  return db;
}


// рассчитывает импульсы дл€ выбранного интервала
void    MakeImpSpec(impulse  *mpimT, uchar  ibCan, time  ti)
{
  uchar i = ti.bHour*2 + ti.bMinute/30;
  uchar t = mpibEngPrevTariff[i];
  ulong dw = *PGetCanImp(mpimT,ibCan,t);

  if (mpwImpHouCanSpec[ibCan] != 0xFFFF)
    dw += mpwImpHouCanSpec[ibCan];

  mpimT[ibCan].mpdwImp[t] = dw;
}


// рассчитывает импульсы дл€ выбранного интервала: во избежание двойного сложени€
void    MakeImpSpec_Winter(impulse  *mpimT, uchar  ibCan, time  ti)
{
  uchar i = ti.bHour*2 + ti.bMinute/30;
  uchar t = mpibEngPrevTariff[i];
  ulong dw = *PGetCanImp(mpimT,ibCan,t);

  dw -= mpwImpHouCanSpec[ibCan];

  mpimT[ibCan].mpdwImp[t] = dw;
}



// добавл€ем к канальному массиву impulse (по текущему тарифу дл€ энергии)
void    AddCanImpEng(impulse  *mpimT, uchar  ibCanal, uchar  wImp)
{
  uchar i = tiPrev.bHour*2 + tiPrev.bMinute/30;
  uchar t = mpibEngCurrTariff[i];
  mpimT[ibCanal].mpdwImp[t] += wImp;
}



// расчитывает значени€ счЄтчиков дл€ текущего мес€ца
void    MakeCntMonCan(void)
{
  double db = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (GetDigitalDevice(c) == 0)
    {
      db  = *PGetCanImpAll(mpimAbsCan,c);
      db *= mpdbValueCntHou[c];
      db += mpdbCount[c];
    }
    else
    {
      db = mpdwBase[c] * mpdbValueCntHou[c];
      if (GetDigitalDevice(c) == 19) db += mpdbCount[c];
    }

    mpdbCntMonCan[ibSoftMon][c] = db;
  }
}


// рассчитывает показани€ счЄтчиков по приращению импульсов
double GetCntCurrImp(uchar  ibCan)
{
  double db = 0;

  if (GetDigitalDevice(ibCan) == 19)
  {
    db = mpdwBase[ibCan] * mpdbValueCntHou[ibCan];
    db += mpdbCount[ibCan];
  }
  else
  {
    db  = mpwImpMntCan[ibSoftMnt][ibCan] * mpdbValueCntMnt[ibCan];
    db += *PGetCanImpAll(mpimAbsCan,ibCan) * mpdbValueCntHou[ibCan];
    db += mpdbCount[ibCan];
  }

  return db;
}



void    MakeImpulse(void)
{
uchar  ibCan;
uint   w;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (mpfUsedNodes[ibCan] == false) continue;

    if (GetDigitalDevice(ibCan) == 0)
    {
      w = mpwImpMntCanCurr[ibCan];
      mpwImpHouCan[ibSoftHou][ibCan] += w;

      AddCanImpEng(mpimDayCan[ibSoftDay], ibCan, w);
      AddCanImpEng(mpimMonCan[ibSoftMon], ibCan, w);
      AddCanImpEng(mpimAbsCan,            ibCan, w);
    }
  }
}


void    MakeImpulseSpec(void)
{
uchar  ibCan;
uint   w;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (mpfUsedNodes[ibCan] == false) continue;

    if (GetDigitalDevice(ibCan) == 0)
    {
      w = mpwImpMntCanCurr[ibCan];
      mpwImpHouCan[ibSoftHou][ibCan] += w;

      AddCanImpEng(mpimDayCan[ibSoftDay], ibCan, w);
      AddCanImpEng(mpimMonCan[ibSoftMon], ibCan, w);
      AddCanImpEng(mpimAbsCan,            ibCan, w);

      if ((tiOldDay.bYear  == tiCurr.bYear)  &&
          (tiOldDay.bMonth == tiCurr.bMonth) &&
          (tiOldDay.bDay   == tiCurr.bDay))
        AddCanImpEng(mpimDayCanSpec, ibCan, w);

      if ((tiOldMon.bYear  == tiCurr.bYear)  &&
          (tiOldMon.bMonth == tiCurr.bMonth))
        AddCanImpEng(mpimMonCanSpec, ibCan, w);
    }
  }
}
