/*------------------------------------------------------------------------------
KEY_EXT_4_CANALS!C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../digitals/extended/extended_4.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "     Каналы     ",
                        szMessage2[]    = "  для загрузки  ",
                        szMessage3[]    = "знач. счетчиков ",
                        szMessage4[]    = "   на начало    ",
                        szMessage5[]    = "   месяцев ?    ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



static void Show(void)
{
  Clear();
  sprintf(szLo+14,"%2u",ibX+1);

  if (mpfExt4EnblCan[ibX] == false)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetExt4EnblCan(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (fExt4Flag == true)
      {
        enKeyboard = KBD_INPUT1;
        LoadSlide(pszMessages);

        Canal();
      }
      else BlockProgram(bSET_EXT4_FLAG);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      Show();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if (enKeyboard == KBD_POSTENTER)
      {
        mpfExt4EnblCan[ibX] = InvertBool(mpfExt4EnblCan[ibX]);

        SaveFile(&flExt4EnblCan);
        Show();
      }
      else Beep();
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
