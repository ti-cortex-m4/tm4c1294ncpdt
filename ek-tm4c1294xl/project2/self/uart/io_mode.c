/*------------------------------------------------------------------------------
io.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "io_mode.h"


typedef void (*fn_io_mode)(bool fOutput);


//static ioMode mIoModes[UART_COUNT];



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


static void IoMode0(bool fOutput) {
}


static void IoMode1(bool fOutput) {
}


static void IoMode2(bool fOutput) {
}


/*static*/ fn_io_mode mFnIoModes[UART_COUNT] = {
  &IoMode0,
  &IoMode1,
  &IoMode2,
};


void IoMode(uchar u, bool fOutput)
{
  ASSERT(u < UART_COUNT);
  mFnIoModes(u, fOutput);
}


#if 0
void    InitSerial2(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R3; // GPIO Port D Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x0020; // GPIO Direction
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x0020; // GPIO Digital Enable

  InputMode2();
}
#endif
