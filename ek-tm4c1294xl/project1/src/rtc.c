/*------------------------------------------------------------------------------
RTC.C
              

------------------------------------------------------------------------------*/

#include        "main.h"



time                    tiGetRTC;



void    InitRTC(void) {
  tiGetRTC.bSecond = 0;
  tiGetRTC.bMinute = 0;
  tiGetRTC.bHour   = 0;
  tiGetRTC.bDay    = 0;
  tiGetRTC.bMonth  = 0;
  tiGetRTC.bYear   = 0;
}


time    *PGetCurrTimeDate(void) {
  return &tiGetRTC;
}
