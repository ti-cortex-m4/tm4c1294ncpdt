/*------------------------------------------------------------------------------
server_to_modem.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "server_to_modem.h"




//void InitModem(void)
//{
//  uchar u;
//  for(u = 0; u < UART_COUNT; u++)
//  {
//    mbModemMode[u] = MM_COMMAND;
//    mbInputMode[u] = IM_BEGIN;
//
//    mbEscapeCnt[u] = 0;
//    mbEscapeMode[u] = EM_BEGIN;
//
//    mbDisconnect[u] = DC_UNKNOWN;
//  }
//
//  fVerbose = false;
//}
//
//
//void ProcessModemModeData(const uchar u, const uchar b)
//{
//  if (IsModem(u))
//  {
//    mbEscapeCnt[u] = 0;
//
//    if ((mbEscapeMode[u] == EM_PAUSE_BEFORE) && (b == '+'))
//      mbEscapeMode[u] = EM_PLUS_1;
//    else if ((mbEscapeMode[u] == EM_PLUS_1) && (b == '+'))
//      mbEscapeMode[u] = EM_PLUS_2;
//    else if ((mbEscapeMode[u] == EM_PLUS_2) && (b == '+'))
//      mbEscapeMode[u] = EM_PLUS_3;
//    else
//      mbEscapeMode[u] = EM_BEGIN;
//  }
//}
//
//
//void Modem_10Hz(void)
//{
//  uchar u;
//  for (u=0; u<UART_COUNT; u++)
//  {
//    if (IsModem(u))
//    {
//      if (mbEscapeCnt[u] >= 10)
//      {
//        if (mbEscapeMode[u] == EM_BEGIN)
//          mbEscapeMode[u] = EM_PAUSE_BEFORE;
//        else if (mbEscapeMode[u] == EM_PLUS_3)
//          mbEscapeMode[u] = EM_PAUSE_AFTER;
//      }
//      else
//        mbEscapeCnt[u]++;
//    }
//  }
//}
