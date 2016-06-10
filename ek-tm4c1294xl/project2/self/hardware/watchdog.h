/*------------------------------------------------------------------------------
watchdog.h


------------------------------------------------------------------------------*/

#define ENABLE_WATCHDOG



void EnableWatchdog(void);
void DisableWatchdog(void);
void ResetWatchdog(void);

void InitWatchdog(void);
bool IsWatchdogReset(void);
