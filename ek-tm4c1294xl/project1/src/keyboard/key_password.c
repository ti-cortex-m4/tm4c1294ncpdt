/*------------------------------------------------------------------------------
KEY_PASSWORD.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../beep.h"
#include        "../access.h"



//                                         0123456789ABCDEF
static char const       szPassword[]    = "Пароль          ",
                        szMaskPass[]    = "   ----------   ";
                        


void    key_SetPassword(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
  
      ShowHi(szPassword);
      ShowLo(szMaskPass);

      szLo[15] = '1';
      ClearPassOne();
      ibX = 3;

      boSetPassword = FALSE;
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_INPUT2;

      ShowLo(szMaskPass);

      szLo[15] = '2';
      ClearPassTwo();
      ibX = 3;
    }
    else if (enKeyboard == KBD_INPUT2)
    {
      if (memcmp(mpbPassOne, mpbPassTwo, 10) == 0)
      {
        enKeyboard = KBD_BEGIN;
        OK();

        boSetPassword = TRUE;
      }
      else 
      {
        enKeyboard = KBD_ENTER;
        LongBeep();

        Error();
      }
    }
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_INPUT1)
    {
      if (ibX < 13)
      {
        mpbPassOne[ibX-3] = bKey;
        szLo[ibX++] = '*';
      }
    }
    else 
    if (enKeyboard == KBD_INPUT2)
    {
      if (ibX < 13)
      {
        mpbPassTwo[ibX-3] = bKey;
        szLo[ibX++] = '*';
      }
    }
  }
}




void    key_GetPassword(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT2;

      ShowHi(szPassword);
      ShowLo(szMaskPass);

      ClearPassTwo();
      ibX = 3;
    }
    else if (enKeyboard == KBD_INPUT2)
    { 
      if ((memcmp(mpbPassOne, mpbPassTwo, 10) == 0) || SuperUser())
      {       
        enKeyboard = KBD_BEGIN;
        OK();

        boSetPassword = TRUE;

        enGlobal = GLB_REPROGRAM;
        Setting();

//        AddSysRecord(EVE_PASSWORD);
      }
      else 
      {
        enKeyboard = KBD_ENTER;
        LongBeep();

        Error();
      }
    }
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_INPUT2)
    {
      if (ibX < 13)
      {
        mpbPassTwo[ibX-3] = bKey;
        szLo[ibX++] = '*';
      }
    }
  }
  else Beep();
}




