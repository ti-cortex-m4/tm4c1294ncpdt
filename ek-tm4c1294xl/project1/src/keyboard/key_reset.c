/*------------------------------------------------------------------------------
KEY_RESET.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../groups.h"
#include        "../tariffs/zones.h"
#include        "../tariffs/tariffs.h"
#include        "../tariffs/relaxs.h"
#include        "../tariffs/gaps.h"
#include        "../digitals/digitals.h"
#include        "../digitals/profile_core.h"
#include        "../digitals/phones.h"
#include        "../digitals/digitals_run.h"
#include        "../digitals/digitals_run.h"
#include        "../serial/speeds.h"
#include        "../output/unified/uni.h"
#include        "../engine.h"
#include        "../factors.h"
#include        "../settings.h"
#include        "../hardware/memory.h"
#include        "../storage/storage.h"



//                                         0123456789ABCDEF
static char const       szResetFull[]   = "Полный сброс    ",
                        szResetCustom[] = "Частичный сброс ";



void    key_SetReset(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      switch (bProgram)
      { 
        case bSET_RESETCUSTOM:  
          ShowHi(szResetCustom);    
          ShowAnswer();  break;

        case bSET_RESETFULL:  
          ShowHi(szResetFull);    
          ShowAnswer();
          break;
      }                 
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      switch (bProgram)
      {
        case bSET_RESETCUSTOM:
          Waiting();
          LongBeep();
          Clear();

          ResetSettings(false);
//          ResetCustom();
//
//          ResetLimits();
//          ResetDecret();
//          ResetGaps();
//          ResetExtended3();
//          ResetExtended4();
//          ResetExtended4T();
//          ResetExtended6();
//          ResetCorrect2();
//          ResetCorrect3();
//          ResetDevices();
//          ResetLimitsAux_All();
//          ResetCurrent2();
//          ResetCheckupCustom();

          if (ResetFlash() == FALSE)
          {
            ShowHi(szAlarm);
            ShowLo(szBadFlash);
            LongBeep();
            DelayMsg();
          }

          Restart();
          break;

        case bSET_RESETFULL:  
          Waiting();
          LongBeep();
          Clear();

          ResetSettings(true);
//          ResetXDATA();
//          ResetKeyboard();
//          ResetDecret();
          ResetGroups();
          ResetFactors();
          ResetZones();
          ResetTariffs();
          ResetRelaxs();
          ResetGaps();
          ResetDigitals();
          ResetPhones();
          ResetProfile();
          ResetSpeeds();
          ResetUni();
//          ResetCurrent();
//          ResetProfiles();
          ResetDevices();
//          ResetSendAT();
//          ResetPhones2();
//          ResetParams();
//          ResetGPS();
//          ResetSMK();
//          ResetExtended3();
//          ResetExtended4();
//          ResetExtended4T();
//          ResetExtended6();
//          ResetCorrect2();
//          ResetCorrect3();
//          ResetDevices();
//          ResetLimitsAux_All();
//          ResetCurrent2();
//          ResetBulk();
//          ResetRecordDisable();
//          ResetUni();
//          ResetCheckupFull();
//
//          ResetLimits();

          if (ResetFlash() == FALSE)
          {
            ShowHi(szAlarm);
            ShowLo(szBadFlash);
            LongBeep();
            DelayMsg();
          }

          Restart();
          break;
      }
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        switch (bProgram)
        {                        
          case bSET_RESETCUSTOM:   
          case bSET_RESETFULL:
            if (enKeyboard == KBD_INPUT1)
              enKeyboard = KBD_POSTINPUT1;
            else
              enKeyboard = KBD_INPUT1;
            ShowAnswer();  break;
        }
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
