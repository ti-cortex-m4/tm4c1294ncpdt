/*------------------------------------------------------------------------------
_CORRECT30.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_correct3.h"
#include "../../time/gps.h"
#include "../../time/correct3.h"



//                                         0123456789ABCDEF
static char const       szTaking30[]    = "Учет работы GPS ",
                        szCorrect30[]   = " при коррекции  ",
                        szTime30[]      = "   времени ?    ";

                        
static char const      *pszCorrect30[]  = { szTaking30, szCorrect30, szTime30, "" };



void    key_SetCorrect30(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      if (UseGps())
      {
        enKeyboard = KBD_INPUT1;
        Clear();
      
        LoadSlide(pszCorrect30);    
        ShowBool(boCorrect3);
      }
      else BlockProgram(bSET_GPS_CONFIG);
    } 
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        boCorrect3 = ~boCorrect3;
        ShowBool(boCorrect3);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}

