/*------------------------------------------------------------------------------
RTC.C
              

------------------------------------------------------------------------------*/

#include        "main.h"
#include        "timedate.h"



time                    tiGetRTC, tiSetRTC;

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



time    *PGetCurrTimeDate(void) {
  return &tiGetRTC;
}


void    SetCurrTimeDate(void) {
  SecIndexToDate(dwRTC);

  tiAlt.bSecond = tiSetRTC.bSecond;
  tiAlt.bMinute = tiSetRTC.bMinute;
  tiAlt.bHour   = tiSetRTC.bHour;
  tiAlt.bDay    = tiSetRTC.bHour;
  tiAlt.bMonth  = tiSetRTC.bMonth;
  tiAlt.bYear   = tiSetRTC.bYear;

  dwRTC = DateToSecIndex();
}


void    SetCurrTime(void) {
  SecIndexToDate(dwRTC);

  tiAlt.bSecond = tiSetRTC.bSecond;
  tiAlt.bMinute = tiSetRTC.bMinute;
  tiAlt.bHour   = tiSetRTC.bHour;

  dwRTC = DateToSecIndex();
}


void    SetCurrDate(void) {
  SecIndexToDate(dwRTC);

  tiAlt.bDay    = tiSetRTC.bHour;
  tiAlt.bMonth  = tiSetRTC.bMonth;
  tiAlt.bYear   = tiSetRTC.bYear;

  dwRTC = DateToSecIndex();
}



void    RTC_Timer1(void) {
  SecIndexToDate(++dwRTC);
  tiGetRTC = tiAlt;
}
