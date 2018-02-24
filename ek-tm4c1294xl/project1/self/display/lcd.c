/*------------------------------------------------------------------------------
LCD!C


------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>
#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "driverlib/interrupt.h"
#include "../main.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "../hardware/beep.h"
#include "../hardware/watchdog.h"
#include "cp1251.h"
#include "start_error.h"
#include "lcd.h"

#define LCD_FLAG_COMM    0x00 // передать команду
#define LCD_FLAG_DATA    0x01 // передать данные


static uchar const      szName[]        = "    СЭМ-2.01    ",
                        szTest[]        = "                ";


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


void SetCtrlBit_LCD(unsigned int wSetBit);
void ClearCtrlBit_LCD(unsigned int wSetBit);

void Write_Byte_LCD(unsigned char bflagDC, unsigned char bData);
unsigned char Read_Byte_LCD(unsigned char bflagDC);

void InitGPIO_LCD(void);

unsigned char bCursorPos;


// Задержка
//~[ 1 = 440 nsec; 2300000 = 1 sec - for 25MHz]
static void _Delay(unsigned long ulgTime)
{
 while(ulgTime--);
}


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

//Вывод символа в заданную позицию ЖКИ
void  ShowCharLCD(unsigned char  bPos, unsigned char  bSymb)
{
 ReadyLCD();
 SetCommLCD(bPos);

 ReadyLCD();
 SetDataLCD(bSymb);
}

// Прямая запись в строку ЖКИ без кириллицы
void  ShowMsgLCDnCyr(uchar bT, uchar *szT)
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
void  ShowMsgLCD(uchar  bT, const uchar  *szT)
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

void  ShowMsgLCD2(uchar  bT, char  *szT)
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


// вывод отметки о прохождении очередного теста
void    TestOK(void)
{
  ReadyLCD();   SetDataLCD('-');
}


// вывод сообщения о ошибке теста
void    TestError(const char  *szT)
{
#ifdef NO_DISPLAY
  StartError(szT);
#else
  IntMasterDisable();

  ShowMsgLCD(0x80, (const uchar *)szAlarm);
  ShowMsgLCD(0xC0, (const uchar *)szT);

  while (1)
  {
    ResetWatchdog();
    DelayMsg(); Beep();
  }
#endif
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

  ReadyLCD();   SetCommLCD(0xC4);
}

 uchar bPos =0;
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

