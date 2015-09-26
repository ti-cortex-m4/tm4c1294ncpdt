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

bool    ValidTimeDateRTC(time  ti);

void    InitRTC(void);
