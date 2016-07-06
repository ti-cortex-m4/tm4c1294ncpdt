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

static uchar            mibPop[UART_COUNT];



void InitModem(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    mfModemDataMode[u] = false;
    mibModemBuf[u] = 0;
  }
}



bool IsModemCommandMode(const uchar u)
{
  return (mbRoutingMode[u] == ROUTING_MODE_CLIENT_MODEM) && (mfModemDataMode[u] == false);
}


void ProcessModemCommandMode(const uchar u, const char b)
{
  if (mibModemBuf[u] >= MODEM_BUF_SIZE)
    mibModemBuf[u] = 0;

  mmbModemBuf[u][ mibModemBuf[u] ] = b;
  mibModemBuf[u]++;
}



bool IsModemCmd(const uchar u, const char *pcszCmd)
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


bool IsModemCmdPrefix(const uchar u, const char *pcszCmd)
{
  uchar i = 0;
  while (*pcszCmd)
  {
    if (mmbModemBuf[u][i++] != *pcszCmd++)
      return false;
  }

  return true;
}


void ModemOut(const uchar u, const char b)
{
  SerialSend(u, b);
}


void InitPop(const uchar u, const uchar i)
{
  mibPop[u] = i;
}


void ModemConnect(const uchar u, const char b)
{
  if (PopSize(u) != 4 + 4*3 + 5)
  {
    ModemOut(u, 4);
    return;
  }

  InitPop(u, 4);

  combo32 cmIP;
  cmIP.mb4[0] = PopChar(u);
  cmIP.mb4[1] = PopChar(u);
  cmIP.mb4[2] = PopChar(u);
  cmIP.mb4[3] = PopChar(u);

  ulong dwIP = cmIP.dw;
  uint wPort = PopInt(u);

  CONSOLE("%u: connect as modem to %u.%u.%u.%u port %u\n",
    u,
    (dwIP >> 24), (dwIP >> 16) & 0xFF, (dwIP >> 8) & 0xFF, dwIP & 0xFF,
	wPort);

  TelnetOpen(dwIP, wPort, u);
}


void RunModem(const uchar u)
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
