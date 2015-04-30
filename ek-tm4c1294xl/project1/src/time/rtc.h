/*------------------------------------------------------------------------------
RTC.H

 DS3234EN
------------------------------------------------------------------------------*/

#include        "../main.h"



#define NATIVE_RTC


void    InitGPIO_RTC();

time    *GetCurrTimeDate(void);

void    SetCurrTimeDate(time  ti);
void    SetCurrTime(time  ti);
void    SetCurrDate(time  ti);

void    SetLabelRTC(void);
bool    GetLabelRTC(void);

bool    TrueCurrTimeDate(time  ti);

void    InitRTC(void);
