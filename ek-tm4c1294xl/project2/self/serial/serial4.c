/*------------------------------------------------------------------------------
SERIAL1!C


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "driverlib/interrupt.h"
//#include "inc/hw_ints.h"
//#include "lwip/opt.h"
//#include "lwip/debug.h"
//#include "lwip/stats.h"
//#include "lwip/tcp.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
//#include "inc/hw_ints.h"
//#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
//#include "self/serial/uarts.h"
#include "serial4.h"



volatile uchar          mpbIn[INBUFF_SIZE], mpbOut[OUTBUFF_SIZE];

volatile uint           iwOutStart, iwOutStop, cwOut;
volatile uint           iwInStart, iwInStop, cwIn;


volatile ulong          dwInTimer;



static bool GetRI(ulong dwStatus)
{
  return ((dwStatus & 0x10) != 0) || ((dwStatus & 0x40) != 0);
}


static bool GetTI(ulong dwStatus)
{
  return ((dwStatus & 0x20) != 0) || (dwStatus == 0);
}


static uchar InByte(void)
{
  return HWREG(UART4_BASE + UART_O_DR);
}


static void OutByte(uchar b)
{
  HWREG(UART4_BASE + UART_O_DR) = b;
}



void    UART4IntHandler(void)
{
  ulong dwStatus = UARTIntStatus(UART4_BASE, true);
  UARTIntClear(UART4_BASE, dwStatus);

  if (GetRI(dwStatus))
  {
    dwInTimer = 0;

    cwIn++;
    mpbIn[iwInStop] = InByte();
    iwInStop = (iwInStop+1) % INBUFF_SIZE;
  }

  if (GetTI(dwStatus))
  {
    if (cwOut > 0 )
    {
      cwOut--;
      OutByte(mpbOut[iwOutStart]);
      iwOutStart = (iwOutStart+1) % OUTBUFF_SIZE;
    }
  }
}
