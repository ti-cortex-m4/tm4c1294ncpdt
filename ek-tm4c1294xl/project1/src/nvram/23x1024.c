/*------------------------------------------------------------------------------
23x1024.С


------------------------------------------------------------------------------*/
#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../time/delay.h"
#include "23x1024.h"



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

static void Delay_1(ulong ulgTime)
{
 while(ulgTime--);
}

//Передача одного байта
//Биты читаются микросхемой ЭОЗУ по переднему фронту
static void  CharOut(uchar bI)
{
 uchar bK;

 for(bK=0; bK<8; bK++)
 {
  if(bI & (0x80 >> bK )) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;
  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 }
}//end CharOut

//Прием одного байта
//Биты фиксируются микросхемой ЭОЗУ в течении активности импульса (высокий уровень на SCK)
static uchar  CharIn(void)
{
 uchar bRez, bK;

 bRez = 0;
 for(bK=0; bK<8; bK++)
 {
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x80 >> bK;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 }
 return(bRez);
}//end CharIn
/*
//Один синхроимпульс
static void  OnePulse_1(void)
{
 HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
}//end OnePulse
*/
//Подготовка к началу работы по SPI
static void Start(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = ~SPI_BIT_CS;
 Delay_1(DELAY_NEW_STAT_PIN);
}

//Окончание работы по SPI
static void Stop(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 Delay_1(DELAY_NEW_STAT_PIN);
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
}

//Первичная инициализация SPI
//По умолчанию режим: Sequential mode (режим непрерывного чтения/записи по всему объему ЭОЗУ)
void Init_EOZU(void)
{
 //Включение периферии
 HWREG(SYSCTL_RCGCGPIO) |= 0x00000020;//Запуск "F"

 DelayGPIO();

 //Для порта "F" (SPI+CE)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DIR)   |= 0x000E;//пины на передачу (PF0 на прием)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DEN)   |= 0x000F;//цифровой сигнал

 Stop();
}

//Чтение в буфер *ptrMas, начиная с байта lgAddr количества байт lgSize
void LoadBytes_EOZU(uchar *ptrMass, ulong lgAddr, ulong lgSize)
{
 if(((lgAddr + lgSize) > MAX_SIZE_23LC1024) || (lgSize == 0)) return;//превышение допустимых границ SRAM

 Start();
 CharOut(0x03);//чтение
 CharOut(*((uchar*)(&lgAddr)+2)); //24-х битный адрес
 CharOut(*((uchar*)(&lgAddr)+1));
 CharOut(*((uchar*)(&lgAddr)+0));

 while(lgSize--)
 {
  *(ptrMass++) = CharIn();
 }

 Stop();
}


//Запись из буфера *ptrMas, начиная с байта lgAddr количества байт lgSize
//=1 - ошибка записи
//=0 - запись успешно завершена
uchar SaveBytes_EOZU(uchar *ptrMass, ulong lgAddr, ulong lgSize)
{
 ulong lgSaveSize;
 uchar bi;

 if(((lgAddr + lgSize) > MAX_SIZE_23LC1024) || (lgSize == 0)) return(1);//превышение допустимых границ SRAM

 lgSaveSize = lgSize;

 for(bi=0; bi<MAXREPEATS_23LC1024; bi++)
 {
  lgSize = lgSaveSize;

  //Запись массива
  Start();
  CharOut(0x02);//запись
  CharOut(*((uchar*)(&lgAddr)+2)); //24-х битный адрес
  CharOut(*((uchar*)(&lgAddr)+1));
  CharOut(*((uchar*)(&lgAddr)+0));

  while(lgSize--)
  {
   CharOut(*(ptrMass++));
  }
  Stop();

  //Проверка записанных данных
  lgSize = lgSaveSize;
  ptrMass -= lgSize;

  Start();
  CharOut(0x03);//чтение
  CharOut(*((uchar*)(&lgAddr)+2)); //24-х битный адрес
  CharOut(*((uchar*)(&lgAddr)+1));
  CharOut(*((uchar*)(&lgAddr)+0));

  while(lgSize--)
  {
   if(*(ptrMass++) != CharIn()) break;
  }
  Stop();

  if((++lgSize) == 0) break;//все верно - выходим
  else
  {//иначе повторяем запись, начиная с неверного байта
   lgAddr += (lgSaveSize-lgSize);
   ptrMass--;
   lgSaveSize = lgSize;
  }
 }//for(bi=0; bi<MAXREPEATS_23LC1024; bi++)

 if(bi == MAXREPEATS_23LC1024) return(1);
 else return(0);
}

//чтение регистра режима работы ЭОЗУ
uchar ReadModeReg_EOZU(void)
{
 uchar bRez;

 Start();
 CharOut(0x05);
 bRez = CharIn();
 Stop();

 return(bRez);
}
