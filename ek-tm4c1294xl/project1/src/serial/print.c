/*------------------------------------------------------------------------------
PRINT.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "utils/uartstdio.h"
#include        "inc/hw_ints.h"
#include        "driverlib/interrupt.h"
#include        "print.h"



void    PrintStart(void) {
  IntEnable(INT_UART0);
}


void    PrintString(const char  *psz) {
  UARTprintf(psz);
}


void    PrintChar(uchar  b) {
  UARTprintf("u", b);
}


void    PrintInt(uint  w) {
  UARTprintf("u", w);
}


void    PrintTime(time  ti) {
  UARTprintf("%02u:%02u:%02u %02u.%02u.%02u",
             ti.bHour,
             ti.bMinute,
             ti.bSecond,
             ti.bDay,
             ti.bMonth,
             ti.bYear);
}


void    PrintStop(void) {
	IntDisable(INT_UART0);
}
