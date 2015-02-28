/*------------------------------------------------------------------------------
KEY_HEALTH.H

 
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../health.h"



//                                         0123456789ABCDEF
static char const       szHealth[]      = "Запросы         ";



void    key_GetHealth(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szHealth);
      Clear();
    }
  }
}



uchar   GetHealth(boolean  bo)
{
  switch (bo)
  {
    case TRUE:      return '+';
    case FALSE:     return '-';
    case UNDEFINED: return '?';
    default:        return '.';
  }
}



void    auto_GetHealth(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
    szLo[0]= GetHealth(boHealthLabelRTC);
	szLo[1]= GetHealth(boHealthTimeRTC);
  }
}
