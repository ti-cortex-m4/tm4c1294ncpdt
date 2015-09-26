/*------------------------------------------------------------------------------
RTC!H

 DS3234EN
------------------------------------------------------------------------------*/

void    InitGPIO_RTC();

time    *GetCurrTimeDate(void);

void    SetCurrTimeDate(time  ti);
void    SetCurrTime(time  ti);
void    SetCurrDate(time  ti);

void    SetLabelRTC(void);
bool    GetLabelRTC(void);

bool    IsValidTimeDateRTC(time  ti);

void    InitRTC(void);
