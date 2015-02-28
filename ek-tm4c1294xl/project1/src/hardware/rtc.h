/*------------------------------------------------------------------------------
RTC.H

 DS3234EN
------------------------------------------------------------------------------*/

time    *GetCurrTimeDate(void);

void    SetCurrTimeDate(time  *pti);
void    SetCurrTime(time  *pti);
void    SetCurrDate(time  *pti);

void    SetLabelRTC(void);
bool    GetLabelRTC(void);

bool    TrueCurrTimeDate(time  *pti);

void    InitRTC(void);
