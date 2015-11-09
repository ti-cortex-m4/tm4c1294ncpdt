/*------------------------------------------------------------------------------
SERIAL1!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "self/tcp/echo.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "hw_uarts.h"
#include "uart4.h"
#include "serial.h"




struct tcp_pcb *tpcb2;



void init_uart(ulong dwSysClockFreq)
{
  iwOutStart = 0;
  iwOutStop = 0;
  cwOut = 0;

  iwInStart = 0;
  iwInStop = 0;
  cwIn = 0;

  InitUART4(dwSysClockFreq);
}



void uart_out(struct tcp_pcb *tpcb, void *arg, u16_t len)
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

void uart_poll(struct tcp_pcb *tpcb);
void Serial_1000Hz(void)
{
	  if (++wInTimer > 2)
	  {

  uart_poll(tpcb2);
	  }
}
