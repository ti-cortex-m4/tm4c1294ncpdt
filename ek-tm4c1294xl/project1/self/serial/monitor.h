/*------------------------------------------------------------------------------
MONITOR.H


------------------------------------------------------------------------------*/

#include "monitor_core.h"



void    MonitorString(const char  *psz);
void    MonitorCharChar(uchar  b);
void    MonitorBool(bool  f);
void    MonitorCharDec(uchar  b);
void    MonitorCharDec3(uchar  b);
void    MonitorCharHex(uchar  b);
void    MonitorIntDec(uint  w);
void    MonitorIntDec5(uint  w);
void    MonitorIntHex(uint  w);
void    MonitorLongDec(ulong  dw);
void    MonitorLongHex(ulong  dw);
void    MonitorLongDecimal(ulong  dw, uint  wDivider);
void    MonitorLong64Hex(uint64_t  ddw);
void    MonitorTime(time  ti);

void    MonitorOut(uint  cwIn, uint  cwOut);
void    MonitorIn(void);
void    MonitorArrayHex(uchar  *pbData, uint  wSize);

