/*------------------------------------------------------------------------------
KEYBOARD.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_settings.h"
#include        "memory/mem_program.h"
#include        "memory/mem_realtime.h"
#include        "display/display.h"
#include        "beep.h"
#include        "delay.h"
#include        "include/programs.h"
#include        "keyboard_auto.h"
#include        "keyboard_key.h"
#include        "keyboard/key_timedate.h"



//                                         0123456789ABCDEF
char const              szProgram[]     = "Программа ?     ",
                        szMaskKey[]     = " ___            ",
                        szNeed[]        = "Необходимо:     ",
                        szBlock[]       = "Запрещено:      ",
                        szNot[]         = "Нет:            ",
                        szButtonP[]     = "   кнопка 'P'   ",
                        szNoNumber[]    = "номер программы ";


// коды отклика клавиш: '0'..'9', '-', '.', 'Программа', 'Ввод'
uchar const             mpbKeys[14] = { 0x2B, 0x0E, 0x1E, 0x2E, 0x3E, 0x0D, 0x1D, 0x2D, 0x3D, 0x0B, 0x1B, 0x3B, 0x07, 0x17 };

uchar                   bKey;
bool                    fKey;

key                     enKeyboard;

uchar                   bProgram;
uint                    wProgram;

time                    tiKey;

uchar                   ibX, ibY, ibZ;



void    InitKeyboard(void)
{
  enKeyboard = KBD_BEGIN;

  bKey = 0;
  fKey = 0;

  cbShowTime = 0;

  boSetTime     = false;
  boSetDate     = false;
}


// выводит сообщение об отсутствии программы
void    NoProgram(void)
{
  ShowHi(szNot);
  sprintf(szLo,"  программы %u  ",bProgram);
  LongBeep();
}


void    NoProgram2(void)
{
  ShowHi(szNot);
  sprintf(szLo,"  программы %u  ",wProgram);
  LongBeep();
}


// выводит сообщение о невозможности выполнения программы
void    BlockProgram(uchar  bA)
{
  ShowHi(szBlock);
  sprintf(szLo," программой %u  ",bA);
  LongBeep();
}


void    BlockProgram2(uint  wA, bool fBeep)
{
  ShowHi(szBlock);
  sprintf(szLo," программой %u  ",wA);
  if (fBeep == 1) LongBeep();
}


// выводит сообщение о невозможности выполнения программы
void    BlockProgramExt(uchar  bA)
{
  ShowHi(szBlock);
  sprintf(szLo," программой %u  ",bA);
  HideCurrentTime(1);
}


// выводит сообщение о невозможности выполнения программы
void    BlockPrograms(uchar  bA, uchar  bB)
{
  ShowHi(szBlock);
  sprintf(szLo," программы %u,%u ",bA,bB);
  LongBeep();
}


// выводит сообщение о невыполненной программе
void    NeedProgram(uchar  bA)
{
  ShowHi(szNeed);
  sprintf(szLo,"  программа %u  ",bA);
  LongBeep();
}


// выводит сообщение о невыполненных программах
void    NeedPrograms(uchar  bA, uchar  bB)
{
  ShowHi(szNeed);
  sprintf(szLo," программы %u,%u ",bA,bB);
  LongBeep(); 
}



// выводит сообщение о необходимости ввода номера программы
void    NeedNumber(void)
{
  ShowHi(szNeed);
  ShowLo(szNoNumber);

  LongBeep();
  DelayInf();

  bKey = bKEY_PROGRAM;
  fKey = true;
}



// главная функция обработки нажатий на клавиатуру
void    Keyboard(void)
{
uchar   i;

  // постоянно выполняемые программы
  Keyboard_Auto();

  // факт нажатия на клавиатуру
  if (fKey == false) return;
  fKey = false;

  for (i=0; i<sizeof(mpbKeys); i++)
    if (bKey == mpbKeys[i]) break;
      
  if (i < sizeof(mpbKeys)) bKey = i; else return;


  // обнуляем счётчик вызова программы по умолчанию
  cbShowTime = 0;

  // перед вызовом программы необходимо нажать кнопку 'Программа'
  if ((enKeyboard == KBD_BEGIN) && (bKey != bKEY_PROGRAM))
  {
    ShowHi(szNeed);
    ShowLo(szButtonP);
    LongBeep();

    return;     
  }

  // нажаты кнопки '-' или '.'
  if ((bKey == bKEY_MINUS) || (bKey == bKEY_POINT))
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS)) 
    {      
      NeedNumber(); DelayInf();
      bKey = bKEY_PROGRAM;
    }
  }

  // нажата кнопка 'Программа'
  if (bKey == bKEY_PROGRAM)
  {
    enKeyboard = KBD_PROGRAM;
    bProgram = 0;
    wProgram = 0;

    fSlide = false;

    ShowHi(szProgram);
    ShowLo(szMaskKey);

    if (enGlobal == GLB_WORK)
      szLo[0] = '>';
    else
    if (enGlobal == GLB_PROGRAM)
      szLo[0] = '-';
    else
    if (enGlobal == GLB_REPROGRAM)
      szLo[0] = '=';

    return;
  }

  // нажата цифровая кнопка: ввод номера программы
  if (bKey < 10)
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS))
    {
      enKeyboard = KBD_DIGITS;
      ShiftLo(1,3);

      return;
    }
  }

  // нажата кнопка 'Ввод'
  if (bKey == bKEY_ENTER)
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS))
    {      
      enKeyboard = KBD_ENTER;

      wProgram = GetInt(1,3);
      if (wProgram > 0xFF) bProgram = 0xFF; else bProgram = wProgram;

      if (bProgram == 0)
      { 
        NeedNumber();
        return;
      }
      else boReset = true;
    }
  }

  Keyboard_Key();
}
