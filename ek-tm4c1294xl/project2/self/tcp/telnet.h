/*------------------------------------------------------------------------------
TELNET,H


------------------------------------------------------------------------------*/

#include "telnet_include.h"



extern tState g_sState[UART_COUNT];



ulong getTelnetTimeout(uchar u);

void TelnetFreePbufs(tState *pState);
void TelnetInit(void);

err_t TelnetConnected(void *arg, struct tcp_pcb *pcb, err_t err);
void TelnetError(void *arg, err_t err);
err_t TelnetSent(void *arg, struct tcp_pcb *pcb, u16_t len);

void TelnetHandler(void);

void TelnetNotifyLinkStatus(bool bLinkStatusUp);
