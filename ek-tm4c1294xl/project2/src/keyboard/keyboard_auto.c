/*------------------------------------------------------------------------------
KEYBOARD_AUTO.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/programs.h"
#include "keyboard.h"
#include "time/key_timedate.h"



void    Keyboard_Auto(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    switch (wProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (wProgram)
    {
      case bGET_CORRECT_TIME:
      case bGET_CURRTIME:       auto_GetCurrTime();     break;
      case bGET_CURRDATE:       auto_GetCurrDate();     break;
    }

    // обновление показаний с каждым импульсом
    if (fOnImpulse == 1)
    {
      fOnImpulse = 0;
    }

    // обновление показаний с частотой 1 √ц
    if (fOnSecond == 1)
    {
      fOnSecond = 0;
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (wProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;
    }
  }
}
