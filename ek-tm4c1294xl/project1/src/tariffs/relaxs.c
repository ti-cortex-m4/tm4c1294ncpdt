/*------------------------------------------------------------------------------
RELAXS.C

 Праздники
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../flash/files.h"
#include        "../timedate.h"
#include        "tariffs.h"
#include        "relaxs.h"



file const              flRelaxsFlag = {DF_RELAXS_FLAG, &boRelaxsFlag, sizeof(boolean), FOR_DEFAULT};
file const              flRelaxsTariff = {DF_RELAXS_TARIFF, &ibRelaxsTariff, sizeof(uchar), FOR_DEFAULT};
file const              flRelaxs = {DF_RELAXS_TARIFF, &reRelaxs, sizeof(relaxs), FOR_DEFAULT};



void    InitRelaxs(void)
{
	LoadFile(&flRelaxsFlag);
	LoadFile(&flRelaxsTariff);
	LoadFile(&flRelaxs);
}


void    ResetRelaxs(void)
{
  boRelaxsFlag = FALSE;
  SaveFile(&flRelaxsFlag);

  ibRelaxsTariff = 1;
  SaveFile(&flRelaxsTariff);

  memset(&reRelaxs, 0, sizeof(relaxs));
	SaveFile(&flRelaxs);
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

	SaveFile(&flRelaxs);
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
uchar   GetModeAlt(void)
{
uchar  i;

  if (bTariffsMode == 0)                // без учёта выходных и праздничных дней
    return(0);                          // будни

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);

    if ((tiRelax.bDay   == tiAlt.bDay) &&
        (tiRelax.bMonth == tiAlt.bMonth)) 
      return(tiRelax.bSecond);          // тип текущего дня определяется по списку праздников
  }

  i = GetWeekdayYMD(tiAlt.bYear, tiAlt.bMonth, tiAlt.bDay);

  if (i < 5)  return(0);                // будни
  else 
  if (i == 5) return(1);                // суббота
  else        return(2);                // воскресенье
}
// требует предварительной установки переменной tiAlt
