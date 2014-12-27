/*------------------------------------------------------------------------------
RTC.C
              

------------------------------------------------------------------------------*/

#include        "main.h"
#include        "timedate.h"



time                    tiGetRTC;
ulong                   dwRTC;



void    InitRTC(void) {
  tiGetRTC.bSecond = 0;
  tiGetRTC.bMinute = 0;
  tiGetRTC.bHour   = 0;
  tiGetRTC.bDay    = 0;
  tiGetRTC.bMonth  = 0;
  tiGetRTC.bYear   = 0;

  tiAlt.bSecond = 0;
  tiAlt.bMinute = 0;
  tiAlt.bHour   = 0;
  tiAlt.bDay    = 31;
  tiAlt.bMonth  = 12;
  tiAlt.bYear   = 14;
  dwRTC = DateToSecIndex();
}


void    RTC_1Hz(void) {
  SecIndexToDate(++dwRTC);
  tiGetRTC = tiAlt;
}


time    *PGetCurrTimeDate(void) {
  return &tiGetRTC;
}
