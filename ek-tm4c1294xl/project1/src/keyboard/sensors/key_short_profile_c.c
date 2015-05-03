/*------------------------------------------------------------------------------
KEY_SHORT_PROFILE_C.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Размер блока  ",
                        szMessage2[]    = "   при опросе   ",
                        szMessage3[]    = "     СС-301     ",
                        szTrue[]        = " 1 получас      ",
                        szFalse[]       = " 6 получасов    ";
                        
static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



static void Show(boolean  boT)
{
  if (boT == FALSE)
    strcpy(szLo,szFalse);
  else         
    strcpy(szLo,szTrue);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetShortProfileC(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();
      
      LoadSlide(pszMessages);
      Show(boShortProfileC);
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boShortProfileC = InvertBoolean(boShortProfileC);

        SaveFile(&flShortProfileC);
        Show(boShortProfileC);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}

