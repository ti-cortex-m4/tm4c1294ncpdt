/*------------------------------------------------------------------------------
AT45.C

 AT45DB321B, SPI Mode 0
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_flash.h"
#include        "../mem_settings.h"
#include        "../mem_realtime.h"
#include        "../settings/flash.h"
#include        "flash_control.h"
//#include        "rtc.h"
//#include        "delay.h"
#include        "../crc-16.h"
//#include        "lcd.h"
//#include        "access.h"
//#include        "nexttime.h"
//#include        "shift.h"
//#include        "display.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"


//Биты управления SPI
#define SPI_BIT_SCK   0x0001 //PQ0
#define SPI_BIT_SI    0x0004 //PQ2
#define SPI_BIT_SO    0x0008 //PQ3
#define SPI_BIT_CS    0x0001 //PH0

//Адреса пинов управления SPI
#define GPIO_DATABIT_SCK (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0004)//PQ0
#define GPIO_DATABIT_SI  (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0010)//PQ2
#define GPIO_DATABIT_SO  (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0020)//PQ3
#define GPIO_DATABIT_CS  (GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0004)//PH0

#define HWREG(x) (*((volatile uint32_t *)(x)))

#define DS80C400

void    Delay5mcs(void) {}

void    EnableFlash()
{
  Delay5mcs();

  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
  HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;//PH0
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
  HWREG(GPIO_DATABIT_CS)  = ~SPI_BIT_CS;//PH0

  Delay5mcs();
}


void    DisableFlash(void)
{
  Delay5mcs();

  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
  HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;//PH0

  Delay5mcs();
}


void    CharOut(uchar  bI)
{
	  //bit 7
	  if(bI & 0x80) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;//PQ2
	  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  //bit 6
	  if(bI & 0x40) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;//PQ2
	  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  //bit 5
	  if(bI & 0x20) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;//PQ2
	  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  //bit 4
	  if(bI & 0x10) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;//PQ2
	  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  //bit 3
	  if(bI & 0x08) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;//PQ2
	  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  //bit 2
	  if(bI & 0x04) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;//PQ2
	  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  //bit 1
	  if(bI & 0x02) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;//PQ2
	  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  //bit 0
	  if(bI & 0x01) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;//PQ2
	  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
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
	  //bit 7
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x80;//PQ3
	  //bit 6
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x40;//PQ3
	  //bit 5
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x20;//PQ3
	  //bit 4
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x10;//PQ3
	  //bit 3
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x08;//PQ3
	  //bit 2
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x04;//PQ3
	  //bit 1
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x02;//PQ3
	  //bit 0
	  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;//PQ0
	  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;//PQ0
	  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x01;//PQ3

	 return(bRez);
}



uchar   ReadStatus(void)
{
  EnableFlash();

  CharOut(0xD7);
  bStatusFlash = CharIn();

  DisableFlash();
  return(bStatusFlash);
}


bool    SafeReadStatus(void)
{
uint    i;

  i = 0;
  while ((ReadStatus() & 0x80) == 0)
  {
    if (++i > wMAXBUSY)
    {
      cwWrnBusy++;
      return(0);
    }
  }

  return(1);
}



bool    PageErase(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus() == 0)
    return(0);
  else
  {
    EnableFlash();

    CharOut(0x81);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    DisableFlash();
    return(1);
  }
}


bool    SafePageErase(void)
{
uchar   i;

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
    return(0);
  }
  else return(1);
}



bool    PageRead(void)
{
uint    i;

  if (SafeReadStatus() == 0)
    return(0);
  else
  {
    EnableFlash();

    CharOut(0xD2);

    i = (wPageIn << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    for (i=0; i<4; i++) CharOut(0);

    for (i=0; i<wPAGE_SIZE; i++) mpbPageIn[i] = CharIn();

    DisableFlash();
    return(1);
  }
}


bool    SafePageRead(void)
{
uchar   i;

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
    return(0);
  }
  else return(1);
}



bool    PageWrite(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus() == 0)
    return(0);
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

  if (SafeReadStatus() == 0)
    return(0);
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

  if (SafeReadStatus() == 0)
  {
    cwErrCompare++;
    return(0);
  }
  else
  {
    if ((bStatusFlash & 0x40) != 0)
    {
      cwWrnCompare++;
      return(0);
    }
    else return(1);
  }
}


bool    SafePageWrite(void)
{
uchar   i;

  memcpy(&mpbPageOut[wFREEPAGE_SIZE+0], &wPrivate, sizeof(uint));
  memcpy(&mpbPageOut[wFREEPAGE_SIZE+2], &wPageOut, sizeof(uint));
  memcpy(&mpbPageOut[wFREEPAGE_SIZE+4], &tiCurr,   sizeof(time));

  MakeCRC16(mpbPageOut, wPAGE_SIZE-2);

  mpbPageOut[wPAGE_SIZE-2] = bCRCHi;
  mpbPageOut[wPAGE_SIZE-1] = bCRCLo;

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
    return(0);
  }
  else return(1);
}


/*
void    InitFlash(void)
{
#ifdef  DS80C400
  TA = 0xAA; TA = 0x55; P5CNT &= 0xF0;

  P6 |= bMASK_CS;
  sfSCK = 0;
#else
//  sfCS  = 1;                          // Inactive Clock Polarity Low
  bP4 |= bMASK_CS;

//  sfSCK = 0;
  bP4 &= ~bMASK_SCK;

//  sfSO  = 1;
  bP4 |= bMASK_SO;

//  sfSI  = 1;
  bP4 |= bMASK_SI;
#endif

//  if (SafeReadStatus() == 0) TestError(szBadFlash);
}
*/


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


bool    GetFlashChecksum(void)
{
  MakeCRC16(mpbPageIn, wPAGE_SIZE);

  if ((bCRCHi != 0x00) && (bCRCLo != 0x00))
  {
    if ((bCRCHi != 0x70) && (bCRCLo != 0x7F))
      return(0);
  }

  return(1);
}
