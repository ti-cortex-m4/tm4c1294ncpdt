/*------------------------------------------------------------------------------
DECRET.C

  Ïðàâèëà ïåðåõîäà íà ñåçîííîå âðåìÿ
------------------------------------------------------------------------------*/

#include        <string.h>
#include        "main.h"
#include        "memory/mem_settings.h"
#include        "timedate.h"
#include        "hardware/rtc.h"



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
}



void    ResetDecret(void)
{
  deDecret = DEC_NONE;
  MakeDecret();
}
