/*------------------------------------------------------------------------------
MONITOR_CORE.H


------------------------------------------------------------------------------*/

void    InitMonitor(void);
void    ResetMonitor(void);

bool    UseMonitor(void);
void    MonitorRepeat(void);

void    MonitorOpen(uchar  ibPrt);
void    MonitorClose(void);

void    DelayMonitor_1Hz(void);

uint    GetMonitorDelay(void);
