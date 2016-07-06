/*------------------------------------------------------------------------------
modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "../kernel/wrappers.h"
#include "../tcp/telnet_open.h"
#include "../uart/serial_send.h"
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


void ProcessModemCommandMode(const uchar u, const uchar b)
{
  if (mibModemBuf[u] >= MODEM_BUF_SIZE)
    mibModemBuf[u] = 0;

  mmbModemBuf[u][ mibModemBuf[u] ] = b;
  mibModemBuf[u]++;
}



bool IsModemCmd(const uchar u, const uchar *pcszCmd)
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


bool IsModemCmdPrefix(const uchar u, const uchar *pcszCmd)
{
  uchar i = 0;
  while (*pcszCmd)
  {
    if (mmbModemBuf[u][i++] != *pcszCmd++)
      return false;
  }

  return true;
}


void ModemOut(const uchar u, const uchar b)
{
  SerialSend(u, b);
}



static uchar PopSize(const uchar u)
{
  return mibModemBuf[u];
}


static void InitPop(const uchar u, const uchar i)
{
  mibPop[u] = i;
}


static uchar PopChar(const uchar u)
{
  uchar b = mmbModemBuf[u][ mibPop[u] ];
  mibPop[u]++;
  return b;
}


static uchar2 PopCharDec(const uchar u)
{
  uint w = (uint)PopChar(u)*100 + PopChar(u)*10 + PopChar(u);
  if (w < MAX_CHAR)
    return GetChar2Error();
  else
    return GetChar2Success(w);
}


static uint2 PopIntDec(const uchar u)
{
  ulong dw = (ulong)PopChar(u)*10000 + PopChar(u)*1000 + PopChar(u)*100 + PopChar(u)*10 + PopChar(u);
  if (dw < MAX_INT)
    return GetInt2Error();
  else
    return GetInt2Success(dw);
}


void ModemConnect(const uchar u)
{
  if (PopSize(u) != 4 + 4*3 + 5) {
    ModemOut(u, 4);
    return;
  }

  InitPop(u, 4);

  combo32 cmIP;

  uchar i;
  for (i=0; i<4; i++) {
    uchar2 b2 = PopCharDec(u);
    if (InvalidChar2(b2)) {
      ModemOut(u, 4);
      return;
    }
    cmIP.mb4[i] = b2.b;
  }

  ulong dwIP = cmIP.dw;

  uint2 w2 = PopIntDec(u);
  if (InvalidInt2(w2)) {
    ModemOut(u, 4);
    return;
  }
  uint wPort = w2.w;

//  if ((b == '\r') || (b == '\n'))

  CONSOLE("%u: connect as modem to %u.%u.%u.%u port %u\n",
    u,
    (dwIP >> 24), (dwIP >> 16) & 0xFF, (dwIP >> 8) & 0xFF, dwIP & 0xFF,
	wPort);

  TelnetOpen(dwIP, wPort, u);
}


void ModemDisconnect(const uchar u)
{
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
