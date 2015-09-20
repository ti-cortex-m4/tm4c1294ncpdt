/*------------------------------------------------------------------------------
RTC.C TODO RTC read temperature
              
 DS3234EN
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../time/timedate.h"
#include "../display/lines.h"
#include "../time/delay.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "rtc.h"
#include "rtc1.h"
#include "rtc2.h"



static void Wait(void) // TODO
{
}


static void  CharOutSPI(unsigned char bI)
{
 unsigned char bK;

 for(bK=0; bK<8; bK++)
 {
  if(bI & (0x80 >> bK )) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;
  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
  Wait();
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  Wait();
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
  Wait();
 }
}


static unsigned char  CharInSPI(void)
{
 unsigned char bRez, bK;
 bRez = 0;

 for(bK=0; bK<8; bK++)
 {
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  Wait();
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
  Wait();
  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x80 >> bK;
  Wait();
 }

 return(bRez);
}



//Подготовка к началу работы по SPI
static void EnableSPI(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 Wait();
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
 Wait();
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 Wait();
 HWREG(GPIO_DATABIT_CS)  = ~SPI_BIT_CS;
 Wait();
}


//Окончание работы по SPI
static void DisableSPI(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 Wait();
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
 Wait();
}



void    EnableWriteRTC(void) {
  EnableSPI();

  CharOutSPI(0x8F);
  CharOutSPI(0x04);

  DisableSPI();
}

/*
void    DisableWriteRTC(void) {
  EnableSPI();

  CharOutSPI(0x8F);
  CharOutSPI(0x44);

  DisableSPI();
}
*/


time    *GetCurrTimeDate(void)
{
static time ti;

  EnableSPI();
  CharOutSPI(0x00);

  ti.bSecond = FromBCD(CharInSPI());
  ti.bMinute = FromBCD(CharInSPI());
  ti.bHour   = FromBCD(CharInSPI());
                       CharInSPI(); // день недели
  ti.bDay    = FromBCD(CharInSPI());
  ti.bMonth  = FromBCD(CharInSPI());
  ti.bYear   = FromBCD(CharInSPI());

  DisableSPI();

  return &ti;
}


void    SetCurrTimeDate(time  ti)
{
  EnableSPI();
  CharOutSPI(0x80);

  CharOutSPI( ToBCD(ti.bSecond) );
  CharOutSPI( ToBCD(ti.bMinute) );
  CharOutSPI( ToBCD(ti.bHour)   );
  CharOutSPI( 0 ); // день недели
  CharOutSPI( ToBCD(ti.bDay)    );
  CharOutSPI( ToBCD(ti.bMonth)  );
  CharOutSPI( ToBCD(ti.bYear)   );

  DisableSPI();
}


void    SetCurrTime(time  ti)
{
  EnableSPI();
  CharOutSPI(0x80);

  CharOutSPI( ToBCD(ti.bSecond) );
  CharOutSPI( ToBCD(ti.bMinute) );
  CharOutSPI( ToBCD(ti.bHour)   );

  DisableSPI();
}


void    SetCurrDate(time  ti)
{
  EnableSPI();
  CharOutSPI(0x84);

  CharOutSPI( ToBCD(ti.bDay)   );
  CharOutSPI( ToBCD(ti.bMonth) );
  CharOutSPI( ToBCD(ti.bYear)  );

  DisableSPI();
}



void    SetLabelRTC(void)
{
uchar   i;

  EnableSPI();

  CharOutSPI(0xA0);
  for (i=0; i<0x10; i++) CharOutSPI(i);

  DisableSPI();
}


bool    GetLabelRTC(void)
{
uchar   i;

  EnableSPI();

  CharOutSPI(0x20);
  for (i=0; i<0x10; i++)
    if (CharInSPI() != i) return(0);

  DisableSPI();

  return(1);
}

/*
void    TODO OutLabelRTC(void) {
uchar   i;

  InitPushCRC();

  EnableSPI();

  CharOutSPI(0x20);
  for (i=0; i<0x10; i++)
    PushChar(CharInSPI());

  DisableSPI();

  PushChar(GetLabelRTC());

  Output(0x10+sizeof(bool));
}
*/


bool    IsValidTimeDateRTC(time  ti)
{
  if (ti.bSecond == FromBCD(0xFF)) return(0);
  if (ti.bMinute == FromBCD(0xFF)) return(0);
  if (ti.bHour   == FromBCD(0xFF)) return(0);
  if (ti.bDay    == FromBCD(0xFF)) return(0);
  if (ti.bMonth  == FromBCD(0xFF)) return(0);
  if (ti.bYear   == FromBCD(0xFF)) return(0);

  if (ti.bSecond > 59) return(0);
  if (ti.bMinute > 59) return(0);
  if (ti.bHour   > 23) return(0);

  if ((ti.bDay == 0) ||
      (ti.bDay > 31)) return(0);

  if ((ti.bMonth == 0) ||
      (ti.bMonth > 12 )) return(0);

  if ((ti.bYear < bMINYEAR) ||
      (ti.bYear > bMAXYEAR)) return(0);

  return(1);
}

/*
void    TODO OutTrueCurrTimeDate(void) {
uchar   i;
time    ti;

  InitPushCRC();

  ti = *GetCurrTimeDate();
  Push(&ti, sizeof(time));

  PushChar(TrueCurrTimeDate(ti));

  Output(sizeof(time)+sizeof(bool));
}
*/


void    InitRTC(void) {
	InitGPIO_RTC();

  EnableWriteRTC();
  SetLabelRTC();

  DisableSPI();
}
