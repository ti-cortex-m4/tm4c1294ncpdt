/*------------------------------------------------------------------------------
tasks,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib_patched.h"
#include "../settings.h"
#include "../tcp/telnet.h"
#include "../uart/serial.h"
#include "entities.h"
#include "tasks.h"



static void StartListen(uchar u)
{
  ASSERT(u < UART_COUNT);

  CONSOLE("%u: listens as server on port %u\n", u, mwPort[u]);
  TelnetListen(mwPort[u], u);
}



static void StartOpen(uchar u)
{
  ASSERT(u < UART_COUNT);

  ulong dwIP = mdwDestinationIP[u];

  CONSOLE("%u: connects as client to %u.%u.%u.%u port %u\n",
    u,
    (dwIP >> 24), (dwIP >> 16) & 0xFF, (dwIP >> 8) & 0xFF, dwIP & 0xFF,
    mwDestinationPort[u]);

  TelnetOpen(mdwDestinationIP[u], mwDestinationPort[u], u);
}



void InitConnections(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    if (mbRoutingMode[u] == ROUTING_MODE_SERVER)
    {
      StartListen(u);
    }
    else
    {
      if (mbConnectionMode[u] == CONNECTION_MODE_IMMEDIATELY)
      {
        CONSOLE("%u: connects as client immediately\n",u);
        StartOpen(u);
      }
    }
  }
}



void TaskConnections(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    if (mbRoutingMode[u] == ROUTING_MODE_CLIENT)
    {
      tTelnetSession *pState = getTelnetSession(u);

      if (mbConnectionMode[u] == CONNECTION_MODE_IMMEDIATELY)
      {
        if (pState->eTCPState == STATE_TCP_IDLE)
        {
          CONSOLE("%u: connects as client immediately after reset\n",u);
          StartOpen(u);
        }
      }
      else if (mbConnectionMode[u] == CONNECTION_MODE_ON_DATA)
      {
        if ((pState->eTCPState == STATE_TCP_IDLE) && SerialReceiveAvailable(pState->ulSerialPort))
        {
          CONSOLE("%u: connects as client on data\n",u);
          StartOpen(u);
        }
      }
      else
      {
        CONSOLE("%u: ERROR connection mode %u\n",u,mbConnectionMode[u]); // TODO restart
      }
    }
  }
}



void TaskLwIpDebug(uint wSeconds)
{
static uint wTimeout;

  if ((fLwIpDebugFlag) && (++wTimeout > wLwIpDebugTimeout))
  {
    wTimeout = 0;
    stats_display();
  }
}
