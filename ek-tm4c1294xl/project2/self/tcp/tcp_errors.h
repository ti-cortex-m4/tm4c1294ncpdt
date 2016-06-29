/*------------------------------------------------------------------------------
tcp_errors.h


------------------------------------------------------------------------------*/

#ifndef __TCP_ERRORS_H__
#define __TCP_ERRORS_H__


typedef enum
{
  HANDLER_ERROR = 0,
  HANDLER_CONNECTED = 1,
  TCP_NEW_LISTEN = 2,
  TCP_BIND_LISTEN = 3,
  TCP_NEW_OPEN = 4,
  TCP_CONNECT_OPEN = 5,
  TCP_CONNECT_POLL = 6,
  TCP_CLOSE_CONNECTED = 7,
  TCP_CLOSE_RECEIVE = 8,
  TCP_CLOSE_CLOSE = 9,
} tcp_operation_t;



#define TCP_OPERATIONS  10



extern err_t                   mwErrTCPErrors[UART_COUNT][TCP_OPERATIONS];
extern uint                    mcwErrTCPCounters[UART_COUNT][TCP_OPERATIONS];
extern ulong                   mdwErrTCPClockSeconds[UART_COUNT][TCP_OPERATIONS];



void ErrorTCPOperation(uchar u, err_t err, tcp_operation_t op);


#endif
