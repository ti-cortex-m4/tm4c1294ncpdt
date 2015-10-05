/*------------------------------------------------------------------------------
MONITOR.H


------------------------------------------------------------------------------*/

#include "../main.h"



void    InitMonitor(void);

bool    UseMonitor(void);

void    MonitorOpen(uchar  ibPrt);
void    MonitorClose(void);

void    DelayMonitor_1Hz(void);

void    MonitorString(const char  *psz);
void    MonitorCharDec(uchar  b);
void    MonitorCharHex(uchar  b);
void    MonitorIntDec(uint  w);
void    MonitorLongDec(ulong  dw);
void    MonitorTime(time  ti);

void    MonitorOut(uint  cwIn, uint  cwOut);
void    MonitorIn(void);

uint    GetMonitorDelay(void);
