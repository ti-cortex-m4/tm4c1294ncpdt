/*------------------------------------------------------------------------------
KEYBOARD_KEY.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "include/programs.h"
#include        "keyboard.h"
#include        "keyboard2.h"
#include        "keyboard/key_timedate.h"
#include        "keyboard/key_password.h"
#include        "keyboard/key_logical.h"
#include        "keyboard/key_private.h"
#include        "keyboard/key_start.h"
#include        "keyboard/key_version.h"
#include        "keyboard/key_decret.h"
#include        "keyboard/key_season.h"
#include        "keyboard/key_groups.h"
#include        "keyboard/tariffs/key_dayzone.h"
#include        "keyboard/tariffs/key_public_tariffs.h"
#include        "keyboard/tariffs/key_oldyearzone.h"
#include        "keyboard/tariffs/key_tariffs_mode.h"
#include        "keyboard/tariffs/key_oldprogram5.h"
#include        "keyboard/tariffs/key_relaxs_flag.h"
#include        "keyboard/tariffs/key_relaxs_tariff.h"
#include        "keyboard/tariffs/key_relaxs.h"
#include        "keyboard/key_factors.h"
#include        "keyboard/key_delays.h"
#include        "keyboard/key_reset.h"
#include        "keyboard/key_analysis.h"



void    Keyboard_Key(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    switch (bProgram)
    {
      case 0xFF:                Keyboard2Program();     break;

      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;

      case bSET_GROUPS:         key_SetGroups();        break;

      case bSET_TRANS_ENG:
      case bSET_TRANS_CNT:
      case bSET_PULSE_HOU:
      case bSET_PULSE_MNT:
      case bSET_LOSSE:
      case bSET_LEVEL:
      case bSET_COUNT:          key_SetFactors();       break;

      case bSET_DAYZONE:        key_SetDayZone();       break;
      case bSET_PUBLIC_TARIFFS: key_SetPublicTariffs(); break;
      case bSET_TARIFFS_MODE:		key_SetTariffsMode();		break;

      case bSET_PROGRAM10:
      case bSET_PROGRAM17:
      case bSET_PROGRAM20:
      case bSET_PROGRAM27:      key_SetOldYearZone();   break;

      case bSET_RELAXS_FLAG:    key_SetRelaxsFlag();    break;
      case bSET_RELAXS_TARIFF:  key_SetRelaxsTariff();  break;
      case bSET_RELAXS:         key_SetRelaxs();        break;

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
      case 0xFF:                Keyboard2Work();        break;

      case bGET_CURRTIME:       key_SetCurrTime();      break;
      case bGET_CURRDATE:       key_SetCurrDate();      break;

      case bGET_GROUPS:         key_GetGroups();        break;

      case bGET_PUBLIC_TARIFFS: key_SetPublicTariffs(); break;
      case bGET_TARIFFS_MODE:		key_SetTariffsMode();		break;

      case bGET_PROGRAM5:       key_GetOldProgram5();   break;
      case bGET_PROGRAM84:
      case bGET_PROGRAM85:      key_GetOldProgram84();  break;

      case bSET_RELAXS_FLAG:    key_SetRelaxsFlag();    break;
      case bSET_RELAXS_TARIFF:  key_SetRelaxsTariff();  break;
      case bSET_RELAXS:         key_GetRelaxs();        break;

      case bGET_TRANS_ENG:
      case bGET_TRANS_CNT:
      case bGET_PULSE_HOU:
      case bGET_PULSE_MNT:
      case bGET_LOSSE:
      case bSET_LEVEL:          key_GetFactors();       break;

//      case bGET_PROGRAM18:      key_GetProgram18();     break;
//      case bGET_PROGRAM19:      key_GetProgram19();     break;

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
      case 0xFF:                Keyboard2Reprogram();   break;

      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;

      case bSET_GROUPS:         key_SetGroups();        break;

      case bSET_DAYZONE:        key_SetDayZone();       break;
      case bSET_PUBLIC_TARIFFS: key_SetPublicTariffs(); break;
      case bSET_TARIFFS_MODE:		key_SetTariffsMode();		break;

      case bSET_PROGRAM10:
      case bSET_PROGRAM17:
      case bSET_PROGRAM20:
      case bSET_PROGRAM27:      key_SetOldYearZone();   break;

      case bSET_RELAXS_FLAG:    key_SetRelaxsFlag();    break;
      case bSET_RELAXS_TARIFF:  key_SetRelaxsTariff();  break;
      case bSET_RELAXS:         key_SetRelaxs();        break;

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
