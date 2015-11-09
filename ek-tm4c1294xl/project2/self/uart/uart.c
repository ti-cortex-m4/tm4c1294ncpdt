/*------------------------------------------------------------------------------
UART.C


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "self/tcp/echo.h"
//#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
//#include "lwip/opt.h"
//#include "lwip/debug.h"
//#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/def.h"
//#include "inc/hw_memmap.h"
//#include "inc/hw_uart.h"
//#include "inc/hw_types.h"
//#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
//#include "driverlib/uart.h"
#include "hw_uart.h"
#include "isr_uart4.h"
#include "uart.h"




static struct tcp_pcb   *tpcb2;



void    InitUART(ulong dwSysClockFreq)
{
  iwOutStart = 0;
  iwOutStop = 0;
  cwOut = 0;

  iwInStart = 0;
  iwInStop = 0;
  cwIn = 0;

  tpcb2 = NULL;

  InitUART4(dwSysClockFreq);
}



void    UART_Out(struct tcp_pcb *tpcb, void *arg, u16_t len)
{
  tpcb2 = tpcb;
  uchar* ptr = arg;

  while (len-- > 0)
  {
    mbOut[iwOutStop] = (*ptr++);
    iwOutStop = (iwOutStop+1) % OUTBUFF_SIZE;
    cwOut++;
  }

  IntPendSet(INT_UART4);
}



static void UART_In(struct tcp_pcb *tpcb)
{
static u8_t buff[100];
u16_t i,c;

    if (cwIn == 0) return;

    c = 0;
    for (i=0; i<100; i++) {
    	if (cwIn > 0) {
    		cwIn--;
    		buff[i] = mbIn[iwInStart];

    		iwInStart++;
    		iwInStart = iwInStart % INBUFF_SIZE;
    		c++;
    	}
    	else break;
    }

	if (c > 0) {
//	      LWIP_PLATFORM_DIAG(("~~~tcp_ack 5 %X\n", tpcb->flags));
//	      (tpcb)->flags &= ~TF_ACK_DELAY;
//	      (tpcb)->flags |= TF_ACK_NOW;
//	      LWIP_PLATFORM_DIAG(("~~~tcp_ack 6 %X\n", tpcb->flags));

//		LOG(("out\n"));
		tcp_write(tpcb, buff, c, 1);
		tcp_output(tpcb);

//	      LWIP_PLATFORM_DIAG(("~~~tcp_ack 5 %X\n", tpcb->flags));
//	      (tpcb)->flags &= ~TF_ACK_DELAY;
//	      (tpcb)->flags |= TF_ACK_NOW;
//	      LWIP_PLATFORM_DIAG(("~~~tcp_ack 6 %X\n", tpcb->flags));
//		LOG(("out=%u\n",c));
	}
}


void UART_1000Hz(void)
{
  if (++wInTimer > 2)
  {
    if (tpcb2 != NULL)
    {
      UART_In(tpcb2);
    }
  }
}
