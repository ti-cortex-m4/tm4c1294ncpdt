/*------------------------------------------------------------------------------
KEY_START.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../access.h"
#include        "../settings.h"
#include        "../groups.h"
#include        "../rtc.h"
#include        "../factors.h"



//                                         0123456789ABCDEF
static message          szStart         = "Старт           ",
                        szRestart       = "Рестарт         ",
                        szDebug         = "Отладка         ";



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

// TODO

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

// TODO

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

// TODO

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    OK();

//    if (boDTREnable == true) DTROff_All();
  }
  else Beep();
}
