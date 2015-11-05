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


extern volatile u32_t dwTimeout;
//void uart_in(uchar b);

void timer(void);



volatile uchar          mpbIn[wINBUFF_SIZE], mpbOut[wOUTBUFF_SIZE];

volatile uint           iwOutStart, iwOutStop, cwOut;
volatile uint           iwInStart, iwInStop, cwIn;



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



static bool GetRI4(ulong dwStatus)
{
  return ((dwStatus & 0x00000010) != 0) || ((dwStatus & 0x00000040) != 0);
}


static bool GetTI4(ulong dwStatus)
{
  return ((dwStatus & 0x00000020) != 0) || (dwStatus == 0);
}


static uchar InByte3(void)
{
  return HWREG(UART4_BASE + UART_O_DR);
}


static void OutByte3(uchar b)
{
  HWREG(UART4_BASE + UART_O_DR) = b;
}



void    UART4IntHandler(void)
{
  ulong dwStatus = UARTIntStatus(UART4_BASE, true);
  UARTIntClear(UART4_BASE, dwStatus);

  if (GetRI4(dwStatus))
  {
    dwTimeout = 0;

    cwIn++;
    mpbIn[iwInStop] = InByte3();
    iwInStop = (iwInStop+1) % wINBUFF_SIZE;
  }

  if (GetTI4(dwStatus))
  {
    if (cwOut > 0 )
    {
      cwOut--;
      OutByte3(mpbOut[iwOutStart]);
      iwOutStart = (iwOutStart+1) % wOUTBUFF_SIZE;
    }
  }
}
