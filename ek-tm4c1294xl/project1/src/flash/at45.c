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
#include "at45.h"
#include "flash1.h"
#include "flash2.h"



void    EnableFlash()
{
	 HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	 HWREG(GPIO_DATAbTT_CS)  = SPI_bTT_CS;//PH0
	 HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	 HWREG(GPIO_DATAbTT_CS)  = ~SPI_bTT_CS;//PH0
}


void    DisableFlash(void)
{
	 HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	 HWREG(GPIO_DATAbTT_CS)  = SPI_bTT_CS;//PH0
}



void    CharOut(uchar  bT)
{
  if (bT & 0x80) HWREG(GPIO_DATAbTT_SI) = SPI_bTT_SI;
  else HWREG(GPIO_DATAbTT_SI) = ~SPI_bTT_SI;
  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;
  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;

  if (bT & 0x40) HWREG(GPIO_DATAbTT_SI) = SPI_bTT_SI;
  else HWREG(GPIO_DATAbTT_SI) = ~SPI_bTT_SI;
  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;
  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;

  if (bT & 0x20) HWREG(GPIO_DATAbTT_SI) = SPI_bTT_SI;
  else HWREG(GPIO_DATAbTT_SI) = ~SPI_bTT_SI;
  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;
  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;

  if (bT & 0x10) HWREG(GPIO_DATAbTT_SI) = SPI_bTT_SI;
  else HWREG(GPIO_DATAbTT_SI) = ~SPI_bTT_SI;
  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;
  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;

  if (bT & 0x08) HWREG(GPIO_DATAbTT_SI) = SPI_bTT_SI;
  else HWREG(GPIO_DATAbTT_SI) = ~SPI_bTT_SI;
  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;
  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;

  if (bT & 0x04) HWREG(GPIO_DATAbTT_SI) = SPI_bTT_SI;
  else HWREG(GPIO_DATAbTT_SI) = ~SPI_bTT_SI;
  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;
  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;

  if (bT & 0x02) HWREG(GPIO_DATAbTT_SI) = SPI_bTT_SI;
  else HWREG(GPIO_DATAbTT_SI) = ~SPI_bTT_SI;
  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;
  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;

  if (bT & 0x01) HWREG(GPIO_DATAbTT_SI) = SPI_bTT_SI;
  else HWREG(GPIO_DATAbTT_SI) = ~SPI_bTT_SI;
  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;
  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;
}


uchar   CharIn(void)
{
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
	  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;//PQ0
	  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT_SO)) bRez |= 0x80;//PQ3
	  //bTt 6
	  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;//PQ0
	  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT_SO)) bRez |= 0x40;//PQ3
	  //bTt 5
	  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;//PQ0
	  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT_SO)) bRez |= 0x20;//PQ3
	  //bTt 4
	  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;//PQ0
	  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT_SO)) bRez |= 0x10;//PQ3
	  //bTt 3
	  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;//PQ0
	  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT_SO)) bRez |= 0x08;//PQ3
	  //bTt 2
	  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;//PQ0
	  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT_SO)) bRez |= 0x04;//PQ3
	  //bTt 1
	  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;//PQ0
	  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT_SO)) bRez |= 0x02;//PQ3
	  //bTt 0
	  HWREG(GPIO_DATAbTT_SCK) =  SPI_bTT_SCK;//PQ0
	  HWREG(GPIO_DATAbTT_SCK) = ~SPI_bTT_SCK;//PQ0
	  if(HWREG(GPIO_DATAbTT_SO)) bRez |= 0x01;//PQ3

	 return(bRez);
}



uchar   ReadStatus(void)
{
  EnableFlash();

  CharOut(0x57);
  bStatusFlash = CharIn();

  DisableFlash();
  return(bStatusFlash);
}


bool SafeReadStatus(void)
{
uint    i;

  i = 0;
  while ((ReadStatus() & 0x80) == 0)
  {
    if (++i > wREAD_STATUS)
    {
      cwWrnBusy++;
      return false;
    }
  }

  return true;
}



bool PageErase(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus() == false)
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


bool SafePageErase(void)
{
uchar   i;

  cwPageErase++;

  for (i=0; i<bMAXREPEAT; i++)
  {
    if (PageErase() == 0)
    {
      cwWrnPageErase++;
      continue;
    }
    else break;
  }

  if (i == bMAXREPEAT)
  {
    cwErrPageErase++;
    return false;
  }
  else return true;
}



bool PageRead(void)
{
uint    i;

  if (SafeReadStatus() == false)
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

    for (i=0; i<wPAGE_SIZE; i++) mpbPageIn[i] = CharIn();

    DisableFlash();
    return true;
  }
}


bool SafePageRead(void)
{
uchar   i;

  cwPageRead++;

  for (i=0; i<bMAXREPEAT; i++)
  {
    if (PageRead() == 0)
    {
      cwWrnPageRead++;
      continue;
    }
    else break;
  }

  if (i == bMAXREPEAT)
  {
    cwErrPageRead++;
    return false;
  }
  else return true;
}



bool PageWrite(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus() == false)
    return false;
  else                                  // запись
  {
    EnableFlash();

    CharOut(0x82);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    for (i=0; i<wPAGE_SIZE; i++) CharOut(mpbPageOut[i]);

    DisableFlash();
  }

  if (SafeReadStatus() == false)
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

  if (SafeReadStatus() == false)
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

  mpbPageOut[wFREEPAGE_SIZE+0] = 0;
  mpbPageOut[wFREEPAGE_SIZE+1] = 0;

  mpbPageOut[wFREEPAGE_SIZE+2] = wPageOut / 0x100;
  mpbPageOut[wFREEPAGE_SIZE+3] = wPageOut % 0x100;

  memcpy(&mpbPageOut[wFREEPAGE_SIZE+4], &tiCurr, sizeof(time));

  MakeCRC16(mpbPageOut, wPAGE_SIZE-2);

  mpbPageOut[wPAGE_SIZE-2] = bCRCHi;
  mpbPageOut[wPAGE_SIZE-1] = bCRCLo;

  cwPageWrite++;

  for (i=0; i<bMAXREPEAT; i++)
  {
    if (PageWrite() == 0)
    {
      cwWrnPageWrite++;
      continue;
    }
    else break;
  }

  if (i == bMAXREPEAT)
  {
    cwErrPageWrite++;
    return false;
  }
  else return true;
}


void    InitFlash(void)
{
  Init_SPIhandAT45DB321();
  DisableFlash();

// TODO if (SafeReadStatus() == false) TestError(szBadFlash);
}



uint    GetFlashStatus(void)
{
uint    i;

  i = 0;

  if (cwErrCompare   != 0) i |= 0x0001;
  if (cwErrPageErase != 0) i |= 0x0002;
  if (cwErrPageRead  != 0) i |= 0x0004;
  if (cwErrPageWrite != 0) i |= 0x0008;

  return(i);
}


bool GetFlashChecksum(void)
{
  MakeCRC16(mpbPageIn, wPAGE_SIZE);

  if ((bCRCHi != 0x00) && (bCRCLo != 0x00))
  {
    if ((bCRCHi != 0x0F) && (bCRCLo != 0x74))
      return false;
  }

  return true;
}


/*
void    TODO OutFlashReadStatus(void) { + add (++i > wREAD_STATUS) + add cwWrnBusy etc
  InitPushCRC();

  ReadStatus();
  PushChar(bStatusFlash);

  PushChar(ReadStatus());

  Output(sizeof(char)+sizeof(char));
}
*/
