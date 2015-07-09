/*------------------------------------------------------------------------------
KEY_START.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_program.h"
#include "../memory/mem_tariffs.h"
#include "keyboard.h"
#include "../display/display.h"
#include "../tariffs/tariffs.h"
#include "../access.h"
#include "../label.h"
#include "../settings.h"
#include "../groups.h"
#include "../realtime/realtime_start.h"
#include "../impulses/impulses.h"
#include "../digitals/digitals.h"
#include "../special/defects.h"
#include "../time/rtc.h"
#include "../impulses/factors.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "../nvram/cache.h"
#include "../serial/speeds_display.h"



//                                         0123456789ABCDEF
static char const       szStart[]       = "Старт           ",
                        szRestart[]     = "Рестарт         ",
                        szDebug[]       = "Отладка         ",
                        szNoTariffs[]   = "Нет тарифов     ",
                        szBadRTC[]      = "показаний RTC ! ";


void    ShowNoTariffs(uchar  ibMonth)
{
  ShowHi(szNoTariffs);
  Clear();

  sprintf(szLo,"для месяца: %-2u ",ibMonth+1);
  DelayMsg();
}


bool    TestTariffs(void)
{
uchar  ibMonth;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    // тарифные графики совмещённые или раздельные для мощности
    if (mpePeriodTrfPow[ibMonth] == NONE)
    {
    	ShowNoTariffs(ibMonth);
      NeedPrograms(bSET_PROGRAM10, bSET_PROGRAM17);
      return(0);
    }

    // тарифные графики раздельные для энергии
    if (mpePeriodTrfEng[ibMonth] == NONE)
    {
    	ShowNoTariffs(ibMonth);
      NeedPrograms(bSET_PROGRAM20, bSET_PROGRAM27);
      return(0);
    }
  }

  return(1);
}


bool    TestDigitals()
{
uchar   c;

  for (c=0; c<bCANALS; c++)
  {
    if (GetDigitalDevice(c) != 0)
    {
      if (StreamPortCan(GetDigitalPort(c),c) == 0) return 0;
    }
  }

  return 1;
}



void    key_Start(void)
{
  if (enKeyboard == KBD_ENTER)
  {  
    enKeyboard = KBD_BEGIN; 

    ShowHi(szStart);     
    Clear();


    if (boSetTime == false)
    {
      NeedProgram(bSET_CURRTIME);
      return;
    }
    else if (boSetDate == false)
    {
      NeedProgram(bSET_CURRDATE);
      return;
    }
    else if (boSetGroups == false)
    {
      NeedProgram(bSET_GROUPS);
      return;
    }
    else if (boSetPassword == false)
    {
      NeedProgram(bSET_PASSWORD);
      return;
    }

    if (TestTariffs() == 0)
      return;

    if (TrueCurrTimeDate(*GetCurrTimeDate()) == false)
    {
      ShowHi(szAlarm);
      ShowLo(szBadRTC); LongBeep(); DelayMsg();
      return;
    }

    if (TestDigitals() == 0)
      return;

// TODO key_Start

    // рассчитываем массивы индексов тарифов для каждого получаса текущих суток (для мощности и энергии)
    MakeAllCurrTariffs();

    StartFactors();
    StartRealtime();
    StartImpulses();

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    StartDefects();

    // запоминаем время/дату первого запуска
    tiStart = *GetCurrTimeDate();

    Work();
    OK();

    Beep();

    SetLabelGlobal();
    enGlobal = GLB_WORK;

    AddSysRecord(EVE_START);

//    if (boDTREnable == true) DTROff_All();
  }
  else Beep();
}



// запускает прибор после перепрограммирования
void    key_Restart(void)
{
  if (enKeyboard == KBD_ENTER)
  {  
    enKeyboard = KBD_BEGIN; 

    ShowHi(szRestart);     
    Clear();    

    if (boSetPassword == false)
    {
      NeedProgram(bSET_PASSWORD);
      return;
    }

// TODO key_Restart

    // рассчитываем массивы индексов тарифов для каждого получаса текущих суток (для мощности и энергии)
    MakeAllCurrTariffs();

    // рассчитываем массив К эквивалентов
    StartFactors();

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    Work();
    OK();

    Beep();

    enGlobal = GLB_WORK;  

    AddSysRecord(EVE_RESTART);

//    if (boDTREnable == true) DTROff_All();
  }
  else Beep();
}



// устанавливает настройки по умолчанию
void    key_Debug(void)
{
  if (enKeyboard == KBD_ENTER)
  {  
    enKeyboard = KBD_BEGIN; 

    ShowHi(szDebug);     
    Clear();

    boSetTime = true;
    SaveCache(&chSetTime);

    boSetDate = true;
    SaveCache(&chSetDate);

    boSetGroups = true;
    SaveCache(&chSetGroups);

    ClearPassOne();
    boSetPassword = true;
    SaveCache(&chSetPassword);

// TODO key_Debug

    // сбрасываем настройки по умолчанию для переменных zoAlt,zoKey
//    ResetZones();

    // сбрасываем настройки по умолчанию для
    ResetTariffs();

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    OK();

//    if (boDTREnable == true) DTROff_All();
  }
  else Beep();
}
