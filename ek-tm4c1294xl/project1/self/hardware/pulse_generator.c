/*------------------------------------------------------------------------------
PULSE_GENERATOR.C

Генератор 1 Гц
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "../time/delay.h"
#include "pulse_generator.h"



static volatile bool    fOutput;
static volatile uint    cwOutput;



static void OutputOn(void)
{
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0020) = 0x0008;
}


static void OutputOff(void)
{
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0020) = ~0x0008;
}



void PulseGeneratorIntHandler(void)
{
  if (GPIOIntStatus(GPIO_PORTP_BASE, false) & GPIO_PIN_5)
  {
    GPIOIntClear(GPIO_PORTP_BASE, GPIO_PIN_5);

    cwOutput = 0;
    fOutput = true;
    OutputOn();
  }
}



void PulseGenerator_350Hz(void)
{
  if (fOutput == true)
  {
    if (++cwOutput > wFREQUENCY_T0/2)
    {
      fOutput = false;
      OutputOff();
    }
  }
}



static void InitInput(void)
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


static void InitOutput(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) |= 0x0008; // GPIO Direction
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DEN) |= 0x0008; // GPIO Digital Enable
}


void InitPulseGenerator(void)
{
  InitInput();
  InitOutput();
}
