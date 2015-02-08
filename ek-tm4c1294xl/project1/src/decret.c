/*------------------------------------------------------------------------------
DECRET.C

  Правила перехода на сезонное время
------------------------------------------------------------------------------*/

#include        <string.h>
#include        "main.h"
#include        "memory/mem_settings.h"
#include        "timedate.h"
#include        "rtc.h"



void    MakeDecret(void)
{
  if (deDecret == DEC_NONE)
  {
    memset(&tiSummer, 0, sizeof(time));
    memset(&tiWinter, 0, sizeof(time));
  }
  else if (deDecret == DEC_AUTO)
  {
    tiSummer = *GetDecretDate(PGetCurrTimeDate(), 3);
    tiWinter = *GetDecretDate(PGetCurrTimeDate(), 10);
  }
}



void    ResetDecret(void)
{
  deDecret = DEC_NONE;
  MakeDecret();
}
