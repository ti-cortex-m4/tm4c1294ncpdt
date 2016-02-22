/*------------------------------------------------------------------------------
io.c


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "inc/hw_memmap.h"
//#include "inc/hw_uart.h"
#include "inc/hw_types.h"
//#include "inc/hw_ints.h"
#include "inc/hw_sysctl.h"
//#include "inc/hw_gpio.h"
#include "../hardware/delay.h"
#include "io_mode.h"



typedef void (*fn_io_mode)(void);


ioMode mIoModes[UART_COUNT];



#if 0
void    InputMode2(void) {
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0080) = ~0x0020;
  bPortsStatus &= 0xFE;
}


void    OutputMode2(void) {
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0080) = 0x0020;
  bPortsStatus |= 0x01;
}
#endif


static void InputMode0(void)
{
}

static void OutputMode0(void)
{
}


static void InputMode1(void)
{
}

static void OutputMode1(void)
{
}


static void InputMode2(void)
{
}

static void OutputMode2(void)
{
}



fn_io_mode FnInputModes[UART_COUNT] = {
  &InputMode0,
  &InputMode1,
  &InputMode2,
};

fn_io_mode FnOutputModes[UART_COUNT] = {
  &OutputMode0,
  &OutputMode1,
  &OutputMode2,
};



void InputMode(uchar u)
{
  ASSERT(u < UART_COUNT);

  mIoModes[u] = IO_MODE_INPUT;
  (*FnInputModes[u])();
}


void OutputMode(uchar u)
{
  ASSERT(u < UART_COUNT);

  mIoModes[u] = IO_MODE_OUTPUT;
  (*FnOutputModes[u])();
}



static void InitIoMode1(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R5; // GPIO Port F Run Mode Clock Gating Control
  DelayGPIO();
//  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x0020; // GPIO Direction
//  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x0020; // GPIO Digital Enable
//
//  InputMode2();
}



void InitIoModes(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    mIoModes[u] = IO_MODE_DEFAULT;
  }

//  InitIoMode0();
  InitIoMode1();
//  InitIoMode2();
}
