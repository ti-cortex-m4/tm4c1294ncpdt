/*------------------------------------------------------------------------------
UNI_TIME,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/rtc.h"
#include "response_uni.h"
#include "uni_time.h"



void    GetTimeUni(void)
{
  Common2(GetCurrTimeDate(), sizeof(time));
}
