/*------------------------------------------------------------------------------
RTC.C
              
 DS3234EN
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "timedate.h"
#include        "display/lines.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"



#if true

//Биты управления SPI
#define SPI_BIT_SCK   0x0008 //PP3
#define SPI_BIT_SI    0x0010 //PP4
#define SPI_BIT_SO    0x0020 //PP5
#define SPI_BIT_CS    0x0004 //PP2 //выборка часов при PP2=1 !!!

//Адреса пинов управления SPI
#define GPIO_DATABIT_SCK (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0020)//PP3
#define GPIO_DATABIT_SI  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0040)//PP4
#define GPIO_DATABIT_SO  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0080)//PP5
#define GPIO_DATABIT_CS  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0010)//PP2

#define HWREG(x) (*((volatile uint32_t *)(x)))

//3 такта на запуск генераторов периферии
static void RunClocking(void)
{
__asm("   nop\n"
      "   nop\n"
      "   nop\n");
}


static void  CharOutSPI(unsigned char bI)
{
 unsigned char bK;

 for(bK=0; bK<8; bK++)
 {
  if(bI & (0x80 >> bK )) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;
  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 }
}


static unsigned char  CharInSPI(void)
{
 unsigned char bRez, bK;
 bRez = 0;

 for(bK=0; bK<8; bK++)
 {
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x80 >> bK;
 }

 return(bRez);
}



//Подготовка к началу работы по SPI
static void EnableSPI(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = ~SPI_BIT_CS;
}


//Окончание работы по SPI
static void DisableSPI(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
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


void    InitRTC(void) {
  //Включение периферии
  HWREG(SYSCTL_RCGCGPIO) |= 0x2000;//Запуск генератора порта "P"

  RunClocking();

  //Для порта "P" (SPI+CE)
  HWREG(GPIO_PORTP_BASE + GPIO_O_DIR)   |= 0x001C;//пины на передачу (PP5 на прием)
  HWREG(GPIO_PORTP_BASE + GPIO_O_DEN)   |= 0x003C;//цифровой сигнал

  EnableWriteRTC();
  DisableSPI();
}



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


void    SetCurrTimeDate(time  *pti)
{
  EnableSPI();
  CharOutSPI(0x80);

  CharOutSPI( ToBCD(pti->bSecond) );
  CharOutSPI( ToBCD(pti->bMinute) );
  CharOutSPI( ToBCD(pti->bHour)   );
  CharOutSPI( 0 ); // день недели
  CharOutSPI( ToBCD(pti->bDay)    );
  CharOutSPI( ToBCD(pti->bMonth)  );
  CharOutSPI( ToBCD(pti->bYear)   );

  DisableSPI();
}


void    SetCurrTime(time  *pti)
{
  EnableSPI();
  CharOutSPI(0x80);

  CharOutSPI( ToBCD(pti->bSecond) );
  CharOutSPI( ToBCD(pti->bMinute) );
  CharOutSPI( ToBCD(pti->bHour)   );

  DisableSPI();
}


void    SetCurrDate(time  *pti)
{
  EnableSPI();
  CharOutSPI(0x84);

  CharOutSPI( ToBCD(pti->bDay)   );
  CharOutSPI( ToBCD(pti->bMonth) );
  CharOutSPI( ToBCD(pti->bYear)  );

  DisableSPI();
}



bool    TrueCurrTimeDate(time  *pti)
{
  if (pti->bSecond == FromBCD(0xFF)) return(0);
  if (pti->bMinute == FromBCD(0xFF)) return(0);
  if (pti->bHour   == FromBCD(0xFF)) return(0);
  if (pti->bDay    == FromBCD(0xFF)) return(0);
  if (pti->bMonth  == FromBCD(0xFF)) return(0);
  if (pti->bYear   == FromBCD(0xFF)) return(0);

  if (pti->bSecond > 59) return(0);
  if (pti->bMinute > 59) return(0);
  if (pti->bHour   > 23) return(0);

  if ((pti->bDay == 0) ||
      (pti->bDay > 31)) return(0);

  if ((pti->bMonth == 0) ||
      (pti->bMonth > 12 )) return(0);

  if ((pti->bYear < bMINYEAR) ||
      (pti->bYear > bMAXYEAR)) return(0);

  return(1);
}


void    RTC_Timer1(void) {
}

#else

ulong                   dwRTC;



void    InitRTC(void) {
  tiGetRTC.bSecond = 0;
  tiGetRTC.bMinute = 0;
  tiGetRTC.bHour   = 0;
  tiGetRTC.bDay    = 0;
  tiGetRTC.bMonth  = 0;
  tiGetRTC.bYear   = 0;

  tiAlt.bSecond = 0;
  tiAlt.bMinute = 0;
  tiAlt.bHour   = 0;
  tiAlt.bDay    = 31;
  tiAlt.bMonth  = 12;
  tiAlt.bYear   = 14;

  dwRTC = DateToSecIndex();
}



time    *GetCurrTimeDate(void) {
  return &tiGetRTC;
}


void    SetCurrTimeDate(void) {
  SecIndexToDate(dwRTC);

  tiAlt.bSecond = tiSetRTC.bSecond;
  tiAlt.bMinute = tiSetRTC.bMinute;
  tiAlt.bHour   = tiSetRTC.bHour;
  tiAlt.bDay    = tiSetRTC.bHour;
  tiAlt.bMonth  = tiSetRTC.bMonth;
  tiAlt.bYear   = tiSetRTC.bYear;

  dwRTC = DateToSecIndex();
}


void    SetCurrTime(void) {
  SecIndexToDate(dwRTC);

  tiAlt.bSecond = tiSetRTC.bSecond;
  tiAlt.bMinute = tiSetRTC.bMinute;
  tiAlt.bHour   = tiSetRTC.bHour;

  dwRTC = DateToSecIndex();
}


void    SetCurrDate(void) {
  SecIndexToDate(dwRTC);

  tiAlt.bDay    = tiSetRTC.bHour;
  tiAlt.bMonth  = tiSetRTC.bMonth;
  tiAlt.bYear   = tiSetRTC.bYear;

  dwRTC = DateToSecIndex();
}



void    RTC_Timer1(void) {
  SecIndexToDate(++dwRTC);
  tiGetRTC = tiAlt;
}

#endif
