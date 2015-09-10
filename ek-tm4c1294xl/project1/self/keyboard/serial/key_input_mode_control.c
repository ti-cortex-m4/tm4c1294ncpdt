/*------------------------------------------------------------------------------
KEY_INPUT_MODE_CONTROL.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"



//                                         0123456789ABCDEF
message         code    szIOControl1    = " Автоматическое ",
                        szIOControl2    = "  переключение  ",
                        szIOControl3    = "на прием ведомых",
                        szIOControl4    = "   портов 3,4   ";
                        
uchar           *code   pszIOControl[]  = { szIOControl1, szIOControl2, szIOControl3, szIOControl4, "" };



void    key_SetInputModeReset(void)
{
  Clear();
  switch (bIOControl)
  {
    case 0:  strcpy(szLo+1,"нет");      break;
    case 1:  strcpy(szLo+1,"30 минут"); break;
    case 6:  strcpy(szLo+1,"3 часа");   break;
    case 12: strcpy(szLo+1,"6 часов");  break;
    case 24: strcpy(szLo+1,"12 часов"); break;
    case 48: strcpy(szLo+1,"24 часа");  break;
    default: strcpy(szLo+1,"?");        break;
  }

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetIOControl(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_POSTENTER;
      Clear();
      
      LoadSlide(pszIOControl);    
      ShowIOControl();  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if (enKeyboard == KBD_POSTENTER)
      {           
        switch (bIOControl)
        {
          case 0:  bIOControl = 1;  break;
          case 1:  bIOControl = 6;  break;
          case 6:  bIOControl = 12; break;
          case 12: bIOControl = 24; break;
          case 24: bIOControl = 48; break;
          case 48: bIOControl = 0;  break;
          default: bIOControl = 0;  break;
        }
        
        ShowIOControl();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
*/
