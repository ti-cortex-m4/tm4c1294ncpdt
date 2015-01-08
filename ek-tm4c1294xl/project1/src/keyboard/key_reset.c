/*------------------------------------------------------------------------------
KEY_RESET.C

 Ввод и просмотр двоичных операций
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../beep.h"
#include        "../label.h"
#include        "../groups.h"


//                                         0123456789ABCDEF
static message          szResetFull     = "Полный сброс    ",
                        szResetCustom   = "Частичный сброс ";



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
          ShowAnswer();  break;
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

          BreakLabelXDATA();
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
//
//          if (ResetFlash() == 0)
//          {
//            ShowHi(szAlarm);
//            ShowLo(szBadFlash);
//            LongBeep();
//            DelayMsg();
//          }
//
//          Restart();
          break;

        case bSET_RESETFULL:  
          Waiting();
          LongBeep();
          Clear();

          BreakLabelXDATA();
//          ResetXDATA();
//          ResetKeyboard();
//          ResetDecret();
          ResetGroups();
//          ResetTariffs();
//          ResetZones();
//          ResetRelaxs();
//          ResetGaps();
//          ResetEngine();
//          ResetSpeeds();
//          ResetSendAT();
//          ResetPhones();
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
//
//          if (ResetFlash() == 0)
//          {
//            ShowHi(szAlarm);
//            ShowLo(szBadFlash);
//            LongBeep();
//            DelayMsg();
//          }
//
//          Restart();
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
