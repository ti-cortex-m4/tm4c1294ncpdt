/*------------------------------------------------------------------------------
_EXTENDED_0_COUNTER.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_extended_0.h"
#include "../../digitals/extended/extended_0.h"



//                                          0123456789ABCDEF
static char const       szExt0Counter1[] = " Число повторов ",
                        szExt0Counter2[] = "  при проверке  ",
                        szExt0Counter3[] = " качества связи ",
                        szExt0Counter4[] = "   (1 .. 50)    ";

static char const      *pszExt0Counter[] = { szExt0Counter1, szExt0Counter2, szExt0Counter3, szExt0Counter4, "" };



static void Show(void)
{
  Clear();
  sprintf(szLo+4,"%2bu из %-2bu", bExt0Limit, bExt0Counter);
}


void    key_SetExt0Counter(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (fExt0Flag == true)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadSlide(pszExt0Counter); 
        Show(); 
      }
      else BlockProgram2(wSET_EXT0_FLAG, 0);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibX = GetCharLo(4,5);
      if ((ibX != 0) && (ibX <= 50))
      {
        enKeyboard = KBD_INPUT2;
        szLo[10] = '_';
        szLo[11] = '_';
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        szLo[4] = '_';
        szLo[5] = '_';
      }
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      enKeyboard = KBD_POSTENTER;

      ibY = GetCharLo(10,11);
      if ((ibY != 0) && (ibY <= 50) && (ibX <= ibY))
      {
        bExt0Limit = ibX;
        bExt0Counter = ibY;

        Show();
      }
      else 
      {
        enKeyboard = KBD_INPUT2;
        LongBeep();

        szLo[10] = '_';
        szLo[11] = '_';
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;

      Clear();
      szLo[4] = '_';
      szLo[5] = '_';
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(4,5);
    }
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,11);
    }
  }
  else Beep();
}

