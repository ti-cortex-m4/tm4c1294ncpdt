/*------------------------------------------------------------------------------
DECRET.C // TODO: сохранять количество переходов отдельно + события

  Правила перехода на сезонное время
------------------------------------------------------------------------------*/

#include        <string.h>
#include "../main.h"
#include "../memory/mem_settings.h"
#include "../flash/files.h"
#include "timedate.h"
#include "rtc.h"
#include "decret.h"



file const              flDecret = {DECRET, &deDecret, sizeof(deDecret)};
file const              flSummer = {SUMMER, &tiSummer, sizeof(time)};
file const              flWinter = {WINTER, &tiWinter, sizeof(time)};



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

  SaveFile(&flDecret);
  SaveFile(&flSummer);
  SaveFile(&flWinter);
}



void    InitDecret(void)
{
  LoadFile(&flDecret);
  LoadFile(&flSummer);
  LoadFile(&flWinter);
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
uint    i;

  i = GetDayIndexMD(bMonth, bDay);

  if (i >= GetDayIndexMD(tiWinter.bMonth, tiWinter.bDay)) return(1);
  if (i >= GetDayIndexMD(tiSummer.bMonth, tiSummer.bDay)) return(0);

  return(1);
}
