/*------------------------------------------------------------------------------
SETTINGS2.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "settings2.h"



//! The timeout for the TCP connection used for the telnet session, specified in seconds.
//! A value of 0 indicates no timeout is to be used.
uint32_t getTelnetTimeout(uint8_t  ibPort)
{
  ASSERT(ibPort < UART_COUNT);
  return 0;
}


bool isServer(uint8_t  ibPort)
{
  ASSERT(ibPort < UART_COUNT);
  return false;
}
