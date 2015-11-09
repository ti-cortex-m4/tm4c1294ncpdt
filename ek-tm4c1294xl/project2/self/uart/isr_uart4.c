/*------------------------------------------------------------------------------
ISR_UART4.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "driverlib/uart.h"
#include "isr_uart4.h"



volatile uchar          mbIn[INBUFF_SIZE], mbOut[OUTBUFF_SIZE];

volatile uint           iwOutStart, iwOutStop, cwOut;
volatile uint           iwInStart, iwInStop, cwIn;


volatile uint           wInTimer;



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
    wInTimer = 0;

    cwIn++;
    mbIn[iwInStop] = InByte();
    iwInStop = (iwInStop+1) % INBUFF_SIZE;
  }

  if (GetTI(dwStatus))
  {
    if (cwOut > 0)
    {
      cwOut--;
      OutByte(mbOut[iwOutStart]);
      iwOutStart = (iwOutStart+1) % OUTBUFF_SIZE;
    }
  }
}
