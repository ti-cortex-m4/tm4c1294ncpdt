/*------------------------------------------------------------------------------
key_profile2mode.c


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "key_profile2mode.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  –азмер блока  ",
                        szMessage2[]    = "   при опросе   ",
                        szMessage3[]    = "  ћеркурий-230  ",
                        szAutomatic[]   = " автоматически  ",
                        szSize1[]       = " 1 получас      ",
                        szSize16[]      = " 16 получасов   ",
                        szSize17[]      = " 17 получасов   ",
                        szByDigital[]   = " по каналам     ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



// TODO switch
void    ShowProfile2Mode(profile2mode p2m)
{
  if (p2m == P2M_SIZE_1)
    strcpy(szLo, szSize1);
  else if (p2m == P2M_SIZE_16)
    strcpy(szLo, szSize16);
  else if (p2m == P2M_SIZE_17)
    strcpy(szLo, szSize17);
  else if (p2m == P2M_BY_DIGITAL)
    strcpy(szLo, szByDigital);
  else
    strcpy(szLo, szAutomatic);
}


profile2mode NextProfile2Mode(profile2mode p2m) {
  if (p2m == P2M_SIZE_1)
    return P2M_SIZE_16;
  else if (p2m == P2M_SIZE_16)
    return P2M_SIZE_17;
  else if (p2m == P2M_SIZE_17)
    return P2M_BY_DIGITAL;
  else
    return P2M_AUTOMATIC;
}



static void Show(void)
{
  ShowProfile2Mode(enProfile2Mode);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetProfile2Mode(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszMessages);
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        enProfile2Mode = NextProfile2Mode(enProfile2Mode);

        SaveCache(&chProfile2Mode);

        Show();
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
