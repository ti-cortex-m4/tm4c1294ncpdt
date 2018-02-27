/*------------------------------------------------------------------------------
led.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_emac.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/emac.h"
#include "led.h"



#ifdef NO_DISPLAY

void InitLEDs(void)
{
  GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6);

  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_4, 0);
  GPIOPadConfigSet(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  OnLED0();
  OnLED1();
  DelayMilliSecond(300);
  OffLED0();
  OffLED1();
}



void OffLED0(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4, GPIO_PIN_4);
}

void OnLED0(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4, 0);
}


void OffLED1(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, GPIO_PIN_6);
}

void OnLED1(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, 0);
}

#endif
