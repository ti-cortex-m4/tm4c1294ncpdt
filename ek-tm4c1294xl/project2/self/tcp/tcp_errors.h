/*------------------------------------------------------------------------------
tcp_errors.h


------------------------------------------------------------------------------*/

#ifndef __TCP_ERRORS_H__
#define __TCP_ERRORS_H__


typedef enum
{
  TCP_NEW_LISTEN,
  TCP_BIND_LISTEN,
  TCP_NEW_OPEN,
  TCP_CONNECT_OPEN,
} tcp_operation_t;



void ErrorTCPOperation(uchar u, err_t err, tcp_operation_t op);


#endif
