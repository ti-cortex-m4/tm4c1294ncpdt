/*------------------------------------------------------------------------------
UART.H


------------------------------------------------------------------------------*/

#include "lwip/tcp.h"



void    InitUART(ulong dwSysClockFreq);
void    UART_Out(struct tcp_pcb *tpcb, void *arg, uint len);

void    UART_1000Hz(void);
