/*------------------------------------------------------------------------------
PRINT2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../../tm4c1294xl/utils/uartstdio.h"
#include "../../tm4c1294xl/driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "print2.h"



void    x_init(void)
{
#ifdef ENABLE_PRINT2

  IntDisable(INT_UART0);
  UARTStdioConfig(0, 57600, 120000000);

#endif
}


void    x_done(void)
{
#ifdef ENABLE_PRINT2

  IntEnable(INT_UART0);

#endif
}



void    x_str(char const  *psz)
{
#ifdef ENABLE_PRINT2

  UARTprintf(psz);

#endif
}


void    x_bytedec(uchar  b)
{
#ifdef ENABLE_PRINT2

  UARTprintf(" %u ", b);

#endif
}


void    x_bytehex(uchar  b)
{
#ifdef ENABLE_PRINT2

  UARTprintf(" %X ", b);

#endif
}


void    x_intdec(uint  w)
{
#ifdef ENABLE_PRINT2

  UARTprintf(" %u ", w);

#endif
}


void    x_longdec(ulong  dw)
{
#ifdef ENABLE_PRINT2

  UARTprintf(" %u ", dw);

#endif
}


void    x_time(time  ti)
{
#ifdef ENABLE_PRINT2

  UARTprintf("%02u:%02u:%02u %02u.%02u.%02u",
             ti.bHour,
             ti.bMinute,
             ti.bSecond,
             ti.bDay,
             ti.bMonth,
             ti.bYear);

#endif
}
