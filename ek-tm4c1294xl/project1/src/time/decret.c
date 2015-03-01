/*------------------------------------------------------------------------------
DECRET.C

  ѕравила перехода на сезонное врем€
------------------------------------------------------------------------------*/

#include        <string.h>
#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../flash/files.h"
#include        "timedate.h"
#include        "rtc.h"
#include        "decret.h"



static boolean SaveDecret(void)
{
  OpenOut(FLS_DECRET);
  ClearOut();

  if (Save(&deDecret, sizeof(uchar)) == FALSE) return FALSE;

  if (Save(&tiSummer, sizeof(time)) == FALSE) return FALSE;
  if (Save(&tiWinter, sizeof(time)) == FALSE) return FALSE;

  return CloseOut();
}


static boolean LoadDecret(void)
{
  OpenIn(FLS_DECRET);

  if (Load(&deDecret, sizeof(uchar)) == FALSE) return FALSE;

  if (Load(&tiSummer, sizeof(time)) == FALSE) return FALSE;
  if (Load(&tiWinter, sizeof(time)) == FALSE) return FALSE;

  return TRUE;
}



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

  SaveDecret();
}



void    InitDecret(void)
{
	LoadDecret();
}


void    ResetDecret(void)
{
  deDecret = DEC_NONE;
  MakeDecret();
}

// TODO: сохран€ть количество переходов отдельно + событи€
