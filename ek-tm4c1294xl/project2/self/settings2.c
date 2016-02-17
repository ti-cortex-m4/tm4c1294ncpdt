/*------------------------------------------------------------------------------
SETTINGS2.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "settings.h"
#include "settings2.h"



//! The timeout for the TCP connection used for the telnet session, specified in seconds.
//! A value of 0 indicates no timeout is to be used.
ulong getTelnetTimeout(uchar u)
{
  ASSERT(u < UART_COUNT);
  return mbConnectionTimeout[u]*60;
}

#if false
bool isServer(uint8_t  ibPort)
{
  ASSERT(ibPort < UART_COUNT);
  return false;
}
#endif
