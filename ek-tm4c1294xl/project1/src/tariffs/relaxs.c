/*------------------------------------------------------------------------------
RELAXS.C

 Праздники
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_tariffs.h"
#include "../nvram/cache.h"
#include "../time/timedate.h"
#include "tariffs.h"
#include "relaxs.h"



cache const             chRelaxsFlag = {RELAXS_FLAG, &boRelaxsFlag, sizeof(bool)};
cache const             chRelaxsTariff = {RELAXS_TARIFF, &ibRelaxsTariff, sizeof(uchar)};
cache const             chRelaxs = {RELAXS_TARIFF, &reRelaxs, sizeof(relaxs)};



void    InitRelaxs(void)
{
  LoadCache(&chRelaxsFlag);
  LoadCache(&chRelaxsTariff);
  LoadCache(&chRelaxs);
}


void    ResetRelaxs(void)
{
  boRelaxsFlag = false;
  SaveCache(&chRelaxsFlag);

  ibRelaxsTariff = 1;
  SaveCache(&chRelaxsTariff);

  memset(&reRelaxs, 0, sizeof(relaxs));
  SaveCache(&chRelaxs);
}


void    DefaultRelaxs(void)
{
static uchar const  mpRelaxs[8*3] = {
	1,  1,  2,
  2,  1,  2,
  7,  1,  2,
  8,  3,  2,
  1,  5,  2,
  9,  5,  2,
  7, 11,  2,
 25, 12,  2
};

uchar  i, j;

  memset(&reRelaxs, 0, sizeof(relaxs));

  SetRelaxSize(0);

  j = 0;
  for (i=0; i<sizeof(mpRelaxs)/3; i++)
  {
    tiRelax.bDay    = mpRelaxs[j++];
    tiRelax.bMonth  = mpRelaxs[j++];
    tiRelax.bSecond = mpRelaxs[j++];  // тип праздника: будни, суббота, воскресенье

    SetRelaxDate(i);
    SetRelaxSize(GetRelaxSize() + 1);
  }

  SaveCache(&chRelaxs);
}



uchar   GetRelaxSize(void)
{
  return reRelaxs.bSize;
}


void    SetRelaxSize(uchar  bSize)
{
  reRelaxs.bSize = bSize;
}



void    GetRelaxDate(uchar  ibRelax)
{
  tiRelax = reRelaxs.mptiDate[ibRelax];
}


void    SetRelaxDate(uchar  ibRelax)
{
  reRelaxs.mptiDate[ibRelax] = tiRelax;
}



// определяет тип дня недели
uchar   GetMode(time  ti)
{
uchar  i;

  if (bOldTrfMode == 0)                // без учёта выходных и праздничных дней
    return(0);                          // будни

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);

    if ((tiRelax.bDay   == ti.bDay) &&
        (tiRelax.bMonth == ti.bMonth))
      return(tiRelax.bSecond);          // тип текущего дня определяется по списку праздников
  }

  i = GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay);

  if (i < 5)  return(0);                // будни
  else 
  if (i == 5) return(1);                // суббота
  else        return(2);                // воскресенье
}
