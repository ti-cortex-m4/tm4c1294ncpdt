/*------------------------------------------------------------------------------
server_to_modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/settings.h"
#include "server_to_modem.h"



volatile uchar          mbFallbackCnt[UART_COUNT];
volatile fallback_mode_t mbFallbackMode[UART_COUNT];


static const uchar     szPacket[] = "abc";
static volatile uchar  mibPacket[UART_COUNT];



void InitServerToModem(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    mbFallbackCnt[u] = 0;
    mbFallbackMode[u] = FM_BEGIN;

    mibPacket[u] = 0;
  }
}



bool IsServerToModem(const uchar u)
{
  return (mbRoutingMode[u] == ROUTING_MODE_SERVER) && (mfServerToModem[u] == true);
}



void ProcessServerToModemData(const uchar u, const uchar b)
{
  if (IsServerToModem(u))
  {
    mbFallbackCnt[u] = 0;

    if ((mbFallbackMode[u] == FM_PAUSE_BEFORE) && (b == szPacket[0])) {
      mibPacket[u] = 1;
      mbFallbackMode[u] = FM_DATA;
    } else if ((mbFallbackMode[u] == FM_DATA) && (b == szPacket[mibPacket[u]])) {
      if (++mibPacket[u] >= sizeof(szPacket) - 1) {
        mibPacket[u] = 0;
        mbFallbackMode[u] = FM_DATA_FINISH;
      }
    } else {
      mibPacket[u] = 0;
      mbFallbackMode[u] = FM_BEGIN;
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
        if (mbFallbackMode[u] == FM_BEGIN)
          mbFallbackMode[u] = FM_PAUSE_BEFORE;
        else if (mbFallbackMode[u] == FM_DATA_FINISH)
          mbFallbackMode[u] = FM_PAUSE_AFTER;
      }
      else
        mbFallbackCnt[u]++;
    }
  }
}



void RunServerToModem(const uchar u)
{
  if (mbFallbackMode[u] == FM_PAUSE_AFTER) {
    mbFallbackMode[u] = FM_BEGIN;
  }
}
