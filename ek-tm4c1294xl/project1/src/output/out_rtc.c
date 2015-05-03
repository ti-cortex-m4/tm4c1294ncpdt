/*------------------------------------------------------------------------------
OUT_RTC.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../time/rtc.h"



void    OutGetCurrTimeDate(void)
{
  Common(GetCurrTimeDate(), sizeof(time));
}
