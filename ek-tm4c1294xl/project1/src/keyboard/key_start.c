/*------------------------------------------------------------------------------
KEY_START.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_program.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../tariffs/tariffs.h"
#include        "../access.h"
#include        "../settings.h"
#include        "../groups.h"
#include        "../rtc.h"
#include        "../factors.h"



//                                         0123456789ABCDEF
static message          szStart         = "Старт           ",
                        szRestart       = "Рестарт         ",
                        szDebug         = "Отладка         ",
                        szNoOldTariff   = "Нет тарифов     ",
                        szBadRTC        = "показаний RTC ! ";


void    ShowNoOldTariff(uchar  ibMonth)
{
  ShowHi(szNoOldTariff);
  Clear();

  sprintf(szLo,"для месяца: %-2u ",ibMonth+1);
  DelayMsg();
}


bool    TestOldTariffs(void)
{
uchar  ibMonth;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    // тарифные графики совмещённые или раздельные для мощности
    if (mpcPowMonth[ibMonth] == 0)
    {
    	ShowNoOldTariff(ibMonth);
      NeedPrograms(bSET_PROGRAM10, bSET_PROGRAM17);
      return(0);
    }

    // тарифные графики раздельные для энергии
    if (mpcEngMonth[ibMonth] == 0)
    {
    	ShowNoOldTariff(ibMonth);
      NeedPrograms(bSET_PROGRAM20, bSET_PROGRAM27);
      return(0);
    }
  }

  return(1);
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

    if (TestOldTariffs() == 0)
      return;

    PGetCurrTimeDate();
    if (TrueCurrTimeDate() == 0)
    {
      ShowHi(szAlarm);
      ShowLo(szBadRTC); LongBeep(); DelayMsg();
      return;
    }

// TODO key_Start

    // рассчитываем массивы индексов тарифов для каждого получаса текущих суток (для мощности и энергии)
    MakeAllCurrTariffs();

    // рассчитываем массив К эквивалентов
    MakeFactors();

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();
    
    // запоминаем время/дату первого запуска
    tiStart = *PGetCurrTimeDate();

    DelayMsg();
    Work(); OK(); 

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
    MakeFactors();

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    DelayMsg();
    Work(); OK(); 

    LongBeep();
    enGlobal = GLB_WORK;  

//    AddSysRecord(EVE_RESTART);

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
    boSetDate = true;

    ClearPassOne();
    boSetPassword = true;

    boSetGroups = true;

// TODO key_Debug
/*
    // сбрасываем настройки по умолчанию для переменных zoAlt,zoKey
    ResetZones();

    // сбрасываем настройки по умолчанию для переменной bOldMode
    ResetTariffs();

    // новый вариант задания тарифов
    for (ibMode=0; ibMode<bMODES; ibMode++)
    {
      // для задания тарифных графиков используется переменная zoKey
      SetZonesEngMonthsMode(0,11);
      SetZonesPowMonthsMode(0,11);
    }

    // старый вариант задания тарифов
    chOldMode = '_';

    SetCharEngMonths(0,11);
    SetCharPowMonths(0,11);
*/
    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    OK();

//    if (boDTREnable == true) DTROff_All();
  }
  else Beep();
}
