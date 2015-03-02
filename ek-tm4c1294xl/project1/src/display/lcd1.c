/*------------------------------------------------------------------------------
LCD1.C


------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>

#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "../main.h"
#include "../display/display.h"
#include "cp1251.h"
#include "lcd.h"

#ifndef NATIVE_LCD

#define HWREG(x) (*((volatile uint32_t *)(x)))

#define PF2_TO_PD0_WR

//Биты управления ЖКИ
#define LCD_BIT_DIR  0x01 //PF0
#define LCD_BIT_RS   0x02 //PF1
#define LCD_BIT_WR   0x04 //PF2 //PD0
#define LCD_BIT_E    0x08 //PF3




//3 такта на запуск генераторов периферии
static void RunClocking(void)
{
__asm("   nop\n"
      "   nop\n"
      "   nop\n");
}

static void _NOP(void)
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


#endif
