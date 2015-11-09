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



void    UART_Out(struct tcp_pcb *tpcb, void *arg, uint len)
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
static uchar mbBuff[100];

  if (cwIn == 0) return;

  uint len = 0;

  uint i;
  for (i=0; i<sizeof(mbBuff)/sizeof(uchar); i++)
  {
    if (cwIn > 0)
    {
      cwIn--;

      mbBuff[i] = mbIn[iwInStart];
      len++;

      iwInStart = (iwInStart+1) % INBUFF_SIZE;
    }
    else break;
  }

  if (len > 0)
  {
    tcp_write(tpcb, mbBuff, len, TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);
  }
}


void    UART_1000Hz(void)
{
  if (cwIn > 0)
  {
    if (++wInTimer > 2)
    {
      if (uart_tpcb != NULL)
      {
        UART_In(uart_tpcb);
      }
    }
  }
}
