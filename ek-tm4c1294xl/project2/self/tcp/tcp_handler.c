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
void echo_error(void *arg, err_t err);
err_t echo_poll(void *arg, struct tcp_pcb *tpcb);
err_t echo_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
void echo_send(struct tcp_pcb *tpcb, struct echo_state *es);
static void HandlerClose(struct tcp_pcb *tpcb);

void
InitTCP_Handler(void)
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
    tcp_recv(newpcb, HandlerReceive);
    tcp_err(newpcb, echo_error);
    tcp_poll(newpcb, echo_poll, 0);
    ret_err = ERR_OK;
  }
  else
  {
    ret_err = ERR_MEM;
  }
  return ret_err;
}


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


void
echo_error(void *arg, err_t err)
{
  struct echo_state *es;

  LWIP_UNUSED_ARG(err);

  es = (struct echo_state *)arg;
  if (es != NULL)
  {
    mem_free(es);
  }
}

err_t
echo_poll(void *arg, struct tcp_pcb *tpcb)
{
//  err_t ret_err;
//  struct echo_state *es;
//
//  es = (struct echo_state *)arg;
//  if (es != NULL)
//  {
//    if (es->p != NULL)
//    {
//      /* there is a remaining pbuf (chain)  */
//      tcp_sent(tpcb, echo_sent);
//      echo_send(tpcb, es);
//    }
//    else
//    {
//      /* no remaining pbuf (chain)  */
//      if(es->state == ES_CLOSING)
//      {
//        HandlerClose(tpcb, es);
//      }
//    }
//    ret_err = ERR_OK;
//  }
//  else
//  {
//    /* nothing to be done */
//    tcp_abort(tpcb);
//    ret_err = ERR_ABRT;
//  }
  return ERR_OK;
}

err_t
echo_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
//  struct echo_state *es;
//
//  LWIP_UNUSED_ARG(len);
//
//  es = (struct echo_state *)arg;
//
//  if(es->p != NULL)
//  {
//    /* still got pbufs to send */
//    tcp_sent(tpcb, echo_sent);
//    echo_send(tpcb, es);
//  }
//  else
//  {
//    /* no more pbufs to send */
//    if(es->state == ES_CLOSING)
//    {
//      HandlerClose(tpcb, es);
//    }
//  }
  return ERR_OK;
}

//void
//echo_send(struct tcp_pcb *tpcb, struct echo_state *es)
//{
//  struct pbuf *ptr;
////  err_t wr_err = ERR_OK;
//
//  while (/*(wr_err == ERR_OK) &&*/
//         (es->p != NULL)/* &&
//         (es->p->len <= tcp_sndbuf(tpcb))*/)
//  {
////  LOG(("<<< while \n"));
//  ptr = es->p;
//
//  /* enqueue data for transmission */
////  LOG(("in=%u\n", ptr->len));
//
//  UART_Out(tpcb, ptr->payload, ptr->len);
//  //wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
//
////  if (wr_err == ERR_OK)
//  {
////     LOG(("<<< ERR_OK \n"));
//
//     u16_t plen;
//      u8_t freed;
//
//     plen = ptr->len;
//     /* continue with next pbuf in chain (if any) */
//     es->p = ptr->next;
//     if(es->p != NULL)
//     {
//       /* new reference! */
//       pbuf_ref(es->p);
//     }
//     /* chop first pbuf from chain */
//      do
//      {
//        /* try hard to free pbuf */
//        freed = pbuf_free(ptr);
//      }
//      while(freed == 0);
//     /* we can read more data now */
////      LOG(("~1 %X\n", tpcb->flags));
//      (tpcb)->flags &= ~TF_ACK_DELAY;
//      (tpcb)->flags |= TF_ACK_NOW;
////      LOG(("~2 %X\n", tpcb->flags));
//     tcp_recved(tpcb, plen);
//   }
//  }
//}


static void HandlerClose(struct tcp_pcb *tpcb)
{
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);

  tcp_close(tpcb);
}
