
//tm4c1294ncpdt.pdf :
// GPIO - page 757 


#include <stdint.h>
#include <stdio.h>

#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "../main.h"
#include "../display/display.h"
#include "cp1251.h"

#define HWREG(x) (*((volatile uint32_t *)(x)))

//адреса строк дисплея
#define LINE_HI         0x80
#define LINE_LO         0xC0

#define PF2_TO_PD0_WR

//Биты управления ЖКИ
#define LCD_BIT_DIR  0x01 //PF0
#define LCD_BIT_RS   0x02 //PF1
#define LCD_BIT_WR   0x04 //PF2 //PD0
#define LCD_BIT_E    0x08 //PF3

#define LCD_FLAG_COMM    0x00 // передать команду
#define LCD_FLAG_DATA    0x01 // передать данные


static uchar const      szName[]        = "     СЭМ+2      ",
                        szTest[]        = "   [       ]    ";


static uchar const      mpbUserFonts[64] =
{
  0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x16, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


unsigned char bCursorPos;


// Задержка
//~[ 1 = 440 nsec; 2300000 = 1 sec - for 25MHz]
void _Delay(unsigned long ulgTime)
{
 while(ulgTime--);
}

//3 такта на запуск генераторов периферии
static void RunClocking(void)
{
__asm("   nop\n"
      "   nop\n"
      "   nop\n");
}

void _NOP(void)
{
  __asm(" nop\n");
}

//Установка одного или нескольких из управляющих битов ЖКИ
void SetCtrlBit_LCD(unsigned int wSetBit)
{
 #ifdef	PF2_TO_PD0_WR
  if(wSetBit & LCD_BIT_WR)
   HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0004) = 0x0001;
  else
   HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + (wSetBit << 2) ) = wSetBit;
 #else
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + (wSetBit << 2) ) = wSetBit;
 #endif
}

//Сброс одного или нескольких из управляющих битов ЖКИ
void ClearCtrlBit_LCD(unsigned int wSetBit)
{
 #ifdef	PF2_TO_PD0_WR
  if(wSetBit & LCD_BIT_WR)
   HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0004) = 0x0000;
  else
   HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + (wSetBit << 2) ) = ~wSetBit;
 #else
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + (wSetBit << 2) ) = ~wSetBit;
 #endif
}

//Порт "К" на передачу данных.
void SetPortK_Out(void)
{
 SetCtrlBit_LCD(LCD_BIT_DIR);//DIR = 1, Буфер согласования уровней на передачу
 HWREG(GPIO_PORTK_BASE + GPIO_O_DIR) |= 0x000000FF;//Пины порта "К" на передачу
}

//Порт "К" на прием данных.
void SetPortK_In(void)
{
 ClearCtrlBit_LCD(LCD_BIT_DIR);//DIR = 0, Буфер согласования уровней на прием
 HWREG(GPIO_PORTK_BASE + GPIO_O_DIR) &= 0xFFFFFF00;//Пины порта "К" на прием
}

//Запись байта в ЖКИ
void Write_Byte_LCD(unsigned char bflagDC, unsigned char bData)
{
 SetPortK_Out();

 if(bflagDC) SetCtrlBit_LCD(LCD_BIT_RS);  //RS=1 - данные
 else ClearCtrlBit_LCD(LCD_BIT_RS);       //RS=0 - команда

 ClearCtrlBit_LCD(LCD_BIT_WR);//WR=0 - запись

 HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x3FC) = bData;//записываем в порт "K" 8 бит данных (шина данных)

 SetCtrlBit_LCD(LCD_BIT_E);    //E=1
 _NOP();//мин. импульс 230 нсек.
 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0
}

//Чтение байта из ЖКИ
unsigned char Read_Byte_LCD(unsigned char bflagDC)
{
 SetPortK_In();

 if(bflagDC) SetCtrlBit_LCD(LCD_BIT_RS);  //RS=1 - данные
 else ClearCtrlBit_LCD(LCD_BIT_RS);       //RS=0 - команда

 SetCtrlBit_LCD(LCD_BIT_WR);   //WR=1 - чтение
 SetCtrlBit_LCD(LCD_BIT_E);    //E=1
 _NOP();//мин. импульс 230 нсек.

 bflagDC = HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x3FC);//читаем из порта "K" 8 бит данных (шина данных)

 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0
 ClearCtrlBit_LCD(LCD_BIT_WR); //WR=0

 return(bflagDC);
}
/*
//Включает мерцание курсора
void CursorOnLCD(void)
{
  ReadyLCD();  SetCommLCD(0x0D);
}

//Отключает мерцание курсора
void CursorOffLCD(void)
{
  ReadyLCD();  SetCommLCD(0x0C);
}

//Возвращает курсор в начальную позицию
void CursorClearPosLCD(void)
{
  ReadyLCD();  SetCommLCD(0x02);
  bCursorPos = 0;
}

//Смещает курсор вправо на одну позицию (если конец строки, то переходит на следующую)
void CursorRShiftLCD(void)
{
  ReadyLCD();  SetCommLCD(0x14);
  bCursorPos++;
}

//Смещает курсор влево на одну позицию (если конец строки, то переходит на следующую)
void CursorLShiftLCD(void)
{
  ReadyLCD(); SetCommLCD(0x10);
  bCursorPos--;
}

//установка курсора в заданную позицию (0..15 - верхняя строка, 16..31 - нижняя строка)
void CursorSetPosLCD(unsigned char bPos)
{
 if(bPos != bCursorPos)
 {
  CursorOffLCD();
  if(bPos > bCursorPos) while(bCursorPos != bPos) CursorRShiftLCD();
  else  while(bCursorPos != bPos) CursorLShiftLCD();
  CursorOnLCD();
 }
}
*/
// Запись команды в контроллер ЖКИ
void SetCommLCD(unsigned char  bT)
{
 Write_Byte_LCD(LCD_FLAG_COMM, bT);
}

// Запись данных в контроллер ЖКИ
void    SetDataLCD(unsigned char  bT)
{
 Write_Byte_LCD(LCD_FLAG_DATA, bT);
}

//Чтение бита готовности
unsigned char GetCommLCD(void)
{
 return( Read_Byte_LCD(LCD_FLAG_COMM) & 0x80 );
}

// Ожидание готовности ЖКИ
void    ReadyLCD(void)
{
 // при готовности контроллера ЖКИ, бит готовности = 0
  while ( GetCommLCD() );
}

//Вывод байта в заданную позицию ЖКИ в HEX(два символа)
void  ShowCharLCD_HEX(unsigned char  bPos, unsigned char  bHEX)
{
 ReadyLCD(); SetCommLCD(bPos);
 ReadyLCD(); if(((bHEX >> 4)& 0x0F) > 9) SetDataLCD( (((bHEX >> 4) & 0x0F) - 10) + 0x41);
             else SetDataLCD( ((bHEX >> 4) & 0x0F) + 0x30 );

 ReadyLCD(); SetCommLCD(bPos+1);
 ReadyLCD(); if((bHEX & 0x0F) > 9) SetDataLCD( ((bHEX & 0x0F) - 10) + 0x41);
             else SetDataLCD( (bHEX & 0x0F) + 0x30 );
}

//Вывод байта в заданную позицию ЖКИ в BCD(два символа)
void  ShowCharLCD_BCD(unsigned char  bPos, unsigned char  bBCD)
{
 ReadyLCD(); SetCommLCD(bPos);
 ReadyLCD(); SetDataLCD( ((bBCD >> 4) & 0x0F) + 0x30 );

 ReadyLCD(); SetCommLCD(bPos+1);
 ReadyLCD(); SetDataLCD( (bBCD & 0x0F) + 0x30 );
}

//Вывод символа в заданную позицию ЖКИ
void  ShowCharLCD(unsigned char  bPos, unsigned char  bSymb)
{
 ReadyLCD();
 SetCommLCD(bPos);

 ReadyLCD();
 SetDataLCD(bSymb);
}

// Прямая запись в строку ЖКИ без кириллицы
void  ShowMsgLCDnCyr(unsigned char bT, unsigned char *szT)
{
 unsigned char   i;

  ReadyLCD();
  SetCommLCD(bT);

  for (i=0; i<16; i++)
  {
    if ( !*szT ) break;
    ReadyLCD();
    SetDataLCD( *szT++ );
  }
}

// Прямая запись в строку ЖКИ с кириллицой
void  ShowMsgLCD(unsigned char  bT, const unsigned char  *szT)
{
 unsigned char  i;

  ReadyLCD();
  SetCommLCD(bT);

  for (i=0; i<16; i++)
  {
    if ( !*szT ) break;
    ReadyLCD();
    SetDataLCD( mpbCyrillic[ *szT++ ] );
  }
}

//Инициализация портов GPIO для работы с индикатором
void InitGPIO_LCD(void)
{
 #ifdef	PF2_TO_PD0_WR
  HWREG(SYSCTL_RCGCGPIO) |= 0x0228;//Запуск генераторов портов "F" и "K" и "D"
 #else
  HWREG(SYSCTL_RCGCGPIO) |= 0x0220;//Запуск генераторов портов "F" и "K"
 #endif

 RunClocking();

 HWREG(GPIO_PORTK_BASE + GPIO_O_DEN) |= 0xFF;//работа с цифровым сигналом
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0F;//работа с цифровым сигналом

 SetPortK_Out();//Пины порта "К" на передачу данных
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0F;//младшие пины Порта "F" на передачу (управляющие всегда на передаче)

 #ifdef	PF2_TO_PD0_WR
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x01;//PD0
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x01;//PD0
 #endif

 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0 Индикатор не выбран
 ClearCtrlBit_LCD(LCD_BIT_WR); //WR=0
}

void    InitLCD(void)
{
uchar  i;

  InitGPIO_LCD();

  _Delay(50000);    SetCommLCD(0x30);
  _Delay(50000);    SetCommLCD(0x30);
  _Delay(50000);    SetCommLCD(0x30);

  ReadyLCD();   SetCommLCD(0x38);
  ReadyLCD();   SetCommLCD(0x08);
  ReadyLCD();   SetCommLCD(0x01);
  ReadyLCD();   SetCommLCD(0x06);
  ReadyLCD();   SetCommLCD(0x0C);

  ReadyLCD();   SetCommLCD(0x40);       // загрузка символов пользователя
  for (i=0; i<64; i++)
  {
    ReadyLCD();
    SetDataLCD( mpbUserFonts[i] );
  }

  ShowMsgLCD(0x80, szName);
  ShowMsgLCD(0xC0, szTest);
}

static uchar bPos =0;
void LCD_Timer0() {
	  if (GetCommLCD() == 0)
	  {
	    if (bPos == 0)
	    {
	      SetCommLCD(0x80);
	      bPos++;
	    }
	    else
	    if (bPos <  17)
	    {
	      SetDataLCD( mpbCyrillic[ szHi[bPos-1] ] );
	      bPos++;
	    }
	    else
	    if (bPos == 17)
	    {
	      SetCommLCD(0xC0);
	      bPos++;
	    }
	    else
	    if (bPos <  34)
	    {
	      SetDataLCD( mpbCyrillic[ szLo[bPos-18] ] );
	      bPos++;
	    }
	    else
	    if (bPos >= 34)
	      bPos = 0;
	  }
}
