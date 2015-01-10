/*------------------------------------------------------------------------------
KEY_START.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_settings.h"
#include        "../mem_program.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../label.h"
#include        "../delay.h"
#include        "../beep.h"
#include        "../access.h"
#include        "../groups.h"
#include        "../rtc.h"



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


    if (boSetTime == boFalse)
    {
      NeedProgram(bSET_CURRTIME);
      return;
    }
    else if (boSetDate == boFalse)
    {
      NeedProgram(bSET_CURRDATE);
      return;
    }
    else if (boSetGroups == boFalse)
    {
      NeedProgram(bSET_GROUPS);
      return;
    }
    else if (boSetPassword == boFalse)
    {
      NeedProgram(bSET_PASSWORD);
      return;
    }

// TODO

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    // устанавливаем метку режима 'Функционирование'
    SetLabel();
    
    // запоминаем время/дату первого запуска
    tiStart = *PGetCurrTimeDate();

    DelayMsg();
    Work(); OK(); 

    LongBeep();
    enGlobal = GLB_WORK;  

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

    if (boSetPassword == boFalse)
    {
      NeedProgram(bSET_PASSWORD);
      return;
    }

// TODO

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    DelayMsg();
    Work(); OK(); 

    LongBeep();
    enGlobal = GLB_WORK;  

//    AddSysRecord(EVE_RESTART);

//    if (boDTREnable == boTrue) DTROff_All();
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

    boSetTime = boTrue;
    boSetDate = boTrue;

    ClearPassOne();
    boSetPassword = boTrue;

    boSetGroups = boTrue;

// TODO

    // устанавливаем признаки используемых каналов и групп
    MakeUsedNodes();

    OK();

//    if (boDTREnable == boTrue) DTROff_All();
  }
  else Beep();
}
