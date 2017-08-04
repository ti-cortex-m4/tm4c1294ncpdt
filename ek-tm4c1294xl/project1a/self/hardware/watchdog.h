/*------------------------------------------------------------------------------
WATCHDOG!H


------------------------------------------------------------------------------*/

#define ENABLE_WATCHDOG


void    EnableWatchdog(void);
void    DisableWatchdog(void);
void    ResetWatchdog(void);
bool    IsResetWatchdog(void);
