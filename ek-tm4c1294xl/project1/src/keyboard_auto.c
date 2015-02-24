/*------------------------------------------------------------------------------
KEYBOARD_AUTO.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "include/programs.h"
#include        "keyboard.h"
#include        "keyboard/key_timedate.h"
#include        "keyboard/key_analysis.h"
#include        "keyboard/key_health.h"
#include        "keyboard/key_single.h"
#include        "keyboard/key_single2.h"
#include        "digitals/digitals.h"
#include        "impulses/impulses.h"



void    Keyboard_Auto(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bGET_ANALYSIS1:      auto_GetAnalysis1();    break;
      case bGET_HEALTH:         auto_GetHealth();       break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (bProgram)
    {
      case bGET_CURRTIME:       auto_GetCurrTime();     break;
      case bGET_CURRDATE:       auto_GetCurrDate();     break;

      case bGET_ANALYSIS1:      auto_GetAnalysis1();    break;
      case bGET_HEALTH:         auto_GetHealth();       break;
    }

    // обновление показаний с каждым импульсом
    if (fOnImpulse == 1)
    {
      fOnImpulse = 0;
      switch (bProgram)
      {
        case bGET_CNTCURR_10:
        case bGET_CNTCURR_110:      if (GetDigitalDevice(ibX) == 0)
                                    auto_GetSingle();   break;

        case bGET_IMPCANCURRMNT:    auto_GetSingle();   break;
      }
    }

    // обновление показаний с частотой 1 √ц
    if (fOnSecond == 1)
    {
      fOnSecond = 0;
      switch (bProgram)
      {
        case bGET_POWGRPPREVHOU:
        case bGET_POWGRPCURRHOU:

        case bGET_POWGRPCURRMNT:    auto_GetSingle();   break;

        case bGET_POWCANPREVHOU:
        case bGET_POWCANCURRHOU:

        case bGET_POWCANCURRMNT:    auto_GetSingle2();  break;

//        case bGET_PROGRAM73:    auto_GetOldProgram73(); break;
//        case bGET_PROGRAM74:    auto_GetOldProgram74(); break;
      }
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bGET_ANALYSIS1:      auto_GetAnalysis1();    break;
      case bGET_HEALTH:         auto_GetHealth();       break;
    }
  }
}
