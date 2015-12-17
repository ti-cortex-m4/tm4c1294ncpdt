/*------------------------------------------------------------------------------
TCP_HANDLER.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "../settings.h"
#include "../uart/uart.h"



static struct tcp_pcb *main_pcb;



static err_t HandlerAccept(void *arg, struct tcp_pcb *tpcb, err_t err);
static err_t HandlerReceive(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void HandlerError(void *arg, err_t err);
static err_t HandlerPoll(void *arg, struct tcp_pcb *tpcb);
static err_t HandlerSent(void *arg, struct tcp_pcb *pcb, u16_t len);
static void HandlerClose(struct tcp_pcb *tpcb);



// TODO check result
err_t InitTCP_Handler(void)
{
  main_pcb = tcp_new();
  if (main_pcb == NULL)
  {
    return ERR_MEM;
  }
  else
  {
    err_t err = tcp_bind(main_pcb, IP_ADDR_ANY, wPort);
    if (err == ERR_OK)
    {
      main_pcb = tcp_listen(main_pcb);
      tcp_accept(main_pcb, HandlerAccept);
    }

    return err;
  }
}



static err_t HandlerAccept(void *arg, struct tcp_pcb *tpcb, err_t err)
{
  tcp_setprio(tpcb, TCP_PRIO_MIN);

  tcp_arg(tpcb, NULL);
  tcp_recv(tpcb, HandlerReceive);
  tcp_err(tpcb, HandlerError);
  tcp_poll(tpcb, HandlerPoll, 0);
  tcp_sent(tpcb, HandlerSent);

  return (ERR_OK);
}



// This function is called when the lwIP TCP/IP stack has an incoming packet to be processed.
static err_t HandlerReceive(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
struct pbuf *q;

  // Process the incoming packet.
  if ((err == ERR_OK) && (p != NULL))
  {
    // Accept the packet from TCP.
    tcp_recved(tpcb, p->tot_len);

    (tpcb)->flags &= ~TF_ACK_DELAY;
    (tpcb)->flags |= TF_ACK_NOW;

    // Loop through the pbufs in this packet.
    for(q = p; q != NULL; q = q->next)
    {
      UART_Out1(q->payload, q->len);
    }

    UART_Out2(tpcb);

    // Free the pbuf.
    pbuf_free(p);
  }

  // If a null packet is passed in, close the connection.
  else if ((err == ERR_OK) && (p == NULL))
  {
    HandlerClose(tpcb);
  }

  return (ERR_OK);
}



// This function is called when the lwIP TCP/IP stack has detected an error. The connection is no longer valid.
static void HandlerError(void *arg, err_t err)
{
//  TODO
}



// This function is called when the lwIP TCP/IP stack has no incoming or outgoing data. It can be used to reset an idle connection.
static err_t HandlerPoll(void *arg, struct tcp_pcb *pcb)
{
  return (ERR_OK);
}



// This function is called when the lwIP TCP/IP stack has received an acknowledgment for data that has been transmitted.
static err_t HandlerSent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
  return (ERR_OK);
}



// This function is called when the the TCP connection should be closed.
static void HandlerClose(struct tcp_pcb *tpcb)
{
  // Clear out all of the TCP callbacks.
  tcp_arg(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);
  tcp_sent(tpcb, NULL);

  // Close the TCP connection.
  tcp_close(tpcb);
}
