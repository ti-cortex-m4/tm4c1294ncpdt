/*------------------------------------------------------------------------------
TCP_CLIENT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"
#include "../state.h"
#include "tcp_client.h"



err_t TCPClientInit(void)
{
  return ERR_OK;
}



static void TCPClientError(void *arg, err_t err)
{
}


static err_t TCPClientPoll(void *arg, struct tcp_pcb *pcb)
{
  return ERR_OK;
}


static err_t TCPClientConnected(void *arg, struct tcp_pcb *pcb, err_t err)
{
  return ERR_OK;
}


err_t TCPClientConnect(ulong dwRemoteIP, uint wRemotePort)
{
  tState *pState = GetState(0);

  void *pcb = tcp_new();

  // Save the requested information and set the TCP callback functions and arguments.
  tcp_arg(pcb, pState);

  // Set the TCP error callback.
  tcp_err(pcb, TCPClientError);

  // Set the callback that will be made after 3 seconds.  This allows us to reattempt the connection if we do not receive a response.
  tcp_poll(pcb, TCPClientPoll, (3000 / TCP_SLOW_INTERVAL));

  // Attempt to connect to the server.
  struct ip_addr sIPAddr;
  sIPAddr.addr = htonl(dwRemoteIP);

  err_t eError = tcp_connect(pcb, &sIPAddr, wRemotePort, TCPClientConnected);
  if (eError != ERR_OK)
  {
    // Remember the error for later.
    pState->eLastErr = eError;
  }

  return eError;
}
