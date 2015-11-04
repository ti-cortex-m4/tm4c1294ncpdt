/*------------------------------------------------------------------------------
SERIAL1!C


------------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"

void timer(void);
void  InitUart4(uint32_t ui32SysClock);



#define wINBUFF_SIZE    0x1000
#define wOUTBUFF_SIZE   0x1000

volatile u8_t                    mpbIn[wINBUFF_SIZE], mpbOut[wOUTBUFF_SIZE];

volatile uint32_t                   iwOutStart,iwOutStop,cwOut;
volatile uint32_t                   iwInStart,iwInStop,cwIn;
struct tcp_pcb *tpcb2;

void InitTimer1(uint32_t ui32SysClock);

void init_uart(uint32_t ui32SysClockFreq)
{
  InitUart4(ui32SysClockFreq);

  iwOutStart = 0;
  iwOutStop = 0;
  cwOut = 0;

  iwInStart = 0;
  iwInStop = 0;
  cwIn = 0;

  InitTimer1(ui32SysClockFreq);

  IntMasterEnable();
}

void uart_out(struct tcp_pcb *tpcb, void *arg, u16_t len)
{
  tpcb2 = tpcb;
  u8_t* ptr = arg;

  while (len-- > 0)
  {
    mpbOut[iwOutStop] = (*ptr++);
    iwOutStop = (iwOutStop+1) % wOUTBUFF_SIZE;
    cwOut++;
  }

  IntPendSet(INT_UART4);
}


#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"



bool    GetRI3(uint32_t ui32Status) {
  return ((ui32Status & 0x00000010) != 0) || ((ui32Status & 0x00000040) != 0);
}


bool    GetTI3(uint32_t ui32Status) {
  return ((ui32Status & 0x00000020) != 0) || (ui32Status == 0);
}


u8_t	InByte3(void) {
  return HWREG(UART4_BASE + UART_O_DR);
}


void    OutByte3(u8_t  bT) {
	HWREG(UART4_BASE + UART_O_DR) = bT;
}

extern volatile u32_t dwTimeout;
//void uart_in(u8_t b);

void    UART4IntHandler(void)
{
  uint32_t ui32Status = UARTIntStatus(UART4_BASE, true);
  UARTIntClear(UART4_BASE, ui32Status);

    if (GetRI3(ui32Status))
    {
      dwTimeout = 0;

      u8_t b = InByte3();
      mpbIn[iwInStop] = b;
      iwInStop = (iwInStop+1) % wINBUFF_SIZE;
      cwIn++;
    }

    if (GetTI3(ui32Status))
    {
      if (cwOut > 0 )
      {
        cwOut--;
        OutByte3(mpbOut[iwOutStart]);
        iwOutStart = (iwOutStart+1) % wOUTBUFF_SIZE;
      }
    }
}
