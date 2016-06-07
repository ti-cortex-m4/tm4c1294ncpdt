/*------------------------------------------------------------------------------
key_review_can.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "key_review_can.h"



//                                         0123456789ABCDEF
//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   Каналы на    ",
                        szMessage2[]    = "  проверку при  ",
                        szMessage3[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



static void Show(uchar  c)
{
  Clear();
  sprintf(szLo+14,"%2u",c+1);

  if (mfReviewCan[c] == false)
    strcpy(szLo+8,szNo);
  else
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetReviewCan(void)
{
static uchar c;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (fReviewFlag == true)
      {
        enKeyboard = KBD_INPUT1;
        LoadSlide(pszMessages);

        Canal();
      }
      else BlockProgram(wSET_REVIEW_FLAG);
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
      mfReviewCan[c] = InvertBool(mfReviewCan[c]);

      SaveCache(&chReviewCan);
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
