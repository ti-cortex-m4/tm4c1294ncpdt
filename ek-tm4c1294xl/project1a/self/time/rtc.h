/*------------------------------------------------------------------------------
RTC!H


------------------------------------------------------------------------------*/

time    *GetCurrTimeDate(void);

void    SetCurrTimeDate(time  ti);
void    SetCurrTime(time  ti);
void    SetCurrDate(time  ti);

bool    GetLabelRTC(void);

bool    ValidTimeDateRTC(time  ti);

void    InitRTC(void);
