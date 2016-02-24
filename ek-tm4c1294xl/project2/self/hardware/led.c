/*------------------------------------------------------------------------------
led.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_emac.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/emac.h"
#include "led.h"



void InitLED(void)
{
  GPIOPinConfigure(GPIO_PK4_EN0LED0);
  GPIOPinConfigure(GPIO_PK6_EN0LED1);

  GPIOPinTypeEthernetLED(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6);
}
