/*------------------------------------------------------------------------------
KEY_CTRL_HOURS.С

 
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/digitals.h"
#include        "../../digitals/profile/profile_core.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szControl[]     = "График коррекции";



static void ShowCtrlHours(void)
{
  Clear();
  sprintf(szLo+1,"%02u:%02u", ibX/2, (ibX%2)*30);

  if (mpboCtrlHou[ibX] == FALSE)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';

  sprintf(szLo+14,"%2u",ibX+1);
}



void    key_SetCtrlHours(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szControl);

      Hour();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowCtrlHours();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < 48)
      {
        enKeyboard = KBD_POSTENTER;
        ShowCtrlHours();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= 48) 
        ibX = 0;

      ShowCtrlHours();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      mpboCtrlHou[ibX] = (mpboCtrlHou[ibX] == TRUE ? FALSE : TRUE);

      SaveFile(&flCtrlHou);

      ShowCtrlHours();
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

