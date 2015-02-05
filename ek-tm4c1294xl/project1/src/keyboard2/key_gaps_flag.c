/*------------------------------------------------------------------------------



------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../tariffs/gaps.h"




//                                         0123456789ABCDEF
static char const    szGapsFlag[] =      "Тарифные периоды";



void    key_SetGapsFlag(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      ShowHi(szGapsFlag);    
      ShowBoolean(boGapsFlag);  
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boGapsFlag = ~boGapsFlag;
        ShowBoolean(boGapsFlag);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}

