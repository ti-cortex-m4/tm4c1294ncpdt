/*------------------------------------------------------------------------------
KEY_FLAG.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "key_flag.h"



static void ShowFlag(boolean const  bo, char const  szTrue[], char const  szFalse[])
{
  if (bo == TRUE)
    strcpy(szLo+1, (char *)szTrue);
  else
    strcpy(szLo+1, (char *)szFalse);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}



void    key_SetFlag(file const  *pflFile, char const  *pszMessages[], char const  szTrue[], char const  szFalse[])
{
  boolean *pboValue = (boolean *) pflFile->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszMessages);
      ShowFlag(*pboValue, szTrue, szFalse);
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        *pboValue = InvertBoolean(*pboValue);
        SaveFile(pflFile);

        ShowFlag(*pboValue, szTrue, szFalse);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
