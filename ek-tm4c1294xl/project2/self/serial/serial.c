/*------------------------------------------------------------------------------
SERIAL1!C


------------------------------------------------------------------------------*/

#include "self/main.h"
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
#include "self/serial/uarts.h"
#include "serial4.h"




struct tcp_pcb *tpcb2;



void init_uart(ulong ui32SysClockFreq)
{
  iwOutStart = 0;
  iwOutStop = 0;
  cwOut = 0;

  iwInStart = 0;
  iwInStop = 0;
  cwIn = 0;

  InitUART4(ui32SysClockFreq);
}



void uart_out(struct tcp_pcb *tpcb, void *arg, u16_t len)
{
  tpcb2 = tpcb;
  uchar* ptr = arg;

  while (len-- > 0)
  {
    mpbOut[iwOutStop] = (*ptr++);
    iwOutStop = (iwOutStop+1) % wOUTBUFF_SIZE;
    cwOut++;
  }

  IntPendSet(INT_UART4);
}



