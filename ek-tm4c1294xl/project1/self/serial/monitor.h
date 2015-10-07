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
//void    MonitorChar(const char  *psz, uchar  b);
void    MonitorCharDec(uchar  b);
void    MonitorCharDec3(uchar  b);
void    MonitorCharHex(uchar  b);
//void    MonitorInt(const char  *psz, uint  w);
void    MonitorIntDec(uint  w);
//void    MonitorLong(const char  *psz, ulong  dw);
void    MonitorLongDec(ulong  dw);
void    MonitorTime(time  ti);

void    MonitorOut(uint  cwIn, uint  cwOut);
void    MonitorIn(void);

uint    GetMonitorDelay(void);
