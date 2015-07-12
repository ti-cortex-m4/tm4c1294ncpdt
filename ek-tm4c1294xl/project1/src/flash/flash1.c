/*------------------------------------------------------------------------------
AT45.C

 AT45DB321B, SPI Mode 0
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../include/flash.h"
#include "flash_control.h"
#include "../kernel/crc-16.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "flash1.h"
#include "../time/delay.h"
#include "flash_define1.h"



void    EnableFlash1()
{
	 HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	 HWREG(GPIO_FLASH1_CS)  = MASK_FLASH1_CS;//PH0
	 HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	 HWREG(GPIO_FLASH1_CS)  = ~MASK_FLASH1_CS;//PH0
}


void    DisableFlash1(void)
{
	 HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	 HWREG(GPIO_FLASH1_CS)  = MASK_FLASH1_CS;//PH0
}



static void CharOut(uchar  bT)
{
  cdwFlashWriteBytes++;

  if (bT & 0x80) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (bT & 0x40) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (bT & 0x20) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (bT & 0x10) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (bT & 0x08) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (bT & 0x04) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (bT & 0x02) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;

  if (bT & 0x01) HWREG(GPIO_FLASH1_SI) = MASK_FLASH1_SI;
  else HWREG(GPIO_FLASH1_SI) = ~MASK_FLASH1_SI;
  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;
  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;
}


static uchar CharIn(void)
{
  cdwFlashReadBytes++;

	 unsigned char bRez;
	 bRez = 0;
	/*
	 unsigned char bK;

	 for(bK=0; bK<8; bK++)
	 {
	  HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0004) =  0x001;//PQ0
	  HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0004) = ~0x001;//PQ0

	  if(HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0020)) bRez |= 0x80 >> bK;//PQ3
	 }
	*/
	  //bTt 7
	  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;//PQ0
	  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	  if(HWREG(GPIO_FLASH1_SO)) bRez |= 0x80;//PQ3
	  //bTt 6
	  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;//PQ0
	  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	  if(HWREG(GPIO_FLASH1_SO)) bRez |= 0x40;//PQ3
	  //bTt 5
	  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;//PQ0
	  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	  if(HWREG(GPIO_FLASH1_SO)) bRez |= 0x20;//PQ3
	  //bTt 4
	  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;//PQ0
	  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	  if(HWREG(GPIO_FLASH1_SO)) bRez |= 0x10;//PQ3
	  //bTt 3
	  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;//PQ0
	  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	  if(HWREG(GPIO_FLASH1_SO)) bRez |= 0x08;//PQ3
	  //bTt 2
	  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;//PQ0
	  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	  if(HWREG(GPIO_FLASH1_SO)) bRez |= 0x04;//PQ3
	  //bTt 1
	  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;//PQ0
	  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	  if(HWREG(GPIO_FLASH1_SO)) bRez |= 0x02;//PQ3
	  //bTt 0
	  HWREG(GPIO_FLASH1_SCK) =  MASK_FLASH1_SCK;//PQ0
	  HWREG(GPIO_FLASH1_SCK) = ~MASK_FLASH1_SCK;//PQ0
	  if(HWREG(GPIO_FLASH1_SO)) bRez |= 0x01;//PQ3

	 return(bRez);
}



uchar   ReadStatus1(void)
{
  EnableFlash1();

  CharOut(0x57);
  bStatusFlash = CharIn();

  DisableFlash1();
  return(bStatusFlash);
}


bool SafeReadStatus1(void)
{
uint    i;

  i = 0;
  while ((ReadStatus1() & 0x80) == 0)
  {
    if (++i > wREAD_STATUS)
    {
      cwWrnBusy++;
      return false;
    }
  }

  return true;
}



bool PageErase1(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus1() == false)
    return false;
  else
  {
    EnableFlash1();

    CharOut(0x81);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    DisableFlash1();
    return true;
  }
}


bool SafePageErase(void)
{
uchar   i;

  cdwPageErase++;

  for (i=0; i<bFLASH_REPEATS; i++)
  {
    if (PageErase1() == 0)
    {
      cwWrnPageErase++;
      continue;
    }
    else break;
  }

  if (i == bFLASH_REPEATS)
  {
    cwErrPageErase++;
    return false;
  }
  else return true;
}



bool PageRead1(void)
{
uint    i;

  if (SafeReadStatus1() == false)
    return false;
  else
  {
    EnableFlash1();

    CharOut(0x52);

    i = (wPageIn << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    for (i=0; i<4; i++) CharOut(0);

    for (i=0; i<wPAGE_BYTES; i++) mpbPageIn[i] = CharIn();

    DisableFlash1();
    return true;
  }
}


bool SafePageRead(void)
{
uchar   i;

  cdwPageRead++;

  for (i=0; i<bFLASH_REPEATS; i++)
  {
    if (PageRead1() == 0)
    {
      cwWrnPageRead++;
      continue;
    }
    else break;
  }

  if (i == bFLASH_REPEATS)
  {
    cwErrPageRead++;
    return false;
  }
  else return true;
}



bool PageWrite1(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus1() == false)
    return false;
  else                                  // запись
  {
    EnableFlash1();

    CharOut(0x82);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    for (i=0; i<wPAGE_BYTES; i++) CharOut(mpbPageOut[i]);

    DisableFlash1();
  }

  if (SafeReadStatus1() == false)
    return false;
  else                                  // проверка записи
  {
    EnableFlash1();

    CharOut(0x60);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    DisableFlash1();
  }

  if (SafeReadStatus1() == false)
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


bool SafePageWrite(void)
{
uchar   i;

  mpbPageOut[wLEAF_BYTES+0] = 0;
  mpbPageOut[wLEAF_BYTES+1] = 0;

  mpbPageOut[wLEAF_BYTES+2] = wPageOut / 0x100;
  mpbPageOut[wLEAF_BYTES+3] = wPageOut % 0x100;

  memcpy(&mpbPageOut[wLEAF_BYTES+4], &tiCurr, sizeof(time));

  MakeCRC16(mpbPageOut, wPAGE_BYTES-2);

  mpbPageOut[wPAGE_BYTES-2] = bCRCHi;
  mpbPageOut[wPAGE_BYTES-1] = bCRCLo;

  cdwPageWrite++;

  for (i=0; i<bFLASH_REPEATS; i++)
  {
    if (PageWrite1() == 0)
    {
      cwWrnPageWrite++;
      continue;
    }
    else break;
  }

  if (i == bFLASH_REPEATS)
  {
    cwErrPageWrite++;
    return false;
  }
  else return true;
}

void    InitGPIO_Flash1(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R3; // GPIO Port D Run Mode Clock Gating Control

  DelayGPIO();

  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x000E; // GPIO Direction
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) &= 0xFFFE;

  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x000F; // GPIO Digital Enable
}


void    InitFlash1(void)
{
  InitGPIO_Flash1();
  DisableFlash1();

// TODO if (SafeReadStatus() == false) TestError(szBadFlash);
}
