/*------------------------------------------------------------------------------
TCP_SERVER.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "tcp_server.h"



err_t InitTCP_Server(void)
{
//  tState *pState = &mtState[0];
//
//  pcb = tcp_new();
//
//  //
//  // Save the requested information and set the TCP callback functions
//  // and arguments.
//  //
//  tcp_arg(pcb, pState);
//
//  //
//  // Set the TCP error callback.
//  //
//  tcp_err(pcb, TelnetError);
//
//  //
//  // Set the callback that will be made after 3 seconds.  This allows us to
//  // reattempt the connection if we do not receive a response.
//  //
//  tcp_poll(pcb, TelnetPoll, (3000 / TCP_SLOW_INTERVAL));
//
//  //
//  // Attempt to connect to the server.
//  //
//  eError = tcp_connect(pcb, &sIPAddr, usTelnetRemotePort, TelnetConnected);
//  if(eError != ERR_OK)
//  {
//      //
//      // Remember the error for later.
//      //
//      pState->eLastErr = eError;
//      return;
//  }
}
