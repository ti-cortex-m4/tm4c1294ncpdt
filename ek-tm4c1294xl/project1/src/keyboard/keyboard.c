/*------------------------------------------------------------------------------
KEYBOARD.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_program.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../display/display.h"
#include "../hardware/beep.h"
#include "../realtime/realtime.h"
#include "../time/delay.h"
#include "../serial/print.h"
#include "../serial/modems.h"
#include "../digitals/answer.h"
#include "../include/programs.h"
#include "../impulses/impulses.h"
#include "../digitals/digitals_status.h"
#include "../devices/devices.h"
#include "../digitals/wait_query.h"
#include "../special/special.h"
#include "../settings.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "keyboard_auto.h"
#include "keyboard_key.h"
#include "time/key_timedate.h"



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

volatile uchar          bKey;
volatile bool           fKey;

key                     enKeyboard;

uint                    wProgram;

time                    tiKey;

uchar                   ibX, ibY, ibZ;



void    InitKeyboard(void)
{
  enKeyboard = KBD_BEGIN;

  bKey = 0;
  fKey = 0;

  cbShowCurrentTime = 0;
}


// выводит сообщение об отсутствии программы
void    NoProgram(void)
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
  HideCurrTime(1);
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
void    RunKeyboard(void)
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


  // обновляем показания на дисплее
  fOnImpulse = 1;
  fOnSecond = 1;

  // обнуляем счётчик вызова программы по умолчанию
  cbShowCurrentTime = 0;

  // разрешаем оставаться в режиме connect на следующие паузу bMAXWAITONLINE
  cbWaitOnline = 0;

  // останавливаем опрос цифровых счётчиков
  if ((fConnect == 1) || (GetCurr() != DEV_BEGIN))
  {
//    if (bKey != bKEY_PROGRAM) return;

    if (((wProgram != bGET_READTIMEDATE1) &&
         (wProgram != bGET_READTIMEDATE2) &&
         (wProgram != wGET_READTRANS)     &&
         (wProgram != wGET_READPULSE)     &&
         (wProgram != bTEST_DIRECT)       &&
         (wProgram != bGET_CNTCANYEAR1)   &&
         (wProgram != bGET_CNTCANYEAR10)  &&
//         (wProgram != bGET_CNTCANYEAR2)   &&
//         (wProgram != bGET_CNTCANYEAR20)  &&
         (wProgram != bGET_CNTCURR_10)    &&
         (wProgram != bGET_CNTCURR_110))  || (bKey == bKEY_PROGRAM))
    {
      SetCurr(DEV_BEGIN);
      SetPause(DEV_BEGIN);

      if (IsOpenSpecial()) { CloseSpecial(); Stop(); }
      CloseSpecialBuff();

      AddDigRecord(EVE_SPECIALCLOSE);

      KeyBreakConnect();
      EnableAnswer();
      return;
    }
  }

  // останавливаем опрос цифровых счётчиков
  if (fCurrent == 1)
  {
    SetCurr(DEV_BEGIN);
    if (cbWaitQuery == 0) cbWaitQuery = bMAXWAITQUERY;
  }

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

    PrintStop();
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

      wProgram = GetIntLo(1,3);
      if (wProgram == 0)
      { 
        NeedNumber();
        return;
      }
      else
      {
        boFirstReset = TRUE;
        //SaveFile(&flFirstReset);
      }
    }
  }

  Keyboard_Key();
}
