/*------------------------------------------------------------------------------
MONITOR.H


------------------------------------------------------------------------------*/

#include "../main.h"



void    InitMonitor(void);

void    MonitorOpen(uchar  ibPrt);
void    MonitorClose(void);

void    DelayMonitor_1Hz(void);

void    MonitorOut(uint  cwIn, uchar  cbOut);
void    MonitorIn(void);

uint    GetMonitorDelay(void);
