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



static struct tcp_pcb *echo_pcb;

enum echo_states
{
  ES_NONE = 0,
  ES_ACCEPTED,
  ES_RECEIVED,
  ES_CLOSING
};

struct echo_state
{
  u8_t state;
//  u8_t retries;
  struct tcp_pcb *pcb;
  /* pbuf (chain) to recycle */
  struct pbuf *p;
};

err_t echo_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t HandlerReceive(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void HandlerError(void *arg, err_t err);
static err_t HandlerPoll(void *arg, struct tcp_pcb *tpcb);
static err_t HandlerSent(void *arg, struct tcp_pcb *pcb, u16_t len);
static void HandlerClose(struct tcp_pcb *tpcb);



void InitTCP_Handler(void)
{
  echo_pcb = tcp_new();
  if (echo_pcb != NULL)
  {
    err_t err;

    err = tcp_bind(echo_pcb, IP_ADDR_ANY, wPort);
    if (err == ERR_OK)
    {
      echo_pcb = tcp_listen(echo_pcb);
      tcp_accept(echo_pcb, echo_accept);
    }
    else
    {
      /* abort? output diagnostic? */
    }
  }
  else
  {
    /* abort? output diagnostic? */
  }
}


err_t
echo_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t ret_err;
  struct echo_state *es;

  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);

  /* Unless this pcb should have NORMAL priority, set its priority now.
     When running out of pcbs, low priority pcbs can be aborted to create
     new pcbs of higher priority. */
  tcp_setprio(newpcb, TCP_PRIO_MIN);

  es = (struct echo_state *)mem_malloc(sizeof(struct echo_state));
  if (es != NULL)
  {
    es->state = ES_ACCEPTED;
    es->pcb = newpcb;
    es->p = NULL;
    /* pass newly allocated es to our callbacks */
    tcp_arg(newpcb, es);
    tcp_sent(newpcb, HandlerSent);
    tcp_recv(newpcb, HandlerReceive);
    tcp_err(newpcb, HandlerError);
    tcp_poll(newpcb, HandlerPoll, 0);
    ret_err = ERR_OK;
  }
  else
  {
    ret_err = ERR_MEM;
  }
  return ret_err;
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
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);

  // Close the TCP connection.
  tcp_close(tpcb);
}
