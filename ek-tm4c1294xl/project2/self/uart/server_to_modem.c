/*------------------------------------------------------------------------------
server_to_modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/restart.h"
#include "../kernel/settings.h"
#include "modem.h"
#include "server_to_modem.h"



static volatile uchar   mbFallbackCnt[UART_COUNT];
static volatile stm_t   mbFallbackMode[UART_COUNT];


static const uchar      szPacket[] = "+ restart as modem +";
static volatile uchar   mibPacket[UART_COUNT];



void InitServerToModem(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    mbFallbackCnt[u] = 0;
    mbFallbackMode[u] = STM_BEGIN;

    mibPacket[u] = 0;
  }
}



static bool IsServerToModem(const uchar u)
{
  return (mbRoutingMode[u] == ROUTING_MODE_SERVER) && (mfServerToModem[u] == true);
}



void ProcessServerToModemData(const uchar u, const uchar b)
{
  if (IsServerToModem(u))
  {
    mbFallbackCnt[u] = 0;

    if ((mbFallbackMode[u] == STM_PAUSE_BEFORE) && (b == szPacket[0])) {
      mibPacket[u] = 1;
      mbFallbackMode[u] = STM_DATA;
    } else if ((mbFallbackMode[u] == STM_DATA) && (b == szPacket[mibPacket[u]])) {
      if (++mibPacket[u] >= sizeof(szPacket) - 1) {
        mibPacket[u] = 0;
        mbFallbackMode[u] = STM_DATA_FINISH;
      }
    } else {
      mibPacket[u] = 0;
      mbFallbackMode[u] = STM_BEGIN;
    }
  }
}


void ServerToModem_10Hz(void)
{
  uchar u;
  for (u=0; u<UART_COUNT; u++)
  {
    if (IsServerToModem(u))
    {
      if (mbFallbackCnt[u] >= 10)
      {
        if (mbFallbackMode[u] == STM_BEGIN)
          mbFallbackMode[u] = STM_PAUSE_BEFORE;
        else if (mbFallbackMode[u] == STM_DATA_FINISH)
          mbFallbackMode[u] = STM_PAUSE_AFTER;
      }
      else
        mbFallbackCnt[u]++;
    }
  }
}



void RunServerToModem(const uchar u)
{
  if (IsServerToModem(u) == true)
  {
    if (mbFallbackMode[u] == STM_PAUSE_AFTER)
    {
      ModemSetVerbose(false);

      ModemOutSetRoutingModeModem(u);
      DelayMilliSecond(100);
      Restart();
    }
  }
}
