/*------------------------------------------------------------------------------
FLASH1,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../memory/mem_flash.h"
#include "../time/delay.h"
#include "../display/lcd.h"
#include "../display/messages.h"
#include "flash_control.h"
#include "flash1_define.h"
#include "flash1.h"



static void Enable(void)
{
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_CS)  =  MASK_FLASH1_CS;

  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_CS)  = ~MASK_FLASH1_CS;
}


static void Disable(void)
{
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_CS)  =  MASK_FLASH1_CS;
}



static void OutChar(uchar  b)
{
  cdwFlashWriteByte++;

  if (b & 0x80) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (b & 0x40) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (b & 0x20) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (b & 0x10) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (b & 0x08) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (b & 0x04) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (b & 0x02) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (b & 0x01) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
}


static uchar InChar(void)
{
  cdwFlashReadByte++;

  uchar b = 0;

  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  if(HWREG(GPIO_FLASH1_SO)) b |= 0x80;

  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  if(HWREG(GPIO_FLASH1_SO)) b |= 0x40;

  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  if(HWREG(GPIO_FLASH1_SO)) b |= 0x20;

  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  if(HWREG(GPIO_FLASH1_SO)) b |= 0x10;

  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  if(HWREG(GPIO_FLASH1_SO)) b |= 0x08;

  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  if(HWREG(GPIO_FLASH1_SO)) b |= 0x04;

  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  if(HWREG(GPIO_FLASH1_SO)) b |= 0x02;

  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
  if(HWREG(GPIO_FLASH1_SO)) b |= 0x01;

  return b;
}



uchar   ReadStatus1(void)
{
  Enable();

  OutChar(0x57);
  bFlashStatus = InChar();

  Disable();
  return bFlashStatus;
}


bool    SafeReadStatus1(void)
{
  uint i = 0;
  while ((ReadStatus1() & 0x80) == 0)
  {
    if (++i > STATUS_REPEATS)
    {
      cwFlashBusyErr++;
      return false;
    }
  }

  cwFlashBusyCnt = i;
  return true;
}



bool    PageErase1(uint const  wPageOut)
{
  ASSERT(wPageOut < wPAGES);
  IncFlashControl(wPageOut);

  if (SafeReadStatus1() == false)
    return false;
  else
  {
    Enable();

    OutChar(0x81);

    uint i = (wPageOut << 2) & 0xFFFC;
    OutChar(i / 0x100);
    OutChar(i % 0x100);
    OutChar(0);

    Disable();
    return true;
  }
}



bool    PageRead1(uint const  wPageIn)
{
  ASSERT(wPageIn < wPAGES);

  if (SafeReadStatus1() == false)
    return false;
  else
  {
    Enable();

    OutChar(0x52);

    uint i = (wPageIn << 2) & 0xFFFC;
    OutChar(i / 0x100);
    OutChar(i % 0x100);
    OutChar(0);

    for (i=0; i<4; i++) OutChar(0);

    for (i=0; i<wPAGE_BYTES; i++) mpbPageIn[i] = InChar();

    Disable();
    return true;
  }
}



bool    PageWrite1(uint const  wPageOut)
{
  ASSERT(wPageOut < wPAGES);
  IncFlashControl(wPageOut);

  if (SafeReadStatus1() == false)
    return false;
  else                                  // ������
  {
    Enable();

    OutChar(0x82);

    uint i = (wPageOut << 2) & 0xFFFC;
    OutChar(i / 0x100);
    OutChar(i % 0x100);
    OutChar(0);

    for (i=0; i<wPAGE_BYTES; i++) OutChar(mpbPageOut[i]);

    Disable();
  }

  if (SafeReadStatus1() == false)
    return false;
  else                                  // �������� ������
  {
    Enable();

    OutChar(0x60);

    uint i = (wPageOut << 2) & 0xFFFC;
    OutChar(i / 0x100);
    OutChar(i % 0x100);
    OutChar(0);

    Disable();
  }

  if (SafeReadStatus1() == false)
  {
    cwFlashCompareErr++;
    cwFlashCompareErr1++;

    return false;
  }
  else
  {
    if ((bFlashStatus & 0x40) != 0)
    {
      cwFlashCompareWrn++;
      return false;
    }
    else return true;
  }
}



static void InitGPIO(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R1; // GPIO Port B Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DIR) |= 0x0030; // GPIO Direction
  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DEN) |= 0x0030; // GPIO Digital Enable

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) |= 0x0010; // GPIO Direction
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) &= 0xFFDF;
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DEN) |= 0x0030; // GPIO Digital Enable
}


void    InitFlash1(void)
{
  InitGPIO();
  Disable();

  if (SafeReadStatus1() == false) TestError(szBadFlash1);
}
