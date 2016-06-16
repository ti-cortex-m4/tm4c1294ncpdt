/*------------------------------------------------------------------------------
error.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/interrupt.h"
#include "../kernel/log.h"
#include "../hardware/led.h"
#include "../hardware/delay.h"
#include "../uart/uart_log.h"
#include "version.h"
#include "error.h"



#ifdef DEBUG

void __error__(char *pszFileName, ulong dwLine)
{
  ConsoleVersion();
  CONSOLE("ERROR assert: file %s, line %d\n", pszFileName, dwLine);

  IntMasterDisable();
  InitLEDs();

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
