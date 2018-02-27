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
#ifndef NO_LED
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);

  GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_2 | GPIO_PIN_3);

  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_2 | GPIO_PIN_2, 0);
  GPIOPadConfigSet(GPIO_PORTP_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
#endif
}



void OffLED0(void)
{
#ifndef NO_LED
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_2, GPIO_PIN_2);
#endif
}

void OnLED0(void)
{
#ifndef NO_LED
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_2, 0);
#endif
}


void OffLED1(void)
{
#ifndef NO_LED
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, GPIO_PIN_3);
#endif
}

void OnLED1(void)
{
#ifndef NO_LED
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, 0);
#endif
}

#endif
