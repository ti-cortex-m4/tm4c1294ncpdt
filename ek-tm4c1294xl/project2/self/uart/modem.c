/*------------------------------------------------------------------------------
modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/restart.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "../kernel/printf.h"
#include "../kernel/wrappers.h"
#include "../tcp/telnet.h"
#include "../tcp/telnet_open.h"
#include "../tcp/telnet_close.h"
#include "../uart/serial_send.h"
#include "modem.h"



volatile modem_mode_t   mbModemMode[UART_COUNT];
volatile input_mode_t   mbInputMode[UART_COUNT];

volatile uchar          mbEscapeCnt[UART_COUNT];
volatile escape_mode_t  mbEscapeMode[UART_COUNT];

volatile uchar          mbDisconnectedByTimeout[UART_COUNT];



#define MODEM_BUF_SIZE  32

static volatile uchar   mmbModemBuf[UART_COUNT][MODEM_BUF_SIZE];
static volatile uchar   mibPush[UART_COUNT];
static volatile uchar   mibPop[UART_COUNT];

static bool             fVerbose;



void InitModem(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    mbModemMode[u] = MODEM_MODE_COMMAND;
    mbInputMode[u] = INPUT_MODE_BEGIN;

    mbEscapeCnt[u] = 0;
    mbEscapeMode[u] = ESCAPE_MODE_BEGIN;

    mbDisconnectedByTimeout[u] = UNKNOWN;
  }

  fVerbose = false;
}



static bool IsEOL(const uchar b)
{
  return (b == '\r') || (b == '\n');
}


static bool IsNumber(const uchar b)
{
  return (b >= '0') || (b <= '9');
}


static uchar ToUpper(const uchar b)
{
  if ((b >= 'a') && (b <= 'z'))
    return 'A' + (b - 'a');
  else
    return b;
}



bool IsModem(const uchar u)
{
  return mbRoutingMode[u] == ROUTING_MODE_CLIENT_MODEM;
}


bool IsModemModeCommand(const uchar u)
{
  return IsModem(u) && (mbModemMode[u] == MODEM_MODE_COMMAND);
}


void ProcessModemModeCommand(const uchar u, const uchar b)
{
  if (mbInputMode[u] == INPUT_MODE_BEGIN)
  {
    mbInputMode[u] = INPUT_MODE_DATA;
    mibPush[u] = 0;
  }

  if (mbInputMode[u] == INPUT_MODE_DATA)
  {
    if (mibPush[u] >= MODEM_BUF_SIZE)
      mibPush[u] = 0;

    mmbModemBuf[u][ mibPush[u] ] = b;
    mibPush[u]++;

    if (IsEOL(b))
      mbInputMode[u] = INPUT_MODE_READY;
  }
}


void ProcessModemModeData(const uchar u, const uchar b)
{
  if (IsModem(u))
  {
    mbEscapeCnt[u] = 0;

    if ((mbEscapeMode[u] == ESCAPE_MODE_PAUSE_BEFORE) && (b == '+'))
      mbEscapeMode[u] = ESCAPE_MODE_PLUS_1;
    else if ((mbEscapeMode[u] == ESCAPE_MODE_PLUS_1) && (b == '+'))
      mbEscapeMode[u] = ESCAPE_MODE_PLUS_2;
    else if ((mbEscapeMode[u] == ESCAPE_MODE_PLUS_2) && (b == '+'))
      mbEscapeMode[u] = ESCAPE_MODE_PLUS_3;
    else
      mbEscapeMode[u] = ESCAPE_MODE_BEGIN;
  }
}


void Modem_10Hz(void)
{
  uchar u;
  for (u=0; u<UART_COUNT; u++)
  {
    if (IsModem(u))
    {
      if (mbEscapeCnt[u] >= 10)
      {
        if (mbEscapeMode[u] == ESCAPE_MODE_BEGIN)
          mbEscapeMode[u] = ESCAPE_MODE_PAUSE_BEFORE;
        else if (mbEscapeMode[u] == ESCAPE_MODE_PLUS_3)
          mbEscapeMode[u] = ESCAPE_MODE_PAUSE_AFTER;
      }
      else
        mbEscapeCnt[u]++;
    }
  }
}



static bool IsModemCmd(const uchar u, const uchar *pcszCmd)
{
  uchar i = 0;
  while (*pcszCmd)
  {
    if (i >= mibPush[u])
      return false;

    if (ToUpper(mmbModemBuf[u][i++]) != ToUpper(*pcszCmd++))
      return false;
  }

  return IsEOL(mmbModemBuf[u][i]);
}


static bool IsModemCmdPrefix(const uchar u, const uchar *pcszCmd)
{
  uchar i = 0;
  while (*pcszCmd)
  {
    if (i >= mibPush[u])
      return false;

    if (ToUpper(mmbModemBuf[u][i++]) != ToUpper(*pcszCmd++))
      return false;
  }

  return true;
}



static void ModemOut(const uchar u, const uchar b, char *pcsz)
{
  if (fVerbose)
  {
    SerialSend(u, '0' + b);
    SerialSend(u, ' ');

    while (*pcsz)
      SerialSend(u, *pcsz++);
  }
  else
  {
    SerialSend(u, '0' + b);
  }

  SerialSend(u, '\r');
  SerialSend(u, '\n');
}


static void ModemOutBuff(const uchar u, const uchar b, const buff bf)
{
  ModemOut(u, b, (char *)bf.pbBuff);
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
    return GetChar2Success(w);
  else
    return GetChar2Error();
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

    cm.mb4[3-i] = b2.b;
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
    return GetInt2Success(dw);
  else
    return GetInt2Error();
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
  if (IsModem(u) && (mbModemMode[u] == MODEM_MODE_COMMAND))
  {
    mbDisconnectedByTimeout[u] = UNKNOWN;

    mbModemMode[u] = MODEM_MODE_DATA;
    ModemOut(u, 1, "CONNECT, connected");
  }
}


void ModemConnectFailed(const uchar u, const err_t err)
{
  mbModemMode[u] = MODEM_MODE_COMMAND;

  if (err == ERR_ABRT)
    ModemOutBuff(u, 8, BuffPrintF("NO ANSWER, no answer from remote host error=%d", err));
  else if (err == ERR_RST)
    ModemOutBuff(u, 3, BuffPrintF("NO CARRIER, connection dropped by remote host error=%d", err));
  else
    ModemOutBuff(u, 7, BuffPrintF("BUSY, connection failed error=%d", err));
}


static void ModemDisconnect(const uchar u)
{
  CONSOLE("%u: disconnect as modem\n", u);

  mbDisconnectedByTimeout[u] = false;

  TelnetCloseClient(u);
  ModemOut(u, 0, "OK, disconnected");
}


void ModemDisconnectedByTimeout(const uchar u)
{
  mbModemMode[u] = MODEM_MODE_COMMAND;
  mbDisconnectedByTimeout[u] = true;

  ModemOut(u, 6, "NO DIALTONE, disconnected by timeout");
}


void RunModem(const uchar u)
{
  if ((mbModemMode[u] == MODEM_MODE_COMMAND) && (mbInputMode[u] == INPUT_MODE_READY))
  {
    if (IsModemCmd(u, "at")) {
      ModemOut(u, 0, "OK, modem available");
    } else if (IsModemCmdPrefix(u, "atdp")) {
      if (!ModemConnect(u))
        ModemOut(u, 4, "ERROR, wrong address");
    } else if (IsModemCmd(u, "ath0")) {
      ModemDisconnect(u);
    } else if (IsModemCmd(u, "atv0")) {
      fVerbose = false;
      ModemOut(u, 0, "OK, numeric answers");
    } else if (IsModemCmd(u, "atv1")) {
      fVerbose = true;
      ModemOut(u, 0, "OK, verbose answers");
    } else if (IsModemCmd(u, "at-rst")) {
      ModemOut(u, 0, "OK, going to restart");
      DelayMilliSecond(100);
      Restart();
    } else if (IsModemCmd(u, "at-c")) {
      if (g_sState[u].eTCPState == STATE_TCP_CONNECTED)
        ModemOut(u, 1, "YES, connected");
      else
        ModemOut(u, 0, "NO, not connected");
    } else if (IsModemCmd(u, "at-dcbt")) {
      if (mbDisconnectedByTimeout[u] == false)
        ModemOut(u, 0, "NO, disconnected normally");
      else if (mbDisconnectedByTimeout[u] == true)
        ModemOut(u, 1, "YES, disconnected by timeout");
      else
        ModemOut(u, 2, "UNKNOWN, never disconnected");
    } else {
      ModemOut(u, 4, "ERROR, unknown command");
    }

    mbInputMode[u] = INPUT_MODE_BEGIN;
  }

  if (mbModemMode[u] == MODEM_MODE_DATA) {
    if (mbEscapeMode[u] == ESCAPE_MODE_PAUSE_AFTER) {
      mbModemMode[u] = MODEM_MODE_COMMAND;
      ModemOut(u, 0, "OK, command mode");
      mbEscapeMode[u] = ESCAPE_MODE_BEGIN;
    }
  }
}
