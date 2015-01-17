/*------------------------------------------------------------------------------
RTC.H


------------------------------------------------------------------------------*/

#include 		"main.h"



extern  time                    tiGetRTC, tiSetRTC;



void    InitRTC(void);

time    *PGetCurrTimeDate(void);

void    SetCurrTimeDate(void);
void    SetCurrTime(void);
void    SetCurrDate(void);

void    RTC_Timer1(void);
