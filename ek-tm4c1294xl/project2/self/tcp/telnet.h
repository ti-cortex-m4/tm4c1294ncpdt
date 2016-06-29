/*------------------------------------------------------------------------------
TELNET.H


------------------------------------------------------------------------------*/

#include "telnet_include.h"



extern tState g_sState[UART_COUNT];



ulong getTelnetTimeout(uchar u);

void TelnetFreePbufs(tState *pState);
void TelnetInit(void);
void TelnetHandler(void);
void TelnetNotifyLinkStatus(bool bLinkStatusUp);
