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



//Áèòû óïðàâëåíèÿ SPI
#define SPI_BIT_SCK   0x0008 //PP3
#define SPI_BIT_SI    0x0010 //PP4
#define SPI_BIT_SO    0x0020 //PP5
#define SPI_BIT_CS    0x0004 //PP2 //âûáîðêà ÷àñîâ ïðè PP2=1 !!!

//Àäðåñà ïèíîâ óïðàâëåíèÿ SPI
#define GPIO_DATABIT_SCK (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0020)//PP3
#define GPIO_DATABIT_SI  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0040)//PP4
#define GPIO_DATABIT_SO  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0080)//PP5
#define GPIO_DATABIT_CS  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0010)//PP2

#define HWREG(x) (*((volatile uint32_t *)(x)))

//3 òàêòà íà çàïóñê ãåíåðàòîðîâ ïåðèôåðèè
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



//Ïîäãîòîâêà ê íà÷àëó ðàáîòû ïî SPI
static void EnableSPI(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = ~SPI_BIT_CS;
}


//Îêîí÷àíèå ðàáîòû ïî SPI
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


time    *GetCurrTimeDate(void)
{
static time ti;

  EnableSPI();
  CharOutSPI(0x00);

  ti.bSecond = FromBCD(CharInSPI());
  ti.bMinute = FromBCD(CharInSPI());
  ti.bHour   = FromBCD(CharInSPI());
                       CharInSPI(); // äåíü íåäåëè
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
  CharOutSPI( 0 ); // äåíü íåäåëè
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

/*
void    TODO OutTrueCurrTimeDate(void) {
uchar   i;
time    ti;

  InitPushCRC();

  ti = *GetCurrTimeDate();
  Push(&ti, sizeof(time));

  PushChar(TrueCurrTimeDate(&ti));

  Output(sizeof(time)+sizeof(bool));
}
*/


void    InitRTC(void) {
  //Âêëþ÷åíèå ïåðèôåðèè
  HWREG(SYSCTL_RCGCGPIO) |= 0x2000;//Çàïóñê ãåíåðàòîðà ïîðòà "P"

  RunClocking();

  //Äëÿ ïîðòà "P" (SPI+CE)
  HWREG(GPIO_PORTP_BASE + GPIO_O_DIR)   |= 0x001C;//ïèíû íà ïåðåäà÷ó (PP5 íà ïðèåì)
  HWREG(GPIO_PORTP_BASE + GPIO_O_DEN)   |= 0x003C;//öèôðîâîé ñèãíàë

  EnableWriteRTC();
  SetLabelRTC();

  DisableSPI();
}



void    RTC_Timer1(void) {
}
