/*------------------------------------------------------------------------------
KEYBOARD.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_program.h"
#include        "display.h"
#include        "slide.h"
#include        "beep.h"
#include        "label.h"
#include        "delay.h"
#include        "include/programs.h"
#include        "keyboard/key_timedate.h"
#include        "keyboard/key_password.h"
#include        "keyboard/key_logical.h"
#include        "keyboard/key_private.h"
#include        "keyboard/key_start.h"
#include        "keyboard/key_version.h"
#include        "keyboard/key_decret.h"
#include        "keyboard/key_season.h"
#include        "keyboard/key_groups.h"
#include        "keyboard/key_dayzone.h"
#include        "keyboard/key_canals.h"
#include        "keyboard/key_delays.h"
#include        "keyboard/key_reset.h"
#include        "keyboard/key_analysis.h"



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

global                  enGlobal;

uchar                   bProgram;
uint                    wProgram;

uchar                   cbShowTime;

time                    tiKey;

uchar                   ibX, ibY, ibZ;



void    InitKeyboard(void)
{
  enKeyboard = KBD_BEGIN;

  bKey = 0;
  fKey = 0;

  cbShowTime = 0;

  boSetTime     = boFalse;
  boSetDate     = boFalse;

  if (GetLabel() == true)
    enGlobal = GLB_WORK;
  else
    enGlobal = GLB_PROGRAM;
}



// включение просмотра текущего времени при бездействии пользователя
void    ShowTimeNow(void)
{
  bProgram = bGET_CURRTIME;
  fSlide = 0;

  enKeyboard = KBD_POSTENTER;
  ibZ = 60;

  ShowHi(szTime);
  Clear();
}


// выключение просмотра текущего времени
void    NoShowTime(bool  fClear)
{
  cbShowTime = 0;
  fSlide = false;

  if (fClear == true)
  {
    enKeyboard = KBD_BEGIN;
    bProgram = 0;
    wProgram = 0;
  }
}



// выводит сообщение об отсутствии программы
void    NoProgram(void)
{
  ShowHi(szNot);
  sprintf(szLo,"  программы %u  ",bProgram);
  LongBeep();
}


// выводит сообщение о невозможности выполнения программы
void    BlockProgram(uchar  bA)
{
  ShowHi(szBlock);
  sprintf(szLo," программой %u  ",bA);
  LongBeep();
}


// выводит сообщение о невозможности выполнения программы
void    BlockProgramExt(uchar  bA)
{
  ShowHi(szBlock);
  sprintf(szLo," программой %u  ",bA);
  NoShowTime(1);
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
  if (enGlobal == GLB_PROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bGET_ANALYSIS1:      auto_Analysis1();       break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (bProgram)
    {
      case bGET_CURRTIME:       auto_GetCurrTime();     break;
      case bGET_CURRDATE:       auto_GetCurrDate();     break;

      case bGET_ANALYSIS1:      auto_Analysis1();       break;
    }                        
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bGET_ANALYSIS1:      auto_Analysis1();       break;
    }
  }

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
      else boReset = boTrue;
    }
  }

  // базовая обработка нажатий кнопок
  if (enGlobal == GLB_PROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;

      case bSET_GROUPS:         key_SetGroups();        break;

      case bSET_TRANS_ENG:
      case bSET_TRANS_CNT:
      case bSET_PULSE_HOU:
      case bSET_PULSE_MNT:
      case bSET_LOSSE:
      case bSET_LEVEL:
      case bSET_COUNT:          key_SetCanals();        break;

      case bSET_DAYZONE:        key_SetDayZone();       break;

      case bSET_PASSWORD:       key_SetPassword();      break;
      case bSET_LOGICAL:        key_SetLogical();       break;
      case bSET_PRIVATE:        key_SetPrivate();       break;

      case bSET_STARTHOU:
      case bSET_START:          key_Start();            break;
      case bSET_DEBUG:          key_Debug();            break;

      case bSET_VERSION:        key_GetVersion();       break;

      case bSET_RESETCUSTOM:
      case bSET_RESETFULL:      key_SetReset();         break;

      case bSET_MAJORDELAYS:
      case bSET_MINORDELAYS:    key_SetDelays();        break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bGET_ANALYSIS1:      key_Analysis1();        break;

      default:                  NoProgram();            break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (bProgram)
    {
      case bGET_CURRTIME:       key_SetCurrTime();      break;
      case bGET_CURRDATE:       key_SetCurrDate();      break;

      case bGET_GROUPS:         key_GetGroups();        break;

      case bGET_TRANS_ENG:
      case bGET_TRANS_CNT:
      case bGET_PULSE_HOU:
      case bGET_PULSE_MNT:
      case bGET_LOSSE:
      case bSET_LEVEL:          key_GetCanals();        break;

      case bSET_PASSWORD:       key_GetPassword();      break;
      case bSET_LOGICAL:        key_SetLogical();       break;
      case bSET_PRIVATE:        key_SetPrivate();       break;

      case bSET_VERSION:
      case bGET_VERSION:        key_GetVersion();       break;

      case bSET_MAJORDELAYS:
      case bSET_MINORDELAYS:    key_SetDelays();        break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bGET_ANALYSIS1:      key_Analysis1();        break;

      default:                  NoProgram();            break;
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;

      case bSET_GROUPS:         key_SetGroups();        break;

      case bSET_DAYZONE:        key_SetDayZone();       break;

      case bSET_PASSWORD:       key_SetPassword();      break;
      case bSET_LOGICAL:        key_SetLogical();       break;
      case bSET_PRIVATE:        key_SetPrivate();       break;

      case bSET_START:          key_Restart();          break;

      case bSET_VERSION:        key_GetVersion();       break;

      case bSET_RESETCUSTOM:
      case bSET_RESETFULL:      key_SetReset();         break;

      case bSET_MAJORDELAYS:
      case bSET_MINORDELAYS:    key_SetDelays();        break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bGET_ANALYSIS1:      key_Analysis1();        break;

      default:                  NoProgram();            break;
    }
  }
}
