/*------------------------------------------------------------------------------
AT45_2.C

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
#include "at45.h"
#include "flash1.h"
//#include "flash2.h"



void    EnableFlash2()
{
	 HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	 HWREG(GPIO_DATAbTT2_CS)  = SPI_bTT2_CS;//PH0
	 HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	 HWREG(GPIO_DATAbTT2_CS)  = ~SPI_bTT2_CS;//PH0
}


void    DisableFlash2(void)
{
	 HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	 HWREG(GPIO_DATAbTT2_CS)  = SPI_bTT2_CS;//PH0
}



static void CharOut2(uchar  bT)
{
  cdwFlashWriteBytes++;

  if (bT & 0x80) HWREG(GPIO_DATAbTT2_SI) = SPI_bTT2_SI;
  else HWREG(GPIO_DATAbTT2_SI) = ~SPI_bTT2_SI;
  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;
  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;

  if (bT & 0x40) HWREG(GPIO_DATAbTT2_SI) = SPI_bTT2_SI;
  else HWREG(GPIO_DATAbTT2_SI) = ~SPI_bTT2_SI;
  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;
  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;

  if (bT & 0x20) HWREG(GPIO_DATAbTT2_SI) = SPI_bTT2_SI;
  else HWREG(GPIO_DATAbTT2_SI) = ~SPI_bTT2_SI;
  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;
  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;

  if (bT & 0x10) HWREG(GPIO_DATAbTT2_SI) = SPI_bTT2_SI;
  else HWREG(GPIO_DATAbTT2_SI) = ~SPI_bTT2_SI;
  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;
  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;

  if (bT & 0x08) HWREG(GPIO_DATAbTT2_SI) = SPI_bTT2_SI;
  else HWREG(GPIO_DATAbTT2_SI) = ~SPI_bTT2_SI;
  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;
  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;

  if (bT & 0x04) HWREG(GPIO_DATAbTT2_SI) = SPI_bTT2_SI;
  else HWREG(GPIO_DATAbTT2_SI) = ~SPI_bTT2_SI;
  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;
  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;

  if (bT & 0x02) HWREG(GPIO_DATAbTT2_SI) = SPI_bTT2_SI;
  else HWREG(GPIO_DATAbTT2_SI) = ~SPI_bTT2_SI;
  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;
  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;

  if (bT & 0x01) HWREG(GPIO_DATAbTT2_SI) = SPI_bTT2_SI;
  else HWREG(GPIO_DATAbTT2_SI) = ~SPI_bTT2_SI;
  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;
  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;
}


uchar   CharIn2(void)
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
	  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;//PQ0
	  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT2_SO)) bRez |= 0x80;//PQ3
	  //bTt 6
	  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;//PQ0
	  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT2_SO)) bRez |= 0x40;//PQ3
	  //bTt 5
	  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;//PQ0
	  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT2_SO)) bRez |= 0x20;//PQ3
	  //bTt 4
	  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;//PQ0
	  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT2_SO)) bRez |= 0x10;//PQ3
	  //bTt 3
	  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;//PQ0
	  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT2_SO)) bRez |= 0x08;//PQ3
	  //bTt 2
	  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;//PQ0
	  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT2_SO)) bRez |= 0x04;//PQ3
	  //bTt 1
	  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;//PQ0
	  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT2_SO)) bRez |= 0x02;//PQ3
	  //bTt 0
	  HWREG(GPIO_DATAbTT2_SCK) =  SPI_bTT2_SCK;//PQ0
	  HWREG(GPIO_DATAbTT2_SCK) = ~SPI_bTT2_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT2_SO)) bRez |= 0x01;//PQ3

	 return(bRez);
}



uchar   ReadStatus2(void)
{
  EnableFlash2();

  CharOut2(0x57);
  bStatusFlash = CharIn2();

  DisableFlash2();
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
    EnableFlash2();

    CharOut2(0x81);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut2(i / 0x100);
    CharOut2(i % 0x100);
    CharOut2(0);

    DisableFlash2();
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
    EnableFlash2();

    CharOut2(0x52);

    i = (wPageIn << 2) & 0xFFFC;
    CharOut2(i / 0x100);
    CharOut2(i % 0x100);
    CharOut2(0);

    for (i=0; i<4; i++) CharOut2(0);

    for (i=0; i<wPAGE_BYTES; i++) mpbPageIn[i] = CharIn2();

    DisableFlash2();
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
    EnableFlash2();

    CharOut2(0x82);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut2(i / 0x100);
    CharOut2(i % 0x100);
    CharOut2(0);

    for (i=0; i<wPAGE_BYTES; i++) CharOut2(mpbPageOut[i]);

    DisableFlash2();
  }

  if (SafeReadStatus2() == false)
    return false;
  else                                  // проверка записи
  {
    EnableFlash2();

    CharOut2(0x60);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut2(i / 0x100);
    CharOut2(i % 0x100);
    CharOut2(0);

    DisableFlash2();
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



void    InitFlash2(void)
{
//  Init_SPIhandAT45DB321();
//  DisableFlash2();

// TODO if (SafeReadStatus2() == false) TestError(szBadFlash);
}
