/*------------------------------------------------------------------------------
operations.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "../tcp/telnet.h"
#include "entity.h"
#include "operations.h"



void Operation1(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    if (mbRoutingMode[u] == ROUTING_MODE_SERVER)
    {
      DEBUG_MSG("Channel %u listens as server on port %u\n", u, mwPort[u]);
      TelnetListen(mwPort[u], u);
    }
    else
    {
      if (mbConnectionMode[u] == CONNECTION_MODE_IMMEDIATELY)
      {
        ulong dwIP = mdwDestinationIP[u];

        DEBUG_MSG("Channel %u immediately connects as client to %u.%u.%u.%u port %u\n",
          u,
          (dwIP >> 24), (dwIP >> 16) & 0xFF, (dwIP >> 8) & 0xFF, dwIP & 0xFF,
          mwDestinationPort[u]);

        TelnetOpen(mdwDestinationIP[u], mwDestinationPort[u], u);
      }
    }
  }
}



void Operation2(void)
{
}
