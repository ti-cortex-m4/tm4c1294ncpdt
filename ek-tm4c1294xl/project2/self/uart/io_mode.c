/*------------------------------------------------------------------------------
io_mode.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "../hardware/delay.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "io_mode.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"



#ifndef SINGLE_UART

static ioMode           mbIOModes[UART_COUNT];



static void InMode0(void)
{
}

static void OutMode0(void)
{
}


static void InMode1(void)
{
  mbIOModes[1] = IO_MODE_INPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0020) = ~0x0008;
}

static void OutMode1(void)
{
  mbIOModes[1] = IO_MODE_OUTPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0020) = 0x0008;
}


static void InMode2(void)
{
  mbIOModes[2] = IO_MODE_INPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0010) = ~0x0004;
}

static void OutMode2(void)
{
  mbIOModes[2] = IO_MODE_OUTPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0010) = 0x0004;
}


static void InMode3(void)
{
  mbIOModes[3] = IO_MODE_INPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0008) = ~0x0002;
}

static void OutMode3(void)
{
  mbIOModes[3] = IO_MODE_OUTPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0008) = 0x0002;
}


static void InMode4(void)
{
  mbIOModes[4] = IO_MODE_INPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0004) = ~0x0001;
}

static void OutMode4(void)
{
  mbIOModes[4] = IO_MODE_OUTPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0004) = 0x0001;
}



typedef void (*fn_io_mode)(void);


static const fn_io_mode mfnInModes[UART_COUNT] =
{
  &InMode0,
  &InMode1,
  &InMode2,
  &InMode3,
  &InMode4,
};

static const fn_io_mode mfnOutModes[UART_COUNT] =
{
  &OutMode0,
  &OutMode1,
  &OutMode2,
  &OutMode3,
  &OutMode4,
};



void InMode(uchar u)
{
  ASSERT(u < UART_COUNT);

  if (fIOModeDebugFlag)
    CONSOLE("[%u] in mode\n",u);

  (*mfnInModes[u])();
}


void OutMode(uchar u)
{
  ASSERT(u < UART_COUNT);

  if (fIOModeDebugFlag)
    CONSOLE("[%u] out mode\n",u);

  (*mfnOutModes[u])();
}



static void InitIOMode0(void)
{
}

static void InitIOMode1(void) // PF3
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0008; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0008; // GPIO Digital Enable
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

  InMode(1);
}

static void InitIOMode2(void) // PF2
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0004; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0004; // GPIO Digital Enable
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

  InMode(2);
}

static void InitIOMode3(void) // PF1
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0002; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0002; // GPIO Digital Enable
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

  InMode(3);
}

static void InitIOMode4(void) // PF0
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0001; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0001; // GPIO Digital Enable
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

  InMode(4);
}


void InitIOModes(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    mbIOModes[u] = IO_MODE_DEFAULT;
  }

  InitIOMode0();
  InitIOMode1();
  InitIOMode2();
  InitIOMode3();
  InitIOMode4();
}



ioMode GetIOMode(uchar u)
{
  ASSERT(u < UART_COUNT);
  return mbIOModes[u];
}

#else

void InMode(uchar u)
{
  ASSERT(u < UART_COUNT);
}


void OutMode(uchar u)
{
  ASSERT(u < UART_COUNT);
}


void InitIOModes(void)
{
}



ioMode GetIOMode(uchar u)
{
  ASSERT(u < UART_COUNT);
  return IO_MODE_DEFAULT;
}

#endif
