/*------------------------------------------------------------------------------
KEY_EXT_4T_RESET2.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/extended_4t.h"



extern  char const                   *pszExt4TReset[];


//                                         0123456789ABCDEF
static char const       szMonths[]      = "Месяцы:         ",
                        szCanals[]      = "Каналы:         ",
                        szCanalFrom[]   = " от: __",
                        szCanalTo[]     = " до: __";



static void ShowAnswer(void)
{
  ShowBool(enKeyboard != KBD_INPUT5);
}


void    key_SetExt4TResetCustom(void)
{
static uchar ibCanMin, ibCanMax, ibMonMin, ibMonMax;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt4TFlag == TRUE)
      {
        enKeyboard = KBD_SHOW;
        Clear(); 
      
        LoadSlide(pszExt4TReset); 
        szLo[0] = '.';
      }
      else BlockProgram2(wSET_EXT4T_FLAG, 0);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibCanMin = GetCharLo(5,6) - 1;
      if (ibCanMin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibCanMax = GetCharLo(13,14) - 1;
      if ((ibCanMax < bCANALS) && (ibCanMax >= ibCanMin))
      {
        enKeyboard = KBD_INPUT3;
        ShowHi(szMonths);

        Clear(); 
        strcpy(szLo+0,szCanalFrom);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      ibMonMin = GetCharLo(5,6) - 1;
      if (ibMonMin < 12)
      {
        enKeyboard = KBD_INPUT4;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      ibMonMax = GetCharLo(13,14) - 1;
      if ((ibMonMax < 12) && (ibMonMax >= ibMonMin))
      {
        enKeyboard = KBD_INPUT5;

        LoadSlide(pszExt4TReset);

        Clear();
        ShowAnswer();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      ResetExtended4T_Custom(ibCanMin, ibCanMax, ibMonMin, ibMonMax);

      OK();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if (enKeyboard == KBD_SHOW)
      {           
        enKeyboard = KBD_INPUT1;
        fSlide = 0;

        ShowHi(szCanals);
        strcpy(szLo+0,szCanalFrom);
      }
      else
      if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
      {           
        if (enKeyboard == KBD_INPUT5)
          enKeyboard = KBD_POSTINPUT5;
        else
          enKeyboard = KBD_INPUT5;

        ShowAnswer();
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
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(13,14);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(5,6);
    }
    else
    if ((enKeyboard == KBD_INPUT4) || (enKeyboard == KBD_POSTINPUT4))
    {
      enKeyboard = KBD_POSTINPUT4;
      ShiftLo(13,14);
    }
    else Beep(); 
  }
  else Beep();
}

