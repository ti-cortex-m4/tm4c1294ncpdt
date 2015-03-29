/*------------------------------------------------------------------------------
KEY_RECALC.С

 
------------------------------------------------------------------------------*/

#include        "../../../main.h"
#include        "../../../memory/mem_schedule.h"
#include        "../../keyboard.h"
#include        "../../../display/display.h"
//#include        "../../../digitals/digitals.h"
//#include        "../../../digitals/digitals_display.h"
//#include        "../../../digitals/profile/profile_core.h"
//#include        "../../../digitals/schedule/enbl_hours.h"
//#include        "../../../digitals/schedule/schedule.h"
//#include        "../../../serial/speeds_display.h"
#include        "../../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szSetRecalc[]   = "Перерасчет      ";
                     


void    ShowRecalc(void)
{
  Clear();
  sprintf(szLo+1,"%02bu:%02bu",ibX/2,(ibX%2)*30);

  if (mpboRecalcHou[ibX] == boFalse) 
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';

  sprintf(szLo+14,"%2bu",ibX+1);
}



void    key_SetRecalc(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szSetRecalc);

      Hour();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowRecalc();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < 48)
      {
        enKeyboard = KBD_POSTENTER;
        ShowRecalc();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= 48) ibX = 0;
      ShowRecalc();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      mpboRecalcHou[ibX] = ~mpboRecalcHou[ibX];      
      ShowRecalc();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      (ibX > 0) ? (ibX--) : (ibX = 48-1);
      ShowRecalc();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep(); 
  }
  else Beep();
}

