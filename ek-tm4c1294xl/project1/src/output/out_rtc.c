/*------------------------------------------------------------------------------
OUT_RTC.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../ports.h"
#include        "../rtc.h"



void    OutGetCurrTimeDate(void)
{
  Common(GetCurrTimeDate(), sizeof(time));
}
