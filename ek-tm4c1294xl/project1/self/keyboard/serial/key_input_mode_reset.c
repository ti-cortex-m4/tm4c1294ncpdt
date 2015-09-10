/*------------------------------------------------------------------------------
KEY_INPUT_MODE_RESET.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"



//                                         0123456789ABCDEF
message         code    szInputModeReset1    = " Автоматическое ",
                        szInputModeReset2    = "  переключение  ",
                        szInputModeReset3    = "на прием ведомых",
                        szInputModeReset4    = "   портов 3,4   ";
                        
uchar           *code   pszInputModeReset[]  = { szInputModeReset1, szInputModeReset2, szInputModeReset3, szInputModeReset4, "" };



void    key_SetInputModeReset(void)
{
  Clear();
  switch (bInputModeReset)
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


void    key_SetInputModeReset(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_POSTENTER;
      Clear();
      
      LoadSlide(pszInputModeReset);    
      ShowInputModeReset();  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if (enKeyboard == KBD_POSTENTER)
      {           
        switch (bInputModeReset)
        {
          case 0:  bInputModeReset = 1;  break;
          case 1:  bInputModeReset = 6;  break;
          case 6:  bInputModeReset = 12; break;
          case 12: bInputModeReset = 24; break;
          case 24: bInputModeReset = 48; break;
          case 48: bInputModeReset = 0;  break;
          default: bInputModeReset = 0;  break;
        }
        
        SaveCache(&chInputModeReset);

        ShowInputModeReset();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
*/
