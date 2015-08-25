/*------------------------------------------------------------------------------
DECRET.C // TODO: сохранять количество переходов отдельно + события

  Правила перехода на сезонное время
------------------------------------------------------------------------------*/

#include        <string.h>
#include "../main.h"
#include "../memory/mem_settings.h"
#include "../nvram/cache.h"
#include "timedate.h"
#include "rtc.h"
#include "decret.h"



cache const             chDecret = {DECRET, &deDecret, sizeof(decret)};
cache const             chSummer = {SUMMER, &tiSummer, sizeof(time)};
cache const             chWinter = {WINTER, &tiWinter, sizeof(time)};



void    MakeDecret(void)
{
  if (deDecret == DEC_NONE)
  {
    memset(&tiSummer, 0, sizeof(time));
    memset(&tiWinter, 0, sizeof(time));
  }
  else if (deDecret == DEC_AUTO)
  {
  	uchar  bYear = GetCurrTimeDate()->bYear;
    tiSummer = *GetDecretDateYM(bYear, 3);
    tiWinter = *GetDecretDateYM(bYear, 10);
  }

  SaveCache(&chDecret);

  SaveCache(&chSummer);
  SaveCache(&chWinter);
}



void    InitDecret(void)
{
  LoadCache(&chDecret);

  LoadCache(&chSummer);
  LoadCache(&chWinter);
}


void    ResetDecret(void)
{
  deDecret = DEC_NONE;
  MakeDecret();
}



bool    IsWinter(time  ti)
{
  return((ti.bDay   == tiWinter.bDay)   &&
         (ti.bMonth == tiWinter.bMonth) &&
         (ti.bHour  <= 3));
}


// возвращает день недели (1: зимнее время, 0: летнее время)
uchar   GetSeasonMD(uchar  bMonth, uchar  bDay)
{
  uint i = GetDayIndexMD(bMonth, bDay);

  if (i >= GetDayIndexMD(tiWinter.bMonth, tiWinter.bDay)) return(1);
  if (i >= GetDayIndexMD(tiSummer.bMonth, tiSummer.bDay)) return(0);

  return(1);
}



// возвращает день недели (1: зимнее время, 0: летнее время)
uchar   GetSeason(time  ti)
{
  uint i = GetDayIndexYMD(ti.bYear, ti.bMonth, ti.bYear);

  if (i >= GetDayIndexYMD(tiWinter.bYear, tiWinter.bMonth, tiWinter.bYear)) return(1);
  if (i >= GetDayIndexYMD(tiSummer.bYear, tiSummer.bMonth, tiSummer.bYear)) return(0);

  return(1);
}


// возвращает день недели (1: зимнее время, 0: летнее время)
uchar   GetSeasonCurr(void)
{
  return GetSeason(*GetCurrTimeDate());
}
