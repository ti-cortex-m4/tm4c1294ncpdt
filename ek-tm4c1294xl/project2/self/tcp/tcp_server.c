/*------------------------------------------------------------------------------
TCP_SERVER.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"
#include "../state.h"
#include "tcp_server.h"



err_t TCPServerInit(void)
{
  return ERR_OK;
}



static void TCPServerError(void *arg, err_t err)
{
}


static err_t TCPServerPoll(void *arg, struct tcp_pcb *pcb)
{
  return ERR_OK;
}


static err_t TCPServerConnected(void *arg, struct tcp_pcb *pcb, err_t err)
{
  return ERR_OK;
}


err_t TCPServerConnect(void)
{
  tState *pState = GetState(0);

  void *pcb = tcp_new();

  // Save the requested information and set the TCP callback functions and arguments.
  tcp_arg(pcb, pState);

  // Set the TCP error callback.
  tcp_err(pcb, TCPServerError);

  // Set the callback that will be made after 3 seconds.  This allows us to reattempt the connection if we do not receive a response.
  tcp_poll(pcb, TCPServerPoll, (3000 / TCP_SLOW_INTERVAL));

  // Attempt to connect to the server.
  err_t eError = tcp_connect(pcb, &sIPAddr, usTelnetRemotePort, TCPServerConnected);
  if (eError != ERR_OK)
  {
    // Remember the error for later.
    pState->eLastErr = eError;
  }

  return eError;
}
