/*------------------------------------------------------------------------------
POWER.C

 ћаксимумы мощности
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_realtime.h"
#include        "memory/mem_tariffs.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_energy_spec.h"
#include        "realtime/realtime.h"
#include        "engine.h"
#include        "energy.h"



void    SetGrpMaxPow(power  *mppoT, uchar  ibGroup, uchar  ibTariff)
{  
  mppoT[ibGroup].mpmaMax[ibTariff] = maAlt ;
}



real    *PGetGrpMaxPowReal(power  *mppoT, uchar  ibGroup, uchar  ibTariff)
{  
  return( &mppoT[ibGroup].mpmaMax[ibTariff].rePow );
}


time    *PGetGrpMaxPowTime(power  *mppoT, uchar  ibGroup, uchar  ibTariff)
{
  return( &mppoT[ibGroup].mpmaMax[ibTariff].tiNow );
}



// находит индекс тарифа с наибольшим значением maximum из всех тарифов
uchar   GetGrpMaxPowIndex(power  *mppoT, uchar  ibGroup)
{
uchar  i,j;

  j = 0;
  for (i=0; i<bTARIFFS; i++)
  {
    if (*PGetGrpMaxPowReal(mppoT,ibGroup,i) >=
        *PGetGrpMaxPowReal(mppoT,ibGroup,j))
      j = i;
  }

  return(j);
}



// рассчитывает маскимумы мощности дл€ выбранного интервала
void    MakeMaxPowNow(power  *mppoT)
{
uchar  i,j;

  j = mpibPowCurrTariff[tiPrev.bHour*2 + tiPrev.bMinute/30];

  for (i=0; i<bGROUPS; i++)
  {
    reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ ibSoftHou ],i,2);

    if (reBuffA >= *PGetGrpMaxPowReal(mppoT,i,j))
    {
      maAlt.rePow = reBuffA;
      maAlt.tiNow = tiPrev;
      SetGrpMaxPow(mppoT,i,j);
    }
  }
}


/*
// рассчитывает максимумы мощности дл€ выбранного интервала
void    MakeMaxPowSpec(power  *mppoT)
{
uchar   j;

  j = mpibPowPrevTariff[ tiAlt.bHour*2 + tiAlt.bMinute/30 ];

  reBuffA = *PGetGrpHouInt2Real(mpwImpHouCanSpec,ibGrp,2);

  if (reBuffA >= *PGetGrpMaxPowReal(mppoT,ibGrp,j))
  {
    maAlt.rePow = reBuffA;
    maAlt.tiNow = tiAlt;
    SetGrpMaxPow(mppoT,ibGrp,j);
  }
}
// требует предварительной установки переменной tiAlt 
*/


// рассчитывает маскимумы мощности дл€ всех интервалов
void    MakeAllMaxPowNow(void)
{       
  MakeMaxPowNow( mppoDayGrp[ibSoftDay] );
  MakeMaxPowNow( mppoMonGrp[ibSoftMon] );
}
