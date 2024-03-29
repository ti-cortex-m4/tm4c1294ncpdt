/*------------------------------------------------------------------------------
PRINT!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "print.h"



void    PrintStart(void) {
#ifdef ENABLE_PRINT

  IntDisable(INT_UART0);
  UARTStdioConfig(0, 9600, 120000000);

#endif
}


void    PrintStop(void) {
#ifdef ENABLE_PRINT

  IntEnable(INT_UART0);

#endif
}



void    PrintString(const char  *psz) {
#ifdef ENABLE_PRINT

  UARTprintf(psz);

#endif
}


void    PrintChar(uchar  b) {
#ifdef ENABLE_PRINT

  UARTprintf(" %u ", b);

#endif
}


void    PrintInt(uint  w) {
#ifdef ENABLE_PRINT

  UARTprintf(" %u ", w);

#endif
}


void    PrintLong(ulong  dw) {
#ifdef ENABLE_PRINT

  UARTprintf(" %u ", dw);

#endif
}


void    PrintTime(time  ti) {
#ifdef ENABLE_PRINT

  UARTprintf("%02u:%02u:%02u %02u.%02u.%02u",
             ti.bHour,
             ti.bMinute,
             ti.bSecond,
             ti.bDay,
             ti.bMonth,
             ti.bYear);

#endif
}
