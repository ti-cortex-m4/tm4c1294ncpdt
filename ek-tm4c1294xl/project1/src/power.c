/*------------------------------------------------------------------------------
POWER.C

 Максимумы мощности
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_realtime.h"
#include        "memory/mem_tariffs.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_energy_spec.h"
#include        "realtime/realtime.h"
#include        "engine.h"
#include        "energy.h"



void    SetGrpMaxPow(power  *mppoT, uchar  ibGrp, uchar  ibTar, maximum  *pma)
{  
	ASSERT(ibGrp < bGROUPS);
	ASSERT(ibTar < bTARIFFS);
  mppoT[ibGrp].mpmaMax[ibTar] = *pma;
}


real    GetGrpMaxPowReal(power  *mppoT, uchar  ibGrp, uchar  ibTar)
{  
	ASSERT(ibGrp < bGROUPS);
	ASSERT(ibTar < bTARIFFS);
  return mppoT[ibGrp].mpmaMax[ibTar].rePow;
}


time    GetGrpMaxPowTime(power  *mppoT, uchar  ibGrp, uchar  ibTar)
{
	ASSERT(ibGrp < bGROUPS);
	ASSERT(ibTar < bTARIFFS);
  return mppoT[ibGrp].mpmaMax[ibTar].tiNow;
}



// находит индекс тарифа с наибольшим значением maximum из всех тарифов
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



// рассчитывает маскимумы мощности для выбранного интервала
void    MakeMaxPow(power  *mppoT)
{
uchar   g,t;
real   	re;
static maximum maAlt;

  t = mpibPowCurrTariff[tiPrev.bHour*2 + tiPrev.bMinute/30];

  for (g=0; g<bGROUPS; g++)
  {
    re = *PGetGrpHouInt2Real(mpwImpHouCan[ ibSoftHou ],g,2);

    if (re >= GetGrpMaxPowReal(mppoT,g,t))
    {
      maAlt.rePow = re;
      maAlt.tiNow = tiPrev;
      SetGrpMaxPow(mppoT,g,t,&maAlt);
    }
  }
}


void    MakeMaxPowSpec(power  *mppoT, uchar  ibGrp, time  *ptiT)
{
uchar		t;
real   	re;
static maximum maAlt;

  t = mpibPowPrevTariff[ ptiT->bHour*2 + ptiT->bMinute/30 ];

  re = *PGetGrpHouInt2Real(mpwImpHouCanSpec,ibGrp,2);

  if (re >= GetGrpMaxPowReal(mppoT,ibGrp,t))
  {
    maAlt.rePow = re;
    maAlt.tiNow = *ptiT;
    SetGrpMaxPow(mppoT,ibGrp,t,&maAlt);
  }
}


void    MakeMaxPowAll(void)
{       
  MakeMaxPow( mppoDayGrp[ibSoftDay] );
  MakeMaxPow( mppoMonGrp[ibSoftMon] );
}
