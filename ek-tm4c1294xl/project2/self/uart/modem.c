/*------------------------------------------------------------------------------
modem.c


------------------------------------------------------------------------------*/

#include <ctype.h>
#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/restart.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "../kernel/wrappers.h"
#include "../tcp/telnet_open.h"
#include "../tcp/telnet_close.h"
#include "../uart/serial_send.h"
#include "modem.h"



volatile modem_mode_t   mbModemMode[UART_COUNT];
volatile input_mode_t   mbInputMode[UART_COUNT];

volatile uchar          mbEscapeCnt[UART_COUNT];
volatile escape_mode_t  mbEscapeMode[UART_COUNT];



#define MODEM_BUF_SIZE  32

static volatile uchar   mmbModemBuf[UART_COUNT][MODEM_BUF_SIZE];
static volatile uchar   mibModemPtr[UART_COUNT];

static uchar            mibPop[UART_COUNT];



void InitModem(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    mbModemMode[u] = MODEM_MODE_COMMAND;
    mbInputMode[u] = INPUT_MODE_BEGIN;

    mbEscapeCnt[u] = 0;
    mbEscapeMode[u] = ESCAPE_MODE_BEGIN;
  }
}



bool IsEOL(const uchar b)
{
  return (b == '\r') || (b == '\n');
}


bool IsNumber(const uchar b)
{
  return (b >= '0') || (b <= '9');
}



bool IsModemModeCommand(const uchar u)
{
  return (mbRoutingMode[u] == ROUTING_MODE_CLIENT_MODEM) && (mbModemMode[u] == MODEM_MODE_COMMAND);
}


void ProcessModemModeCommand(const uchar u, const uchar b)
{
  if (mbInputMode[u] == INPUT_MODE_BEGIN)
  {
    mbInputMode[u] == INPUT_MODE_DATA;
    mibModemPtr[u] = 0;
  }

  if (mbInputMode[u] == INPUT_MODE_DATA)
  {
    if (mibModemPtr[u] >= MODEM_BUF_SIZE)
      mibModemPtr[u] = 0;

    mmbModemBuf[u][ mibModemPtr[u] ] = b;
    mibModemPtr[u]++;

    if (IsEOL(b))
      mbInputMode[u] = INPUT_MODE_READY;
  }
}



bool IsModemCmd(const uchar u, const uchar *pcszCmd)
{
  uchar i = 0;
  while (*pcszCmd)
  {
    if (i >= mibModemPtr[u])
      return false;

    if (_toupper(mmbModemBuf[u][i++]) != _toupper(*pcszCmd++))
      return false;
  }

  return IsEOL(mmbModemBuf[u][i]);
}


bool IsModemCmdPrefix(const uchar u, const uchar *pcszCmd)
{
  uchar i = 0;
  while (*pcszCmd)
  {
    if (i >= mibModemPtr[u])
      return false;

    if (_toupper(mmbModemBuf[u][i++]) != _toupper(*pcszCmd++))
      return false;
  }

  return true;
}


void ModemOut(const uchar u, const uchar b)
{
  SerialSend(u, b);
  SerialSend(u, '\r');
  SerialSend(u, '\n');
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
  uint w = 0;
  uchar m = 100;

  uchar i;
  for (i=0; i<3; i++)
  {
    uchar b = PopChar(u);
    if (!IsNumber(b))
      GetChar2Error();

    w += (b - '0')*m;
    m /= 10;
  }

  if (w < MAX_CHAR)
    return GetChar2Error();
  else
    return GetChar2Success(w);
}


static ulong2 PopIPDec(const uchar u)
{
  combo32 cm;

  uchar i;
  for (i=0; i<4; i++)
  {
    uchar2 b2 = PopCharDec(u);
    if (InvalidChar2(b2))
      return GetLong2Error();

    cm.mb4[i] = b2.b;
  }

  return GetLong2Success(cm.dw);
}


static uint2 PopIntDec(const uchar u)
{
  ulong dw = 0;
  uint m = 10000;

  uchar i;
  for (i=0; i<5; i++)
  {
    uchar b = PopChar(u);
    if (!IsNumber(b))
      GetChar2Error();

    dw += (b - '0')*m;
    m /= 10;
  }

  if (dw < MAX_INT)
    return GetInt2Error();
  else
    return GetInt2Success(dw);
}


bool ModemConnect(const uchar u)
{
  InitPop(u, 4);

  ulong2 dw2 = PopIPDec(u);
  if (InvalidLong2(dw2))
    return false;

  ulong dwIP = dw2.dw;

  uint2 w2 = PopIntDec(u);
  if (InvalidInt2(w2))
    return false;

  uint wPort = w2.w;

  if (!IsEOL(PopChar(u)))
    return false;

  CONSOLE("%u: connect as modem to %u.%u.%u.%u port %u\n",
    u,
    (dwIP >> 24), (dwIP >> 16) & 0xFF, (dwIP >> 8) & 0xFF, dwIP & 0xFF,
    wPort);

  TelnetOpen(dwIP, wPort, u);
  return true;
}


void ModemConnected(const uchar u)
{
  if ((mbRoutingMode[u] == ROUTING_MODE_CLIENT_MODEM) && (mbModemMode[u] == MODEM_MODE_COMMAND)) // ???
  {
    mbModemMode[u] = MODEM_MODE_DATA;
    ModemOut(u, 1); // TODO
  }
}


void ModemDisconnect(const uchar u)
{
  CONSOLE("%u: disconnect as modem\n", u);

  // TODO check status
  TelnetCloseClient(u);
  // TODO check result
}


void RunModem(const uchar u)
{
  if ((mbModemMode[u] == MODEM_MODE_COMMAND) && (mbInputMode[u] == INPUT_MODE_READY))
  {
    if (IsModemCmd(u, "at-restart"))
    {
      ModemOut(u, 0);
      DelayMilliSecond(500);
      Restart();
    }
    if (IsModemCmd(u, "at"))
      ModemOut(u, 0);
    else if (IsModemCmdPrefix(u, "atdp"))
    {
      if (!ModemConnect(u))
        ModemOut(u, 4);
    }
    else if (IsModemCmd(u, "ath0"))
      ModemDisconnect(u);
    else
    {
      WARNING("RunModem: unknown command\n");
      ModemOut(u, 4);
    }

    mbInputMode[u] == INPUT_MODE_BEGIN;
  }

  if (mbModemMode[u] == MODEM_MODE_DATA)
  {
    if (mbEscapeMode[u] == ESCAPE_MODE_PAUSE_AFTER)
    {
      mbModemMode[u] = MODEM_MODE_COMMAND;
      ModemOut(u, 0); // TODO
      mbEscapeMode[u] = ESCAPE_MODE_BEGIN;
    }
  }
}



void Modem_10Hz(void)
{
  uchar u;
  for (u=0; u<UART_COUNT; u++)
  {
     if (mbEscapeMode[u] == ESCAPE_MODE_DATA)
     {
       if (++mbEscapeCnt[u] > 10)
         mbEscapeMode[u] = ESCAPE_MODE_PAUSE_BEFORE;
     }
     else if (mbEscapeMode[u] == ESCAPE_MODE_PLUS_3)
     {
       if (++mbEscapeCnt[u] > 10)
         mbEscapeMode[u] = ESCAPE_MODE_PAUSE_AFTER;
     }
  }
}


void ProcessModemModeData(const uchar u, const uchar b)
{
  mbEscapeCnt[u] = 0;

  if ((mbEscapeMode[u] == ESCAPE_MODE_PAUSE_BEFORE) && (b == '+'))
  {
    mbEscapeMode[u] == ESCAPE_MODE_PLUS_1;
  }
  else if ((mbEscapeMode[u] == ESCAPE_MODE_PLUS_1) && (b == '+'))
  {
    mbEscapeMode[u] == ESCAPE_MODE_PLUS_2;
  }
  else if ((mbEscapeMode[u] == ESCAPE_MODE_PLUS_2) && (b == '+'))
  {
    mbEscapeMode[u] == ESCAPE_MODE_PLUS_3;
  }
  else
  {
    mbEscapeMode[u] = ESCAPE_MODE_DATA;
  }
}

// локальный порт недоступен
// удаленный порт недоступен
// ATH0 в неправильном режиме
