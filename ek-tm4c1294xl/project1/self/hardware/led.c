/*------------------------------------------------------------------------------
led.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "../time/delay.h"
#include "led.h"



#ifdef NO_DISPLAY

void InitLED(void)
{
  GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_2 | GPIO_PIN_3);

  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_2 | GPIO_PIN_2, 0);
  GPIOPadConfigSet(GPIO_PORTP_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
}



void OffLED0(void)
{
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_2, GPIO_PIN_2);
}

void OnLED0(void)
{
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_2, 0);
}


void OffLED1(void)
{
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, GPIO_PIN_3);
}

void OnLED1(void)
{
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, 0);
}

#endif
