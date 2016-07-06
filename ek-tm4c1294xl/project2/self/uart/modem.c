/*------------------------------------------------------------------------------
modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "../kernel/log.h"
#include "../tcp/telnet_open.h"
#include "serial_send.h"
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

  mmbModemBuf[u][ mibModemBuf[u] ] = b;
  mibModemBuf[u]++;
}



bool IsModemCmd(const char u, const char *pcszCmd)
{
  uchar i = 0;
  while (*pcszCmd)
  {
    if (mmbModemBuf[u][i++] != *pcszCmd++)
      return false;
  }

  uchar b = mmbModemBuf[u][i];
  if ((b == '\r') || (b == '\n'))
    return true;

  return false;
}


bool IsModemCmdPrefix(const char u, const char *pcszCmd)
{
  uchar i = 0;
  while (*pcszCmd)
  {
    if (mmbModemBuf[u][i++] != *pcszCmd++)
      return false;
  }

  return true;
}


void ModemOut(const char u, const char b)
{
  SerialSend(u, b);
}


void ModemConnect(const char u, const char b)
{
  ulong dwIP = 0;
  uint wPort = 0;

  CONSOLE("%u: connect as modem to %u.%u.%u.%u port %u\n",
    u,
    (dwIP >> 24), (dwIP >> 16) & 0xFF, (dwIP >> 8) & 0xFF, dwIP & 0xFF,
	wPort);

  TelnetOpen(dwIP, wPort, u);
}


void RunModem(const char u)
{
  if (mfModemDataMode[u] == false)
  {
    if (IsModemCmd(u, "AT"))
      ModemOut(u, 0);
    else if (IsModemCmdPrefix(u, "ATDP"))
      ModemConnect(u);
    else if (IsModemCmd(u, "ATH0"))
      ModemDisconnect(u);
    else
      WARNING("RunModem: unknown command\n");
  }
}
