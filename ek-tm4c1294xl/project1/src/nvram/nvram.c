/*------------------------------------------------------------------------------
NVRAM.С


------------------------------------------------------------------------------*/
#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../memory/mem_nvram.h"
#include "../kernel/crc-16.h"
#include "../time/delay.h"
#include "nvram.h"



//Общий объем памяти
#define MAX_SIZE_23LC1024 (128 * 1024) //128кб
//Количество повторов при операциях записи в ЭОЗУ
#define MAXREPEATS_23LC1024    10

  //Биты управления SPI
  #define SPI_BIT_SO    0x0001 //PF0
  #define SPI_BIT_SI    0x0002 //PF1
  #define SPI_BIT_CS    0x0004 //PF2
  #define SPI_BIT_SCK   0x0008 //PF3

  //Адреса пинов управления SPI
  #define GPIO_DATABIT_SO  (GPIO_PORTF_BASE + GPIO_O_DATA + 0x0004)//PF0
  #define GPIO_DATABIT_SI  (GPIO_PORTF_BASE + GPIO_O_DATA + 0x0008)//PF1
  #define GPIO_DATABIT_CS  (GPIO_PORTF_BASE + GPIO_O_DATA + 0x0010)//PF2
  #define GPIO_DATABIT_SCK (GPIO_PORTF_BASE + GPIO_O_DATA + 0x0020)//PF3

 #define DELAY_NEW_STAT_PIN 1

static void NvramDelay(ulong ulgTime)
{
 while(ulgTime--);
}

//Передача одного байта
//Биты читаются микросхемой ЭОЗУ по переднему фронту
 void  NvramCharOut(uchar bI)
{
  cdwNvramWriteBytes++;

 uchar i;
 for(i=0; i<8; i++)
 {
  if(bI & (0x80 >> i )) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;
  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 }
}



//Прием одного байта
//Биты фиксируются микросхемой ЭОЗУ в течении активности импульса (высокий уровень на SCK)
uchar  NvramCharIn(void)
{
  cdwNvramReadBytes++;

 uchar b = 0;

 uchar i;
 for(i=0; i<8; i++)
 {
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  if(HWREG(GPIO_DATABIT_SO)) b |= 0x80 >> i;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 }

 return(b);
}


/*
//Один синхроимпульс
static void  OnePulse_1(void)
{
 HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
}//end OnePulse
*/
//Подготовка к началу работы по SPI
void NvramStart(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = ~SPI_BIT_CS;
 NvramDelay(DELAY_NEW_STAT_PIN);
}

//Окончание работы по SPI
void NvramStop(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 NvramDelay(DELAY_NEW_STAT_PIN);
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
}
