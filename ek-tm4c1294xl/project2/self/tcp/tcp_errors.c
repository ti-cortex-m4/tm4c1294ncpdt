/*------------------------------------------------------------------------------
tcp_errors.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/clock.h"
#include "tcp_errors.h"



err_t                   mwErrTCPCodes[UART_COUNT][TCP_OPERATIONS];
uint                    mcwErrTCPCounters[UART_COUNT][TCP_OPERATIONS];
ulong                   mdwErrTCPClockSeconds[UART_COUNT][TCP_OPERATIONS];



void ErrorTCPOperation(uchar u, err_t err, tcp_operation_t op)
{
  ASSERT(op < TCP_OPERATIONS);

  mwErrTCPCodes[u][op] = err;
  mcwErrTCPCounters[u][op]++;
  mdwErrTCPClockSeconds[u][op] = GetClockSeconds();
}
