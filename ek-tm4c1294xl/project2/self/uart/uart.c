/*------------------------------------------------------------------------------
UART.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "lwip/tcp.h"
#include "lwip/def.h"
#include "hw_uart.h"
#include "isr_uart4.h"
#include "uart.h"



static struct tcp_pcb   *uart_tpcb;



void    InitUART(ulong dwSysClockFreq)
{
  iwOutStart = 0;
  iwOutStop = 0;
  cwOut = 0;

  iwInStart = 0;
  iwInStop = 0;
  cwIn = 0;

  uart_tpcb = NULL;

  InitUART4(dwSysClockFreq);
}



void    UART_Out(struct tcp_pcb *tpcb, void *arg, u16_t len)
{
  uart_tpcb = tpcb;

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
u16_t i,len;

  if (cwIn == 0) return;

  len = 0;
  for (i=0; i<100; i++)
  {
    if (cwIn > 0)
    {
      cwIn--;
      buff[i] = mbIn[iwInStart];

      iwInStart++;
      iwInStart = iwInStart % INBUFF_SIZE;
      len++;
    }
    else break;
  }

  if (len > 0)
  {
    tcp_write(tpcb, buff, len, TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);
  }
}


void    UART_1000Hz(void)
{
  if ((++wInTimer > 2) && (cwIn > 0))
  {
    if (uart_tpcb != NULL)
    {
      UART_In(uart_tpcb);
    }
  }
}
