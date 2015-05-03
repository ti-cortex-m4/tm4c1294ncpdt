/*------------------------------------------------------------------------------
KEY.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include 		    "inc/hw_gpio.h"
#include 		    "inc/hw_memmap.h"
#include 		    "inc/hw_sysctl.h"
#include 		    "inc/hw_types.h"
#include "../time/delay.h"
#include "keyboard.h"
#include "key.h"



static uchar            bRepeat;        // счётчик для обработка антидребезга
static uchar            bPrevKey;       // код нажатой клавишы за предыдущий период сканирования



void    InitKey(void)
{
#ifdef NATIVE_KEYBOARD

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R12; // GPIO Port N Run Mode Clock Gating Control
  RunClocking();
  HWREG(GPIO_PORTN_BASE + GPIO_O_DIR) &= 0xFFC0; // GPIO Direction
  HWREG(GPIO_PORTN_BASE + GPIO_O_DEN) |= 0x003F; // GPIO Digital Enable

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R7; // GPIO Port H Run Mode Clock Gating Control
  RunClocking();
  HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DIR) &= 0xFFF0; // GPIO Direction
  HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DEN) |= 0x000F; // GPIO Digital Enable

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R14; // GPIO Port Q Run Mode Clock Gating Control
  RunClocking();
  HWREG(GPIO_PORTQ_BASE + GPIO_O_DIR) &= 0xFFF0; // GPIO Direction
  HWREG(GPIO_PORTQ_BASE + GPIO_O_DEN) |= 0x000F; // GPIO Digital Enable

#endif
}



uint    GetKey(void)
{
uint  i = 0;

  if (HWREG((GPIO_PORTN_BASE + GPIO_O_DATA + 0x0004)) == 0) i |= 0x0001; // 0
  if (HWREG((GPIO_PORTN_BASE + GPIO_O_DATA + 0x0008)) == 0) i |= 0x0002; // 1
  if (HWREG((GPIO_PORTN_BASE + GPIO_O_DATA + 0x0010)) == 0) i |= 0x0004; // 2
  if (HWREG((GPIO_PORTN_BASE + GPIO_O_DATA + 0x0020)) == 0) i |= 0x0008; // 3
  if (HWREG((GPIO_PORTN_BASE + GPIO_O_DATA + 0x0040)) == 0) i |= 0x0010; // 4
  if (HWREG((GPIO_PORTN_BASE + GPIO_O_DATA + 0x0080)) == 0) i |= 0x0020; // 5

  if (HWREG((GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0004)) == 0) i |= 0x0040; // 6
  if (HWREG((GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0008)) == 0) i |= 0x0080; // 7
  if (HWREG((GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0010)) == 0) i |= 0x0100; // 8
  if (HWREG((GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0020)) == 0) i |= 0x0200; // 9

  if (HWREG((GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0004)) == 0) i |= 0x0400; // .
  if (HWREG((GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0008)) == 0) i |= 0x0800; // -
  if (HWREG((GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0010)) == 0) i |= 0x1000; // P
  if (HWREG((GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0020)) == 0) i |= 0x2000; // E

  return i;
}


uchar   ConvertKey(uint  i)
{
  switch (i)
  {
    case 0x0001: return 0x2B;
    case 0x0002: return 0x0E;
    case 0x0004: return 0x1E;
    case 0x0008: return 0x2E;
    case 0x0010: return 0x3E;
    case 0x0020: return 0x0D;
    case 0x0040: return 0x1D;
    case 0x0080: return 0x2D;
    case 0x0100: return 0x3D;
    case 0x0200: return 0x0B;
    case 0x0400: return 0x3B;
    case 0x0800: return 0x1B;
    case 0x1000: return 0x07;
    case 0x2000: return 0x17;
    default: return 0;
  }
}


void    Key_Timer0(void)
{
uint   i;

  if (fKey == false)                           // если обработано предыдущее нажатие клавишы
  {
    i = GetKey();

    if (i != 0)                                // если есть нажатие клавишы
    {
      bKey = ConvertKey(i);
    }
    else                                       // если не нажато ни одной клавиши
    {
      bPrevKey = 0;
      bRepeat  = 0;
    }

    if ((bKey != 0) && (bPrevKey == 0))         // если нажата одна клавиша (без повторов)
    {
      if (++bRepeat > 5)                        // обработка антидребезга
      {
        bRepeat  = 0;
        bPrevKey = bKey;

        fKey = true;                            // можно обрабатывать нажатие клавишы
      }
    }
  }
}
