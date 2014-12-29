/*------------------------------------------------------------------------------
KEY_TIMEDATE.H

 Установка и просмотр текущего времени и даты
------------------------------------------------------------------------------*/

void    key_SetCurrTime(void);
void    key_SetCurrDate(void);
void    auto_GetCurrTime(void);   
void    auto_GetCurrDate(void); 
  
// TODO move to separate place
void    ShowTimeNow(void);
void    NoShowTime(bool  fClear);
