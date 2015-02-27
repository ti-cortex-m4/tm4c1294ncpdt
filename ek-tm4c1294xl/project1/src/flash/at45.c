/*------------------------------------------------------------------------------
AT45.C

 AT45DB321B, SPI Mode 0
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_flash.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_realtime.h"
#include        "../include/flash.h"
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
#define SPI_bTT_SCK   0x0001 //PQ0
#define SPI_bTT_SI    0x0004 //PQ2
#define SPI_bTT_SO    0x0008 //PQ3
#define SPI_bTT_CS    0x0001 //PH0

//Адреса пинов управления SPI
#define GPIO_DATAbTT_SCK (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0004)//PQ0
#define GPIO_DATAbTT_SI  (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0010)//PQ2
#define GPIO_DATAbTT_SO  (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0020)//PQ3
#define GPIO_DATAbTT_CS  (GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0004)//PH0

#define HWREG(x) (*((volatile uint32_t *)(x)))



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


boolean SafeReadStatus(void)
{
uint    i;

  i = 0;
  while ((ReadStatus() & 0x80) == 0)
  {
    if (++i > wREAD_STATUS)
    {
      cwWrnBusy++;
      return FALSE;
    }
  }

  return TRUE;
}



boolean PageErase(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus() == FALSE)
    return FALSE;
  else
  {
    EnableFlash();

    CharOut(0x81);

    i = (wPageOut << 2) & 0xFFFC;
    CharOut(i / 0x100);
    CharOut(i % 0x100);
    CharOut(0);

    DisableFlash();
    return TRUE;
  }
}


boolean SafePageErase(void)
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
    return FALSE;
  }
  else return TRUE;
}



boolean PageRead(void)
{
uint    i;

  if (SafeReadStatus() == FALSE)
    return FALSE;
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
    return TRUE;
  }
}


boolean SafePageRead(void)
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
    return FALSE;
  }
  else return TRUE;
}



boolean PageWrite(void)
{
uint    i;

  IncFlashControl();

  if (SafeReadStatus() == FALSE)
    return FALSE;
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

  if (SafeReadStatus() == FALSE)
    return FALSE;
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

  if (SafeReadStatus() == FALSE)
  {
    cwErrCompare++;
    return FALSE;
  }
  else
  {
    if ((bStatusFlash & 0x40) != 0)
    {
      cwWrnCompare++;
      return FALSE;
    }
    else return TRUE;
  }
}


boolean SafePageWrite(format  fo)
{
uchar   i;

  mpbPageOut[wFREEPAGE_SIZE+0] = fo;
  mpbPageOut[wFREEPAGE_SIZE+1] = bBlockOut++;

  mpbPageOut[wFREEPAGE_SIZE+2] = wPageOut / 0x100;
  mpbPageOut[wFREEPAGE_SIZE+3] = wPageOut % 0x100;

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
    return FALSE;
  }
  else return TRUE;
}


static void RunClocking(void)
{
__asm("   nop\n"
      "   nop\n"
      "   nop\n");
}


void Init_SPIhandAT45DB321(void)
{
	 //Включение периферии
	 HWREG(SYSCTL_RCGCGPIO) |= 0x4080;//Запуск генераторов портов "H" и "Q"

	 RunClocking();

	 //Для порта "Q" (SPI)
	 HWREG(GPIO_PORTQ_BASE + GPIO_O_DIR)   |= 0x0005;//пины на передачу (PQ3 на прием)
	 HWREG(GPIO_PORTQ_BASE + GPIO_O_DEN)   |= 0x000D;//цифровой сигнал

	 //Для порта "H" (CE)
	 HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DIR) |= 0x0001;//пин на передачу
	 HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DEN) |= 0x0001;//цифровой сигнал
}



void    InitFlash(void)
{
  Init_SPIhandAT45DB321();
  DisableFlash();

// TODO if (SafeReadStatus() == FALSE) TestError(szBadFlash);
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


boolean GetFlashChecksum(void)
{
  MakeCRC16(mpbPageIn, wPAGE_SIZE);

  if ((bCRCHi != 0x00) && (bCRCLo != 0x00))
  {
    if ((bCRCHi != 0x70) && (bCRCLo != 0x7F))
      return FALSE;
  }

  return TRUE;
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
