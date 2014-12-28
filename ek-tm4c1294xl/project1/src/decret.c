/*------------------------------------------------------------------------------
DECRET.C

  Подпрограммы управления правилами перехода на сезонное время
------------------------------------------------------------------------------*/

#include        <string.h>
#include        "main.h"
#include        "mem_settings.h"
#include        "timedate.h"



void    MakeDecret(void)
{
  if (deDecret == DEC_NONE)
  {
    memset(&tiSummer, '\0', sizeof(time));
    memset(&tiWinter, '\0', sizeof(time));
  }
  else if (deDecret == DEC_AUTO)
  {
    tiAlt.bMonth = 3;
    DecretDate();
    memcpy(&tiSummer, &tiAlt, sizeof(time));

    tiAlt.bMonth = 10;
    DecretDate();
    memcpy(&tiWinter, &tiAlt, sizeof(time));
  }
}



void    ResetDecret(void)
{
  deDecret = DEC_NONE;
  MakeDecret();
}
