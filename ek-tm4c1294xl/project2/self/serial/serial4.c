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





volatile uchar          mpbIn[wINBUFF_SIZE], mpbOut[wOUTBUFF_SIZE];

volatile uint           iwOutStart, iwOutStop, cwOut;
volatile uint           iwInStart, iwInStop, cwIn;


volatile ulong dwTimeout;



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
