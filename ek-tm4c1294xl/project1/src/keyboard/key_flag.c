/*------------------------------------------------------------------------------
KEY_FLAG.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../flash/files.h"
#include        "key_flag.h"



void    key_SetFlag(file const  *pflFile, char const  *pszSlide[])
{
  boolean *pboVal = (boolean *) pflFile->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszSlide);
      ShowBoolean(*pboVal);
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        *pboVal = InvertBoolean(*pboVal);
        SaveFile(pflFile);

        ShowBoolean(*pboVal);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
