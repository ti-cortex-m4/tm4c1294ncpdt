/*------------------------------------------------------------------------------
WATCHDOG.H


------------------------------------------------------------------------------*/

#define ENABLE_WATCHDOG


void    InitWDT(void);

void    EnableWDT(void);
void    DisableWDT(void);
void    ResetWDT(void);
bool    IsResetWDT(void);
