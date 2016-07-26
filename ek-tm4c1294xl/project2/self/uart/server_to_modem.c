/*------------------------------------------------------------------------------
server_to_modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "server_to_modem.h"



volatile uchar          mbFallbackCnt[UART_COUNT];
volatile escape_mode_t  mbFallbackMode[UART_COUNT];



void InitServerToModem(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    mbFallbackCnt[u] = 0;
    mbFallbackMode[u] = FM_BEGIN;
  }
}


//void ProcessModemModeData(const uchar u, const uchar b)
//{
//  if (IsServerToModem(u))
//  {
//    mbFallbackCnt[u] = 0;
//
//    if ((mbFallbackMode[u] == FM_PAUSE_BEFORE) && (b == '+'))
//      mbFallbackMode[u] = FM_PLUS_1;
//    else if ((mbFallbackMode[u] == FM_PLUS_1) && (b == '+'))
//      mbFallbackMode[u] = FM_PLUS_2;
//    else if ((mbFallbackMode[u] == FM_PLUS_2) && (b == '+'))
//      mbFallbackMode[u] = FM_PLUS_3;
//    else
//      mbFallbackMode[u] = FM_BEGIN;
//  }
//}


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



//        if (bT == szPacketCRC[ibPacket0])
//        {
//          if (++ibPacket0 >= bPACKET_HEADER)
//          {
//            ibPacket0 = 0;
//            mpSerial[0] = SER_PACKET_HEADER;
//            iwInBuff0 = 0;
//          }
//        }
//        else if (bT != szPacketCRC[0]) ibPacket0 = 0;
