/*------------------------------------------------------------------------------
tcp_errors.h


------------------------------------------------------------------------------*/

#ifndef __TCP_ERRORS_H__
#define __TCP_ERRORS_H__


typedef enum
{
  HANDLER_ERROR,
  HANDLER_CONNECTED,
  TCP_NEW_LISTEN,
  TCP_BIND_LISTEN,
  TCP_NEW_OPEN,
  TCP_CONNECT_OPEN,
  TCP_CONNECT_POLL,
} tcp_operation_t;



#define TCP_OPERATIONS  7



extern err_t                   mwErrTCPErrors[UART_COUNT][TCP_OPERATIONS];
extern uint                    mcwErrTCPCounters[UART_COUNT][TCP_OPERATIONS];
extern ulong                   mdwErrTCPClockSeconds[UART_COUNT][TCP_OPERATIONS];



void ErrorTCPOperation(uchar u, err_t err, tcp_operation_t op);


#endif
