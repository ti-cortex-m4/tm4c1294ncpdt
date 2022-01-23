/*------------------------------------------------------------------------------
tasks.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib.h"
#include "../kernel/log.h"
#include "settings.h"
#include "../tcp/telnet.h"
#include "../tcp/telnet_listen.h"
#include "../tcp/telnet_open.h"
#include "../uart/serial.h"
#include "../uart/serial_receive.h"
#include "../uart/modem.h"
#include "../uart/modem_to_server.h"
#include "../uart/server_to_modem.h"
#include "entities.h"
#include "console_version.h"
#include "tasks.h"



void StartServerConnection(uchar u)
{
  ASSERT(u < UART_COUNT);

  CONSOLE("%u: listen as server on port %u\n", u, mwPort[u]);
  TelnetListen(mwPort[u], u);
}


void StartClientConnection(uchar u)
{
  ASSERT(u < UART_COUNT);

  ulong dw = mdwDestinationIP[u];
  CONSOLE("%u: connect as client to %u.%u.%u.%u port %u\n",
    u,
    (dw >> 24), (dw >> 16) & 0xFF, (dw >> 8) & 0xFF, dw & 0xFF,
    mwDestinationPort[u]);

  TelnetOpen(mdwDestinationIP[u], mwDestinationPort[u], u);
}



void StartConnection(uchar u)
{
  ASSERT(u < UART_COUNT);

  if (mbRoutingMode[u] == ROUTING_MODE_SERVER)
  {
    StartServerConnection(u);
  }
  else if (mbRoutingMode[u] == ROUTING_MODE_CLIENT)
  {
    if (mbConnectionMode[u] == CONNECTION_MODE_IMMEDIATELY)
    {
      CONSOLE("%u: connect as client immediately\n",u);
      StartClientConnection(u);
    }
  }
  else if (IsModem(u))
  {
  }
  else
  {
    ERROR("%u: wrong routing mode %u\n", u, mbRoutingMode[u]);
  }
}


void StartConnections(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    StartConnection(u);
  }
}



void RunConnections(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    if (mbRoutingMode[u] == ROUTING_MODE_SERVER)
    {
      RunServerToModem(u);
    }
    else if (mbRoutingMode[u] == ROUTING_MODE_CLIENT)
    {
      tState *pState = &g_sState[u];

      if (mbConnectionMode[u] == CONNECTION_MODE_IMMEDIATELY)
      {
        if (pState->eTCPState == STATE_TCP_IDLE)
        {
          CONSOLE("%u: connect as client immediately after reset\n",u);
          StartClientConnection(u);
        }
      }
      else if (mbConnectionMode[u] == CONNECTION_MODE_ON_DATA)
      {
        if ((pState->eTCPState == STATE_TCP_IDLE) && SerialReceiveAvailable(pState->ucSerialPort))
        {
          CONSOLE("%u: connect as client on data\n",u);
          StartClientConnection(u);
        }
      }
      else
      {
        ERROR("%u: wrong connection mode %u", u, mbConnectionMode[u]);
      }
    }
    else if (IsModem(u))
    {
      RunModem(u);
      RunModemToServer(u);
    }
  }
}



void RunLwipDebug(void)
{
static uint wTimeout;

  if ((fLWIPDebugFlag) && (++wTimeout > wLWIPDebugTimeout*10))
  {
    wTimeout = 0;
    stats_display();

#if TCP_DEBUG || TCP_INPUT_DEBUG || TCP_OUTPUT_DEBUG
    tcp_debug_print_pcbs();
#endif

    ConsoleVersion();
  }
}
