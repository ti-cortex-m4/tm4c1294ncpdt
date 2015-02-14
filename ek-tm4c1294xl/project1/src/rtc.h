/*------------------------------------------------------------------------------
RTC.H

 DS3234EN
------------------------------------------------------------------------------*/

#include        "main.h"



void    InitRTC(void);

time   *GetCurrTimeDate(void);

void    SetCurrTimeDate(time  *pti);
void    SetCurrTime(time  *pti);
void    SetCurrDate(time  *pti);

bool    TrueCurrTimeDate(time  *pti);

void    RTC_Timer1(void);
