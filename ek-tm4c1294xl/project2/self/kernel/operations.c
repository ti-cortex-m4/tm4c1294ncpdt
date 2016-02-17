/*------------------------------------------------------------------------------
operations.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "../tcp/telnet.h"
#include "../uart/serial.h"
#include "entity.h"
#include "operations.h"



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



void Operation1(void)
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



void Operation2(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    if (mbRoutingMode[u] == ROUTING_MODE_CLIENT)
    {
      if (mbConnectionMode[u] == CONNECTION_MODE_ON_DATA)
      {
        tTelnetSession *pState = getTelnetSession(u);

        if ((pState->eTCPState == STATE_TCP_IDLE) && SerialReceiveAvailable(pState->ulSerialPort))
        {
          CONSOLE("%u: connects as client on data\n",u);
          StartOpen(u);
        }
      }
    }
  }
}
