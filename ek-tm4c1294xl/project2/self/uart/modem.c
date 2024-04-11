/*------------------------------------------------------------------------------
modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/restart.h"
#include "../hardware/storage.h"
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

volatile disconnect_t   mbDisconnect[UART_COUNT];



#define MODEM_BUF_SIZE  32

static volatile uchar   mmbModemBuf[UART_COUNT][MODEM_BUF_SIZE];
static volatile uchar   mibPush[UART_COUNT];
static volatile uchar   mibPop[UART_COUNT];

static bool             fVerbose;



void InitModem(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    mbModemMode[u] = MM_COMMAND;
    mbInputMode[u] = IM_BEGIN;

    mbEscapeCnt[u] = 0;
    mbEscapeMode[u] = EM_BEGIN;

    mbDisconnect[u] = DC_UNKNOWN;
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



void ModemSetVerbose(const bool f)
{
  fVerbose = f;
}


bool IsModem(const uchar u)
{
  return mbRoutingMode[u] == ROUTING_MODE_CLIENT_MODEM;
}


bool IsModemModeCommand(const uchar u)
{
  return IsModem(u) && (mbModemMode[u] == MM_COMMAND);
}


bool IsModemModeData(const uchar u)
{
  return IsModem(u) && (mbModemMode[u] == MM_DATA);
}


void ProcessModemModeCommand(const uchar u, const uchar b)
{
  if (mbInputMode[u] == IM_BEGIN)
  {
    mbInputMode[u] = IM_DATA;
    mibPush[u] = 0;
  }

  if (mbInputMode[u] == IM_DATA)
  {
    if (mibPush[u] >= MODEM_BUF_SIZE)
      mibPush[u] = 0;

    mmbModemBuf[u][ mibPush[u] ] = b;
    mibPush[u]++;

    if (IsEOL(b))
      mbInputMode[u] = IM_READY;
  }
}


void ProcessModemModeData(const uchar u, const uchar b)
{
  if (IsModem(u))
  {
    mbEscapeCnt[u] = 0;

    if ((mbEscapeMode[u] == EM_PAUSE_BEFORE) && (b == '+'))
      mbEscapeMode[u] = EM_PLUS_1;
    else if ((mbEscapeMode[u] == EM_PLUS_1) && (b == '+'))
      mbEscapeMode[u] = EM_PLUS_2;
    else if ((mbEscapeMode[u] == EM_PLUS_2) && (b == '+'))
      mbEscapeMode[u] = EM_PLUS_3;
    else
      mbEscapeMode[u] = EM_BEGIN;
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
        if (mbEscapeMode[u] == EM_BEGIN)
          mbEscapeMode[u] = EM_PAUSE_BEFORE;
        else if (mbEscapeMode[u] == EM_PLUS_3)
          mbEscapeMode[u] = EM_PAUSE_AFTER;
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

  CONSOLE("[%u] connect as modem to %u.%u.%u.%u port %u\n",
    u,
    (dwIP >> 24), (dwIP >> 16) & 0xFF, (dwIP >> 8) & 0xFF, dwIP & 0xFF,
    wPort);

  TelnetOpen(dwIP, wPort, u);
  return true;
}


void ModemConnected(const uchar u)
{
  if (IsModem(u) && (mbModemMode[u] == MM_COMMAND))
  {
    mbDisconnect[u] = DC_UNKNOWN;

    mbModemMode[u] = MM_DATA;
    ModemOut(u, 1, "CONNECT, connected");
  }
}


void ModemConnectFailed(const uchar u, const err_t err)
{
  mbModemMode[u] = MM_COMMAND;

  if (err == ERR_ABRT)
    ModemOutBuff(u, 8, BuffPrintF("NO ANSWER, no answer from remote host, error %d", err));
  else if (err == ERR_RST) {
    mbDisconnect[u] = DC_REMOTE;
    TelnetCloseClient(u);

    ModemOutBuff(u, 3, BuffPrintF("NO CARRIER, connection dropped by remote host, error %d", err));
  } else
    ModemOutBuff(u, 7, BuffPrintF("BUSY, connection failed, error %d", err));
}


static void ModemDisconnect(const uchar u)
{
  CONSOLE("[%u] disconnect as modem\n", u);

  mbDisconnect[u] = DC_NORMALLY;
  TelnetCloseClient(u);

  ModemOut(u, 0, "OK, disconnected");
}


void ModemDisconnectedByTimeout(const uchar u)
{
  mbModemMode[u] = MM_COMMAND;
  mbDisconnect[u] = DC_TIMEOUT;

  ModemOut(u, 6, "NO DIALTONE, disconnected by timeout");
}


static void ModemOutGetRoutingMode(const uchar u)
{
  uchar bRoutingMode = MAX_CHAR;
  LoadChar(&bRoutingMode, mpenRoutingModes[u]->dwEepRom);

  switch (bRoutingMode) {
    case 0: ModemOut(u, 0, "SERVER, routing mode will be 'server' after next restart"); break;
    case 1: ModemOut(u, 1, "CLIENT, routing mode will be 'client' after next restart"); break;
    case 2: ModemOut(u, 2, "MODEM, routing mode will be 'modem' after next restart"); break;
    default: ModemOut(u, 3, "ERROR, wrong routing mode"); break;
  }
}


void ModemOutSetRoutingModeModem(const uchar u)
{
  uchar bRoutingMode = 2;
  const ulong code = SaveChar(&bRoutingMode, mpenRoutingModes[u]->dwEepRom);

  switch (code) {
    case 0: ModemOut(u, 0, "OK, routing mode will be 'modem' after next restart"); break;
    default: ModemOut(u, 1, "ERROR, unable to save - hardware error"); break;
  }
}


void ModemOutSetRoutingModeServer(const uchar u)
{
  uchar bRoutingMode = 0;
  const ulong code = SaveChar(&bRoutingMode, mpenRoutingModes[u]->dwEepRom);

  switch (code) {
    case 0: ModemOut(u, 0, "OK, routing mode will be 'server' after next restart"); break;
    default: ModemOut(u, 1, "ERROR, unable to save - hardware error"); break;
  }
}


void RunModem(const uchar u)
{
  if ((mbModemMode[u] == MM_COMMAND) && (mbInputMode[u] == IM_READY))
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
    } else if (IsModemCmd(u, "at-dc")) {
      if (mbDisconnect[u] == DC_NORMALLY)
        ModemOut(u, 0, "NORMALLY, disconnected normally");
      else if (mbDisconnect[u] == DC_TIMEOUT)
        ModemOut(u, 1, "TIMEOUT, disconnected by timeout");
      else if (mbDisconnect[u] == DC_REMOTE)
        ModemOut(u, 2, "REMOTE, disconnected by remote host");
      else
        ModemOut(u, 3, "UNKNOWN, never disconnected");
    } else if (IsModemCmd(u, "at-frm")) {
      ModemOutGetRoutingMode(u);
    } else if (IsModemCmd(u, "at-frm=modem")) {
      ModemOutSetRoutingModeModem(u);
    } else if (IsModemCmd(u, "at-frm=server")) {
      ModemOutSetRoutingModeServer(u);
    } else {
      ModemOut(u, 4, "ERROR, unknown command");
    }

    mbInputMode[u] = IM_BEGIN;
  }

  if (mbModemMode[u] == MM_DATA) {
    if (mbEscapeMode[u] == EM_PAUSE_AFTER) {
      mbModemMode[u] = MM_COMMAND;
      ModemOut(u, 0, "OK, command mode");
      mbEscapeMode[u] = EM_BEGIN;
    }
  }
}
