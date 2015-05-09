/*------------------------------------------------------------------------------
KEY_CORRECT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_correct1.h"
#include "../../console.h"
#include "../../time/correct1.h"



//                                         0123456789ABCDEF
static char const       szCorrect[]     = " оррекци€ секунд",
                        szCurrMonth[]   = "за текущий мес€ц",
                        szPrevMonth[]   = "за прошлый мес€ц",
                        szCorrTotal[]   = "      всего     ",
                        szCorrGPS[]     = "   с часов GPS  ",
                        szCorrKey[]     = "  с клавиатуры  ",
                        szCorrCRC[]     = " по системе CRC ",
                        szCorrEscK_hi[] = "по запросу Esc K",
                        szCorrEscK_lo[] = "по системе Esc k",
                        szCorrSMK[]     = "   с —»ћЁ -48   ";

static char const       *pszGetCorrectCurr[] = { szCorrect, szCurrMonth, "" },
                        *pszGetCorrectPrev[] = { szCorrect, szPrevMonth, "" };



// вывод статистики коррекции секунд за текущий мес€ц
void    ShowCorrectCurr1(void)
{
  uint iwAmax, iwAmin;

  switch (ibX)
  {
    case 0: ShowLo(szCorrTotal);   iwAmax = mpcwPosValueCurr[0]; iwAmin = mpcwNegValueCurr[0]; break;
    case 1: ShowLo(szCorrGPS);     iwAmax = mpcwPosValueCurr[1]; iwAmin = mpcwNegValueCurr[1]; break;
    case 2: ShowLo(szCorrKey);     iwAmax = mpcwPosValueCurr[2]; iwAmin = mpcwNegValueCurr[2]; break;
    case 3: ShowLo(szCorrCRC);     iwAmax = mpcwPosValueCurr[3]; iwAmin = mpcwNegValueCurr[3]; break;
    case 4: ShowLo(szCorrEscK_hi); iwAmax = mpcwPosValueCurr[4]; iwAmin = mpcwNegValueCurr[4]; break;
    case 5: ShowLo(szCorrEscK_lo); iwAmax = mpcwPosValueCurr[5]; iwAmin = mpcwNegValueCurr[5]; break;

    case 6: ShowLo(szCorrSMK);     iwAmax = mpcwPosValueCurr[9]; iwAmin = mpcwNegValueCurr[9]; break;
  }

  Delay(1000); Clear();
  sprintf(szLo+1,"+%02u.%02u  -%02u.%02u",
                 (uchar)(iwAmax / 60),
                 (uchar)(iwAmax % 60),
                 (uchar)(iwAmin / 60),
                 (uchar)(iwAmin % 60));
}


// вывод статистики коррекции секунд за текущий мес€ц
void    ShowCorrectCurr2(void)
{
  uint iwAmax, iwAmin;

  switch (ibX)
  {
    case 0: iwAmax = mpcwPosCountCurr[0]; iwAmin = mpcwNegCountCurr[0]; break;
    case 1: iwAmax = mpcwPosCountCurr[1]; iwAmin = mpcwNegCountCurr[1]; break;
    case 2: iwAmax = mpcwPosCountCurr[2]; iwAmin = mpcwNegCountCurr[2]; break;
    case 3: iwAmax = mpcwPosCountCurr[3]; iwAmin = mpcwNegCountCurr[3]; break;
    case 4: iwAmax = mpcwPosCountCurr[4]; iwAmin = mpcwNegCountCurr[4]; break;
    case 5: iwAmax = mpcwPosCountCurr[5]; iwAmin = mpcwNegCountCurr[5]; break;

    case 6: iwAmax = mpcwPosCountCurr[9]; iwAmin = mpcwNegCountCurr[9]; break;
  }

  Clear(); sprintf(szLo+3,"%5u  %-5u",iwAmax,iwAmin);
  Delay(1000);
  ShowCorrectCurr1();
}


// просмотр статистики коррекции секунд за текущий мес€ц
void    key_GetCorrectCurr(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      LoadSlide(pszGetCorrectCurr);
      Clear();

      ibX = 0;
      ShowCorrectCurr1();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX > 6) ibX = 0;
      ShowCorrectCurr1();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) ibX--; else ibX = 6;
      ShowCorrectCurr1();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
      ShowCorrectCurr2();
    else
      Beep();
  }
  else Beep();
}



// вывод статистики коррекции секунд за предыдущий мес€ц
void    ShowCorrectPrev1(void)
{
  uint iwAmax, iwAmin;

  switch (ibX)
  {
    case 0: ShowLo(szCorrTotal);   iwAmax = mpcwPosValuePrev[0]; iwAmin = mpcwNegValuePrev[0]; break;
    case 1: ShowLo(szCorrGPS);     iwAmax = mpcwPosValuePrev[1]; iwAmin = mpcwNegValuePrev[1]; break;
    case 2: ShowLo(szCorrKey);     iwAmax = mpcwPosValuePrev[2]; iwAmin = mpcwNegValuePrev[2]; break;
    case 3: ShowLo(szCorrCRC);     iwAmax = mpcwPosValuePrev[3]; iwAmin = mpcwNegValuePrev[3]; break;
    case 4: ShowLo(szCorrEscK_hi); iwAmax = mpcwPosValuePrev[4]; iwAmin = mpcwNegValuePrev[4]; break;
    case 5: ShowLo(szCorrEscK_lo); iwAmax = mpcwPosValuePrev[5]; iwAmin = mpcwNegValuePrev[5]; break;

    case 6: ShowLo(szCorrSMK);     iwAmax = mpcwPosValuePrev[9]; iwAmin = mpcwNegValuePrev[9]; break;
  }

  Delay(1000); Clear();
  sprintf(szLo+1,"+%02u.%02u  -%02u.%02u",
                 (uchar)(iwAmax / 60),
                 (uchar)(iwAmax % 60),
                 (uchar)(iwAmin / 60),
                 (uchar)(iwAmin % 60));
}


// вывод статистики коррекции секунд за предыдущий мес€ц
void    ShowCorrectPrev2(void)
{
  uint iwAmax, iwAmin;

  switch (ibX)
  {
    case 0: iwAmax = mpcwPosCountPrev[0]; iwAmin = mpcwNegCountPrev[0]; break;
    case 1: iwAmax = mpcwPosCountPrev[1]; iwAmin = mpcwNegCountPrev[1]; break;
    case 2: iwAmax = mpcwPosCountPrev[2]; iwAmin = mpcwNegCountPrev[2]; break;
    case 3: iwAmax = mpcwPosCountPrev[3]; iwAmin = mpcwNegCountPrev[3]; break;
    case 4: iwAmax = mpcwPosCountPrev[4]; iwAmin = mpcwNegCountPrev[4]; break;
    case 5: iwAmax = mpcwPosCountPrev[5]; iwAmin = mpcwNegCountPrev[5]; break;

    case 6: iwAmax = mpcwPosCountPrev[9]; iwAmin = mpcwNegCountPrev[9]; break;
  }

  Clear(); sprintf(szLo+3,"%5u  %-5u",iwAmax,iwAmin);
  Delay(1000);
  ShowCorrectPrev1();
}


// просмотр статистики коррекции секунд за предыдущий мес€ц
void    key_GetCorrectPrev(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      LoadSlide(pszGetCorrectPrev);
      Clear();

      ibX = 0;
      ShowCorrectPrev1();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX > 6) ibX = 0;
      ShowCorrectPrev1();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) ibX--; else ibX = 6;
      ShowCorrectPrev1();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
      ShowCorrectPrev2();
    else
      Beep();
  }
  else Beep();
}
