/*------------------------------------------------------------------------------
io_mode.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "../hardware/delay.h"
#include "io_mode.h"



ioMode mIoModes[UART_COUNT];



static void InputMode0(void)
{
}

static void OutputMode0(void)
{
}


static void InputMode1(void)
{
  mIoModes[1] = IO_MODE_INPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0020) = ~0x0008;
}

static void OutputMode1(void)
{
  mIoModes[1] = IO_MODE_OUTPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0020) = 0x0008;
}


static void InputMode2(void)
{
  mIoModes[2] = IO_MODE_INPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0010) = ~0x0004;
}

static void OutputMode2(void)
{
  mIoModes[2] = IO_MODE_OUTPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0010) = 0x0004;
}

/*
static void InputMode3(void)
{
  mIoModes[3] = IO_MODE_INPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0008) = ~0x0002;
}

static void OutputMode3(void)
{
  mIoModes[3] = IO_MODE_OUTPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0008) = 0x0002;
}


static void InputMode4(void)
{
  mIoModes[4] = IO_MODE_INPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0004) = ~0x0001;
}

static void OutputMode4(void)
{
  mIoModes[4] = IO_MODE_OUTPUT;
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0004) = 0x0001;
}
*/


typedef void (*fn_io_mode)(void);


fn_io_mode mfnInputModes[UART_COUNT] =
{
  &InputMode0,
  &InputMode1,
  &InputMode2,
//  &InputMode3,
//  &InputMode4,
};

fn_io_mode mfnOutputModes[UART_COUNT] =
{
  &OutputMode0,
  &OutputMode1,
  &OutputMode2,
//  &OutputMode3,
//  &OutputMode4,
};



void InputMode(uchar u)
{
  ASSERT(u < UART_COUNT);
  (*mfnInputModes[u])();
}


void OutputMode(uchar u)
{
  ASSERT(u < UART_COUNT);
  (*mfnOutputModes[u])();
}



static void InitIoMode0(void)
{
}

static void InitIoMode1(void) // PF3
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0008; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0008; // GPIO Digital Enable

  InputMode(1);
}

static void InitIoMode2(void) // PF2
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0004; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0004; // GPIO Digital Enable

  InputMode(2);
}
/*
static void InitIoMode3(void) // PF1
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0002; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0002; // GPIO Digital Enable

  InputMode(3);
}

static void InitIoMode4(void) // PF0
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0001; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0001; // GPIO Digital Enable

  InputMode(4);
}
*/

void InitIoModes(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    mIoModes[u] = IO_MODE_DEFAULT;
  }

  InitIoMode0();
  InitIoMode1();
  InitIoMode2();
//  InitIoMode3();
//  InitIoMode4();
}
