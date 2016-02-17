/*------------------------------------------------------------------------------
UART,H


------------------------------------------------------------------------------*/

#include "lwip/tcp.h"



void    InitUART(ulong dwSysClockFreq);

void    UART_Out1(uchar* ptr, uint len);
void    UART_Out2(struct tcp_pcb *tpcb);

void    UART_1000Hz(void);
