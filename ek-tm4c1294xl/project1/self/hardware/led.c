/*------------------------------------------------------------------------------
led.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
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



void LEDGreenOff(void)
{
#ifndef NO_LED
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_2, GPIO_PIN_2);
#endif
}

void LEDGreenOn(void)
{
#ifndef NO_LED
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_2, 0);
#endif
}


void LEDRedOff(void)
{
#ifndef NO_LED
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, GPIO_PIN_3);
#endif
}

void LEDRedOn(void)
{
#ifndef NO_LED
  GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_3, 0);
#endif
}



void RunLED_StartError(void) {
  static ulong dw = 0;

  dw++;
  if (dw > 0x10000) {
    LEDRedOff();
    LEDGreenOn();
  }
  if (dw > 0x20000) {
    LEDGreenOff();
    LEDRedOn();
    dw = 0;
  }
}

void RunLED_RealTime(void) {
  static ulong dw = 0;

  dw++;
  if (dw > 0x10) {
    LEDGreenOff();
  }
  if (dw > 0x20) {
    LEDGreenOn();
    dw = 0;
  }
}

void RunLED_Reset(void) {
  static ulong dw = 0;
  LEDGreenOn();

  dw++;
  if (dw > 0x40) {
    LEDRedOff();
  }
  if (dw > 0x80) {
    LEDRedOn();
    dw = 0;
  }
}

#endif
