/*------------------------------------------------------------------------------
WATCHDOG.H


------------------------------------------------------------------------------*/

#define ENABLE_WATCHDOG


void    InitWatchdog(void);

void    EnableWatchdog(void);
void    DisableWatchdog(void);
void    ResetWatchdog(void);
bool    IsResetWatchdog(void);
