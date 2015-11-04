/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of and a contribution to the lwIP TCP/IP stack.
 *
 * Credits go to Adam Dunkels (and the current maintainers) of this software.
 *
 * Christiaan Simons rewrote this file to get a more stable echo example.
 */

/**
 * @file
 * TCP echo server example using raw API.
 *
 * Echos all bytes sent by connecting client,
 * and passively closes when client is done.
 *
 */


#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "serial1.h"
#include "timer1.h"


#if LWIP_TCP

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
  u8_t retries;
  struct tcp_pcb *pcb;
  /* pbuf (chain) to recycle */
  struct pbuf *p;
};

err_t echo_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
err_t echo_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
void echo_error(void *arg, err_t err);
err_t echo_poll(void *arg, struct tcp_pcb *tpcb);
err_t echo_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
void echo_send(struct tcp_pcb *tpcb, struct echo_state *es);
void echo_close(struct tcp_pcb *tpcb, struct echo_state *es);

void timer(void) {
  UARTprintf("%05u.%03u ", (dwTimer / 1000), (dwTimer % 1000));
}

void
echo_init(void)
{
  UARTprintf("*** echo_init start \n");

  echo_pcb = tcp_new();
  if (echo_pcb != NULL)
  {
    err_t err;

    err = tcp_bind(echo_pcb, IP_ADDR_ANY, 1001);
    if (err == ERR_OK)
    {
      echo_pcb = tcp_listen(echo_pcb);
      tcp_accept(echo_pcb, echo_accept);
    }
    else 
    {
      UARTprintf("*** abort? output diagnostic? 1 \n");
      /* abort? output diagnostic? */
    }
  }
  else
  {
    UARTprintf("*** abort? output diagnostic? 2 \n");
    /* abort? output diagnostic? */
  }
  UARTprintf("*** echo_init stop \n");
}


err_t
echo_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  UARTprintf("*** echo_accept start \n");

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
    es->retries = 0;
    es->p = NULL;
    /* pass newly allocated es to our callbacks */
    tcp_arg(newpcb, es);
    tcp_recv(newpcb, echo_recv);
    tcp_err(newpcb, echo_error);
    tcp_poll(newpcb, echo_poll, 0);
    ret_err = ERR_OK;
  }
  else
  {
    ret_err = ERR_MEM;
    UARTprintf("***  ERR_MEM \n");
  }

  UARTprintf("*** echo_accept stop \n");
  return ret_err;  
}

err_t
echo_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  timer(); UARTprintf(">>>  echo_recv start \n");

  struct echo_state *es;
  err_t ret_err;

  LWIP_ASSERT("arg != NULL",arg != NULL);
  es = (struct echo_state *)arg;
  if (p == NULL)
  {
    UARTprintf(">>>  remote host closed connection \n");
    /* remote host closed connection */
    es->state = ES_CLOSING;
    if(es->p == NULL)
    {
       UARTprintf(">>>  we're done sending, close it \n");
       /* we're done sending, close it */
       echo_close(tpcb, es);
    }
    else
    {
   	  UARTprintf(">>>  we're not done yet \n");
      /* we're not done yet */
      tcp_sent(tpcb, echo_sent);
      echo_send(tpcb, es);
    }
    ret_err = ERR_OK;
  }
  else if(err != ERR_OK)
  {
    UARTprintf(">>>  cleanup, for unkown reason \n");
    /* cleanup, for unkown reason */
    if (p != NULL)
    {
      es->p = NULL;
      pbuf_free(p);
    }
    ret_err = err;
  }
  else if(es->state == ES_ACCEPTED)
  {
	  UARTprintf(">>>  first data chunk \n");
    /* first data chunk in p->payload */
    es->state = ES_RECEIVED;
    /* store reference to incoming pbuf (chain) */
    es->p = p;
    /* install send completion notifier */
    tcp_sent(tpcb, echo_sent);
    echo_send(tpcb, es);
    ret_err = ERR_OK;
  }
  else if (es->state == ES_RECEIVED)
  {
    UARTprintf(">>>  read some more data \n");
    /* read some more data */
    if(es->p == NULL)
    {
      UARTprintf(">>>  read some more data 1 \n");
      es->p = p;
      tcp_sent(tpcb, echo_sent);
      echo_send(tpcb, es);
    }
    else
    {
      UARTprintf(">>>  read some more data 2 \n");
      struct pbuf *ptr;

      /* chain pbufs to the end of what we recv'ed previously  */
      ptr = es->p;
      pbuf_chain(ptr,p);
    }
    ret_err = ERR_OK;
  }
  else if(es->state == ES_CLOSING)
  {
    UARTprintf(">>>  odd case, remote side closing twice, trash data \n");
    /* odd case, remote side closing twice, trash data */
    tcp_recved(tpcb, p->tot_len);
    es->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  else
  {
    UARTprintf(">>>  unkown es->state, trash data \n");
    /* unkown es->state, trash data  */
    tcp_recved(tpcb, p->tot_len);
    es->p = NULL;
    pbuf_free(p);
    ret_err = ERR_OK;
  }

  timer(); UARTprintf(">>>  echo_recv stop, err=%u \n\n", ret_err);
  return ret_err;
}

void
echo_error(void *arg, err_t err)
{
  UARTprintf("*** echo_error \n");
  struct echo_state *es;

  LWIP_UNUSED_ARG(err);

  es = (struct echo_state *)arg;
  if (es != NULL)
  {
    mem_free(es);
  }
}

void uart_poll(struct tcp_pcb *tpcb)
{
static u8_t buff[100];
u16_t i,c;

    if (cwIn > 0) UARTprintf(" \n");

    c = 0;
    for (i=0; i<100; i++) {
    	if (cwIn > 0) {
    		cwIn--;
    		buff[i] = mpbIn[iwInStart];

//    		UARTprintf("%X > %02X \n",iwInStart,buff[i]);

    		iwInStart++;
    		iwInStart = iwInStart % wINBUFF_SIZE;
    		c++;
    	}
    	else
    		break;
    }

    if (cwIn > 0) UARTprintf(" \n");

	if (c > 0) tcp_write(tpcb, buff, c, 1);
}

err_t
echo_poll(void *arg, struct tcp_pcb *tpcb)
{
//  UARTprintf("--- echo_poll start \n");

  err_t ret_err;
  struct echo_state *es;

  es = (struct echo_state *)arg;
  if (es != NULL)
  {
    if (es->p != NULL)
    {
      UARTprintf("--- there is a remaining pbuf (chain) \n");
      /* there is a remaining pbuf (chain)  */
      tcp_sent(tpcb, echo_sent);
      echo_send(tpcb, es);
    }
    else
    {
//      UARTprintf("--- no remaining pbuf (chain) \n");
      /* no remaining pbuf (chain)  */
      if(es->state == ES_CLOSING)
      {
        echo_close(tpcb, es);
      }
    }
    ret_err = ERR_OK;
  }
  else
  {
  	UARTprintf("--- nothing to be done \n");

    /* nothing to be done */
    tcp_abort(tpcb);
    ret_err = ERR_ABRT;
  }

//  UARTprintf("--- echo_poll stop \n");

//  uart_poll(tpcb);
  return ret_err;
}

err_t
echo_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  timer(); UARTprintf("+++ echo_sent start \n");
  struct echo_state *es;

  LWIP_UNUSED_ARG(len);

  es = (struct echo_state *)arg;
  es->retries = 0;
  
  if(es->p != NULL)
  {
    UARTprintf("+++ still got pbufs to send \n");
    /* still got pbufs to send */
    tcp_sent(tpcb, echo_sent);
    echo_send(tpcb, es);
  }
  else
  {
    UARTprintf("+++ no more pbufs to send \n");

    /* no more pbufs to send */
    if(es->state == ES_CLOSING)
    {
      echo_close(tpcb, es);
    }
  }

  timer(); UARTprintf("+++ echo_sent stop \n");
  return ERR_OK;
}

void uart_out(struct tcp_pcb *tpcb, void *arg, u16_t len);

void
echo_send(struct tcp_pcb *tpcb, struct echo_state *es)
{
  timer(); UARTprintf("<<< echo_send2 start \n");

  struct pbuf *ptr;
//  err_t wr_err = ERR_OK;

  while (/*(wr_err == ERR_OK) &&*/
         (es->p != NULL)/* &&
         (es->p->len <= tcp_sndbuf(tpcb))*/)
  {
  UARTprintf("<<< while \n");
  ptr = es->p;

  /* enqueue data for transmission */
  UARTprintf("<<<  length=%u \n", ptr->len);

  uart_out(tpcb, ptr->payload, ptr->len);
  //wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);

//  if (wr_err == ERR_OK)
  {
//     UARTprintf("<<< ERR_OK \n");

     u16_t plen;
      u8_t freed;

     plen = ptr->len;
     /* continue with next pbuf in chain (if any) */
     es->p = ptr->next;
     if(es->p != NULL)
     {
       /* new reference! */
       pbuf_ref(es->p);
     }
     /* chop first pbuf from chain */
      do
      {
        /* try hard to free pbuf */
        freed = pbuf_free(ptr);
      }
      while(freed == 0);
     /* we can read more data now */
     tcp_recved(tpcb, plen);
   }
  }

  timer(); UARTprintf("<<< echo_send2 stop \n");
}

void uart_in(u8_t b)
{

}

void
echo_send3(struct tcp_pcb *tpcb, struct echo_state *es)
{
  UARTprintf("<<< echo_send start \n");

  struct pbuf *ptr;
  err_t wr_err = ERR_OK;
 
  while ((wr_err == ERR_OK) &&
         (es->p != NULL) && 
         (es->p->len <= tcp_sndbuf(tpcb)))
  {
  UARTprintf("<<< while \n");
  ptr = es->p;

  /* enqueue data for transmission */
  UARTprintf("<<< enqueue data for transmission, length=%u \n", ptr->len);

  wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
  if (wr_err == ERR_OK)
  {
     UARTprintf("<<< ERR_OK \n");

     u16_t plen;
      u8_t freed;

     plen = ptr->len;
     /* continue with next pbuf in chain (if any) */
     es->p = ptr->next;
     if(es->p != NULL)
     {
       /* new reference! */
       pbuf_ref(es->p);
     }
     /* chop first pbuf from chain */
      do
      {
        /* try hard to free pbuf */
        freed = pbuf_free(ptr);
      }
      while(freed == 0);
     /* we can read more data now */
     tcp_recved(tpcb, plen);
   }
   else if(wr_err == ERR_MEM)
   {
     UARTprintf("<<< ERR_MEM \n");
      /* we are low on memory, try later / harder, defer to poll */
     es->p = ptr;
   }
   else
   {
     UARTprintf("<<< other problem ?? \n");
     /* other problem ?? */
   }
  }

  UARTprintf("<<< echo_send stop \n");
}

void
echo_close(struct tcp_pcb *tpcb, struct echo_state *es)
{
  UARTprintf("*** echo_close start \n");
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);
  
  if (es != NULL)
  {
    mem_free(es);
  }  
  tcp_close(tpcb);
  UARTprintf("*** echo_close stop \n");
}

#endif /* LWIP_TCP */
