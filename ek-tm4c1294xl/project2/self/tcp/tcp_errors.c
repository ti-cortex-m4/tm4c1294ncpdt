/*------------------------------------------------------------------------------
tcp_errors.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "tcp_errors.h"



err_t                   mwErrors[UART_COUNT]
uint                    mcwErrorTCPFunctions[UART_COUNT][10];
ulong                   mdwErrorClock[UART_COUNT][10];



void ErrorTCPFunction(uchar u, err_t err, tcp_function_t func)
{
  mwErrors[u] = err;
  mcwErrorTCPFunctions[u][tcp_function_t]++;
  mdwErrorClock[u][tcp_function_t] = GetClockSeconds();
}
