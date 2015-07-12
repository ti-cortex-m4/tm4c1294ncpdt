/*------------------------------------------------------------------------------
FLASH2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../memory/mem_flash.h"
#include "../time/delay.h"
#include "flash_control.h"
#include "flash_define2.h"
#include "flash2.h"



static void EnableFlash(void)
{
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_CS)  = MASK_FLASH2_CS;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_CS)  = ~MASK_FLASH2_CS;
}


static void DisableFlash(void)
{
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_CS)  = MASK_FLASH2_CS;
}



static void CharOut(uchar  b)
{
  cdwFlashWriteBytes++;

  if (b & 0x80) HWREG(GPIO_FLASH2_SI) = MASK_FLASH2_SI;
  else HWREG(GPIO_FLASH2_SI) = ~MASK_FLASH2_SI;
  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;

  if (b & 0x40) HWREG(GPIO_FLASH2_SI) = MASK_FLASH2_SI;
  else HWREG(GPIO_FLASH2_SI) = ~MASK_FLASH2_SI;
  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;

  if (b & 0x20) HWREG(GPIO_FLASH2_SI) = MASK_FLASH2_SI;
  else HWREG(GPIO_FLASH2_SI) = ~MASK_FLASH2_SI;
  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;

  if (b & 0x10) HWREG(GPIO_FLASH2_SI) = MASK_FLASH2_SI;
  else HWREG(GPIO_FLASH2_SI) = ~MASK_FLASH2_SI;
  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;

  if (b & 0x08) HWREG(GPIO_FLASH2_SI) = MASK_FLASH2_SI;
  else HWREG(GPIO_FLASH2_SI) = ~MASK_FLASH2_SI;
  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;

  if (b & 0x04) HWREG(GPIO_FLASH2_SI) = MASK_FLASH2_SI;
  else HWREG(GPIO_FLASH2_SI) = ~MASK_FLASH2_SI;
  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;

  if (b & 0x02) HWREG(GPIO_FLASH2_SI) = MASK_FLASH2_SI;
  else HWREG(GPIO_FLASH2_SI) = ~MASK_FLASH2_SI;
  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;

  if (b & 0x01) HWREG(GPIO_FLASH2_SI) = MASK_FLASH2_SI;
  else HWREG(GPIO_FLASH2_SI) = ~MASK_FLASH2_SI;
  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
}


static uchar CharIn(void)
{
  cdwFlashReadBytes++;

  uchar b = 0;

  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  if(HWREG(GPIO_FLASH2_SO)) b |= 0x80;

  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  if(HWREG(GPIO_FLASH2_SO)) b |= 0x40;

  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  if(HWREG(GPIO_FLASH2_SO)) b |= 0x20;

  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  if(HWREG(GPIO_FLASH2_SO)) b |= 0x10;

  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  if(HWREG(GPIO_FLASH2_SO)) b |= 0x08;

  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  if(HWREG(GPIO_FLASH2_SO)) b |= 0x04;

  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  if(HWREG(GPIO_FLASH2_SO)) b |= 0x02;

  HWREG(GPIO_FLASH2_SCK) =  MASK_FLASH2_SCK;
  HWREG(GPIO_FLASH2_SCK) = ~MASK_FLASH2_SCK;
  if(HWREG(GPIO_FLASH2_SO)) b |= 0x01;

  return b;
}



uchar   ReadStatus2(void)
{
  EnableFlash();

  CharOut(0x57);
  bStatusFlash = CharIn();

  DisableFlash();
  return(bStatusFlash);
}


bool SafeReadStatus2(void)
{
uint    i;

  i = 0;
  while ((ReadStatus2() & 0x80) == 0)
  {
    if (++i > wREAD_STATUS)
    {
      cwWrnBusy++;
      return false;
    }
  }

  return true;
}



bool PageErase2(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus2() == false)
    return false;
  else
  {
    EnableFlash();

    CharOut(0x81);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    DisableFlash();
    return true;
  }
}



bool PageRead2(void)
{
uint    i;

  if (SafeReadStatus2() == false)
    return false;
  else
  {
    EnableFlash();

    CharOut(0x52);

    i = (wPageIn << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    for (i=0; i<4; i++) CharOut(0);

    for (i=0; i<wPAGE_BYTES; i++) mpbPageIn[i] = CharIn();

    DisableFlash();
    return true;
  }
}



bool PageWrite2(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus2() == false)
    return false;
  else                                  // запись
  {
    EnableFlash();

    CharOut(0x82);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    for (i=0; i<wPAGE_BYTES; i++) CharOut(mpbPageOut[i]);

    DisableFlash();
  }

  if (SafeReadStatus2() == false)
    return false;
  else                                  // проверка записи
  {
    EnableFlash();

    CharOut(0x60);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    DisableFlash();
  }

  if (SafeReadStatus2() == false)
  {
    cwErrCompare++;
    return false;
  }
  else
  {
    if ((bStatusFlash & 0x40) != 0)
    {
      cwWrnCompare++;
      return false;
    }
    else return true;
  }
}



void    InitGPIO_Flash2(void)
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


void    InitFlash2(void)
{
  InitGPIO_Flash2();
  DisableFlash();

// TODO if (SafeReadStatus2() == false) TestError(szBadFlash);
}
