/*------------------------------------------------------------------------------
modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "modem.h"



static volatile bool    mfModemDataMode[UART_COUNT];


#define MODEM_BUF_SIZE  32

static volatile uchar   mmbModemBuf[UART_COUNT][MODEM_BUF_SIZE];

static volatile uchar   mibModemBuf[UART_COUNT];



void InitModem(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    mfModemDataMode[u] = false;
    mibModemBuf[u] = 0;
  }
}



bool IsModemCommandMode(const char u)
{
  return (mbRoutingMode[u] == ROUTING_MODE_CLIENT_MODEM) && (mfModemDataMode[u] == false);
}


void ProcessModemCommandMode(const char u, const char b)
{
  if (mibModemBuf[u] >= MODEM_BUF_SIZE)
    mibModemBuf[u] = 0;

  mibModemBuf[u][ mibModemBuf[u] ] = b;
}
