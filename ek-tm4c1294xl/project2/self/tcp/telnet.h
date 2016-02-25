/*------------------------------------------------------------------------------
TELNET,H


------------------------------------------------------------------------------*/

#include "telnet_include.h"



extern tState g_sTelnetSession[UART_COUNT];



ulong getTelnetTimeout(uchar u);

void TelnetFreePbufs(tState *pState);
extern void TelnetInit(void);

err_t TelnetAccept(void *arg, struct tcp_pcb *pcb, err_t err);
err_t TelnetConnected(void *arg, struct tcp_pcb *pcb, err_t err);
void TelnetError(void *arg, err_t err);

extern err_t TelnetCloseClient(uint32_t ulSerialPort);
extern err_t TelnetCloseServer(uint32_t ulSerialPort);
extern void TelnetClose(uint32_t ulSerialPort);

extern void TelnetHandler(void);

void TelnetNotifyLinkStatus(bool bLinkStatusUp);
