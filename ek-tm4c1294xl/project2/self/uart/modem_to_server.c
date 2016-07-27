/*------------------------------------------------------------------------------
modem_to_server.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "modem_to_server.h"



static volatile uchar  mbTimeout[UART_COUNT];



void InitModemToServer(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    mbTimeout[u] = 0;
  }
}


static bool IsModemToServer(const uchar u)
{
  return (mbRoutingMode[u] == ROUTING_MODE_CLIENT_MODEM) && (mbModemToServerTimeout[u] > 0);
}


void ProcessModemToServerData(const uchar u, const uchar b)
{
  if IsModemToServer(u)
  {
    mbTimeout[u] = 0;
  }
}



void ModemToServer_1Hz(void)
{
  uchar u;
  for (u=0; u<UART_COUNT; u++)
  {
    if (IsModemToServer(u))
    {
      if (++mbTimeout[u] > mbModemToServerTimeout[u])
      {
      }
    }
  }
}


void RunServerToModem(const uchar u)
{
//  if (mbFallbackMode[u] == FM_PAUSE_AFTER)
  {
    ModemSetVerbose(false);

    ModemOutSetRoutingModeServer(u);
    DelayMilliSecond(100);
    Restart();
  }
}
