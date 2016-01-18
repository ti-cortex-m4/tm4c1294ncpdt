/*------------------------------------------------------------------------------
STATE.C


------------------------------------------------------------------------------*/

#include "main.h"
//#include "lwip/opt.h"
//#include "lwip/debug.h"
//#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "state.h"



static tState           mtState[UART_COUNT];



void InitState(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
//    mtState[u].pConnectPCB = NULL;
//    mtState[u].pListenPCB = NULL;
//    mtState[u].eTCPState = STATE_TCP_IDLE;
//    mtState[u].eTelnetState = STATE_NORMAL;
//    mtState[u].ucFlags = 0;
//    mtState[u].ulConnectionTimeout = 0;
//    mtState[u].ulMaxTimeout = 0;
//    mtState[u].ulSerialPort = MAX_S2E_PORTS;
//    mtState[u].usTelnetRemotePort = 0;
//    mtState[u].usTelnetLocalPort = 0;
//    mtState[u].ulTelnetRemoteIP = 0;
//    mtState[u].iBufQRead = 0;
//    mtState[u].iBufQWrite = 0;
//    mtState[u].pBufHead = NULL;
//    mtState[u].pBufCurrent = NULL;
//    mtState[u].ulBufIndex = 0;
//    mtState[u].ulLastTCPSendTime = 0;
//    mtState[u].bLinkLost = false;
//    mtState[u].ucConnectCount = 0;
//    mtState[u].ucReconnectCount = 0;
//    mtState[u].ucErrorCount = 0;
    mtState[u].eLastErr = ERR_OK;
  }
}
