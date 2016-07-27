/*------------------------------------------------------------------------------
modem_to_server.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/restart.h"
#include "../kernel/settings.h"
#include "modem.h"
#include "modem_to_server.h"



static volatile mts_t   mbFallbackMode[UART_COUNT];
static volatile uchar   mbTimeout[UART_COUNT];



void InitModemToServer(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    mbTimeout[u] = 0;
    mbFallbackMode[u] = MTS_BEGIN;
  }
}


static bool IsModemToServer(const uchar u)
{
  return (mbRoutingMode[u] == ROUTING_MODE_CLIENT_MODEM) && (mbModemToServerTimeout[u] > 0);
}


void ProcessModemToServerData(const uchar u)
{
  if (IsModemToServer(u))
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
        mbFallbackMode[u] = MTS_TIMEOUT;
      }
    }
  }
}


void RunModemToServer(const uchar u)
{
  if (IsModemToServer(u) == true)
  {
    if (mbFallbackMode[u] == MTS_TIMEOUT)
    {
      ModemSetVerbose(false);

      ModemOutSetRoutingModeServer(u);
      DelayMilliSecond(100);
      Restart();
    }
  }
}
