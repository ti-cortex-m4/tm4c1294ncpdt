/*------------------------------------------------------------------------------
key_profile2mode_can.c


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "key_profile2mode.h"
#include "key_profile2mode_can.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Размер блока  ",
                        szMessage2[]    = "   при опросе   ",
                        szMessage3[]    = "  Меркурий-230  ",
                        szMessage4[]    = "   по каналам   ",
                        szBlocked[]     = "Запрещено:      ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



static void Show(uchar  c)
{
  Clear();
  sprintf(szLo+14,"%2u",c+1);

  ShowProfile2Mode(enProfile2ModeCan[c]);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}


void    key_SetProfile2ModeCan(void)
{
static uchar c;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (enProfile2Mode == P2M_BY_DIGITAL)
      {
        enKeyboard = KBD_INPUT1;
        LoadSlide(pszMessages);

        Canal();
      }
      else
      {
        ShowHi(szBlocked);
        Clear();
        sprintf(szLo+1,"программой %u",wSET_PROFILE_2_MODE);
      }
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      c = 0;
      Show(c);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show(c);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;

      Show(c);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      enProfile2ModeCan[c] = NextProfile2Mode(enProfile2ModeCan[c]);

      SaveCache(&chProfile2ModeCan);

      Show(c);
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
