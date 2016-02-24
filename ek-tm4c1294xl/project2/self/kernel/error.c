/*------------------------------------------------------------------------------
error.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/interrupt.h"
#include "../kernel/log.h"
#include "../hardware/led.h"
#include "../hardware/delay.h"
#include "../uart/uart_log.h"
#include "error.h"



#ifdef DEBUG

void __error__(char *pszFileName, ulong dwLine)
{
  CONSOLE("assert error: file %s, line %d\n", pszFileName, dwLine);

  IntMasterDisable();
  while (true)
  {
    OffLED0();
    OffLED1();
    DelayMilliSecond(500);

    OnLED0();
    OnLED1();
    DelayMilliSecond(500);
  }
}

#endif
