/*------------------------------------------------------------------------------
MAX_POWER!C

 Максимумы мощности
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_tariffs.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_energy_spec.h"
#include "../realtime/realtime.h"
#include "../energy.h"



void    SetGrpMaxPow(power  *mppoT, uchar  ibGrp, uchar  ibTar, value  *pva)
{
  ASSERT(ibGrp < bGROUPS);
  ASSERT(ibTar < bTARIFFS);
  mppoT[ibGrp].mpmaMax[ibTar] = *pva;
}


float   GetGrpMaxPowReal(power  *mppoT, uchar  ibGrp, uchar  ibTar)
{
  ASSERT(ibGrp < bGROUPS);
  ASSERT(ibTar < bTARIFFS);
  return mppoT[ibGrp].mpmaMax[ibTar].reSelf;
}


time    GetGrpMaxPowTime(power  *mppoT, uchar  ibGrp, uchar  ibTar)
{
  ASSERT(ibGrp < bGROUPS);
  ASSERT(ibTar < bTARIFFS);
  return mppoT[ibGrp].mpmaMax[ibTar].tiSelf;
}



// находит индекс тарифа с наибольшим значением value из всех тарифов
uchar   GetGrpMaxPowIndex(power  *mppoT, uchar  ibGrp)
{
uchar  i,j;

  j = 0;
  for (i=0; i<bTARIFFS; i++)
  {
    if (GetGrpMaxPowReal(mppoT,ibGrp,i) >=
        GetGrpMaxPowReal(mppoT,ibGrp,j))
      j = i;
  }

  return(j);
}



void    MakeMaxPow(power  *mppoT)
{
uchar   g;
float  	re;
value   va;

  uchar i = tiPrev.bHour*2 + tiPrev.bMinute/30;
  uchar t = mpibPowCurrTariff[i];

  for (g=0; g<bGROUPS; g++)
  {
    re = GetGrpHouInt2Real(mpwImpHouCan[ ibSoftHou ],g,2);
    if (re >= GetGrpMaxPowReal(mppoT,g,t))
    {
      va.reSelf = re;
      va.tiSelf = tiPrev;
      SetGrpMaxPow(mppoT,g,t,&va);
    }
  }
}


void    MakeMaxPowSpec(power  *mppoT, uchar  ibGrp, time  ti)
{
float  	re;
value   va;

  uchar i = ti.bHour*2 + ti.bMinute/30;
  uchar t = mpibPowPrevTariff[i];

  re = GetGrpHouInt2Real(mpwImpHouCanSpec,ibGrp,2);
  if (re >= GetGrpMaxPowReal(mppoT,ibGrp,t))
  {
    va.reSelf = re;
    va.tiSelf = ti;
    SetGrpMaxPow(mppoT,ibGrp,t,&va);
  }
}


// расчёт максимумов мощности за текущие сутки и месяц
void    MakeMaxPowAll(void)
{
  MakeMaxPow( mppoDayGrp[ibSoftDay] );
  MakeMaxPow( mppoMonGrp[ibSoftMon] );
}
