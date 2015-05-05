/*------------------------------------------------------------------------------
KEY_RESET.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "keyboard.h"
#include "../display/display.h"
#include "../groups.h"
#include "../tariffs/zones.h"
#include "../tariffs/tariffs.h"
#include "../tariffs/relaxs.h"
#include "../tariffs/gaps.h"
#include "../digitals/digitals.h"
#include "../digitals/params/params.h"
#include "../digitals/profile/profile_core.h"
#include "../digitals/phones.h"
#include "../devices/devices_init.h"
#include "../serial/speeds.h"
#include "../serial/flow.h"
#include "../output/unified/uni.h"
#include "../engine.h"
#include "../factors.h"
#include "../settings.h"
#include "../hardware/memory.h"
#include "../storage/storage.h"
#include "../time/decret.h"



//                                         0123456789ABCDEF
static char const       szResetFull[]   = "������ �����    ",
                        szResetCustom[] = "��������� ����� ";



void    key_SetReset(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      switch (wProgram)
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
      switch (wProgram)
      {
        case bSET_RESETCUSTOM:
          Waiting();
          LongBeep();
          Clear();

          ResetSettings(false);
//          ResetCustom();
//
//          ResetLimits();
          ResetDecret();
//          ResetGaps();
//          ResetExtended3();
//          ResetExtended4();
//          ResetExtended4T();
//          ResetExtended6();
//          ResetCorrect2();
//          ResetCorrect3();
          ResetDevices();
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
          ResetDecret();
          ResetGroups();
          ResetFactors();
          ResetZones();
          ResetTariffs();
          ResetRelaxs();
          ResetGaps();
          ResetDigitals();
          ResetParams();
          ResetPhones();
          ResetProfile();
          ResetSpeeds();
          ResetUni();
          ResetFlow();
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
//          ResetCurrent2();
//          ResetBulk();
//          ResetRecordDisable();
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
        switch (wProgram)
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
