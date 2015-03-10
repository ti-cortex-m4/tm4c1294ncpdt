/*------------------------------------------------------------------------------
KEY_START.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_program.h"
#include        "../memory/mem_tariffs.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../tariffs/tariffs.h"
#include        "../access.h"
#include        "../settings.h"
#include        "../groups.h"
#include        "../realtime/realtime_start.h"
#include        "../impulses/impulses.h"
#include        "../digitals/digitals.h"
#include        "../time/rtc.h"
#include        "../factors.h"
#include        "../flash/records.h"
#include        "../serial/speeds2.h"



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
    if (mpeTariffPow[ibMonth] == NONE)
    {
    	ShowNoTariffs(ibMonth);
      NeedPrograms(bSET_PROGRAM10, bSET_PROGRAM17);
      return(0);
    }

    // тарифные графики раздельные для энергии
    if (mpeTariffEng[ibMonth] == NONE)
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

    if (TrueCurrTimeDate(GetCurrTimeDate()) == false)
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

    // запоминаем время/дату первого запуска
    tiStart = *GetCurrTimeDate();

    Delay(1000);
    Work();
    OK();

    LongBeep();

    enGlobal = GLB_WORK;  
    SaveGlobal();

//    AddSysRecord(EVE_START);
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

    Delay(1000);
    Work();
    OK();

    LongBeep();
    enGlobal = GLB_WORK;  

    AddSysRecord(EVE_RESTART);
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

    boSetTime = TRUE;
    boSetDate = TRUE;

    ClearPassOne();
    boSetPassword = TRUE;

    boSetGroups = TRUE;

// TODO key_Debug

    // сбрасываем настройки по умолчанию для переменных zoAlt,zoKey
//    ResetZones();

    // сбрасываем настройки по умолчанию для
    ResetTariffs();

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    OK();
  }
  else Beep();
}
