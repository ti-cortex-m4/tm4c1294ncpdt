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



void InitLEDs(void)
{
  GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6);

  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_4, 0);
  GPIOPadConfigSet(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
}



void OffLED1(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4, GPIO_PIN_4);
}

void OnLED1(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4, 0);
}


void OffLED2(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, GPIO_PIN_6);
}

void OnLED2(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, 0);
}



void InitEthernetLEDs(void)
{
  GPIOPinConfigure(GPIO_PK4_EN0LED0);
  GPIOPinConfigure(GPIO_PK6_EN0LED1);

  GPIOPinTypeEthernetLED(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6);
}
