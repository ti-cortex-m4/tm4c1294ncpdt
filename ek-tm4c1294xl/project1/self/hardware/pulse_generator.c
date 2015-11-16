/*------------------------------------------------------------------------------
PULSE_GENERATOR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "pulse_generator.h"



uchar   bPulseGenerator;


void    PulseGeneratorIntHandler(void)
{
  if (GPIOIntStatus(GPIO_PORTP_BASE, false) & GPIO_PIN_5)
  {
    bPulseGenerator++;
    GPIOIntClear(GPIO_PORTP_BASE, GPIO_PIN_5);
  }
}



void    InitPulseGenerator(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);

  GPIOPinTypeGPIOInput(GPIO_PORTP_BASE, GPIO_PIN_5);
  GPIOPadConfigSet(GPIO_PORTP_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

  GPIOIntDisable(GPIO_PORTP_BASE, GPIO_PIN_5);
  GPIOIntClear(GPIO_PORTP_BASE, GPIO_PIN_5);
  GPIOIntRegister(GPIO_PORTP_BASE, PulseGeneratorIntHandler);
  GPIOIntTypeSet(GPIO_PORTP_BASE, GPIO_PIN_5, GPIO_FALLING_EDGE);
  GPIOIntEnable(GPIO_PORTP_BASE, GPIO_PIN_5);
}
