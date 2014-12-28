/*------------------------------------------------------------------------------
DELAY.C 


------------------------------------------------------------------------------*/

#include        "main.h"
#include 		"driverlib/sysctl.h"



void    Delay(uint  wMSec)
{
  if (wMSec == 0) return;

  while (wMSec-- > 0) {
    SysCtlDelay(1000);
  }
}



void    DelayMsg(void) {
  Delay(1500);
}


void    DelayInf(void) {
  Delay(500);
}


void    DelayOff(void) {
  Delay(100);
}
