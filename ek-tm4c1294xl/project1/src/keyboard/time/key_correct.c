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

static char const       *pszCorrectCurr[] = { szCorrect, szCurrMonth, "" },
                        *pszCorrectPrev[] = { szCorrect, szPrevMonth, "" };



// вывод статистики коррекции секунд за текущий мес€ц
void    ShowCorrectCurr1(void)
{
  uint wPos, wNeg;

  switch (ibX)
  {
    case 0: ShowLo(szCorrTotal);   wPos = mpcwPosValueCurr[0]; wNeg = mpcwNegValueCurr[0]; break;
    case 1: ShowLo(szCorrGPS);     wPos = mpcwPosValueCurr[1]; wNeg = mpcwNegValueCurr[1]; break;
    case 2: ShowLo(szCorrKey);     wPos = mpcwPosValueCurr[2]; wNeg = mpcwNegValueCurr[2]; break;
    case 3: ShowLo(szCorrCRC);     wPos = mpcwPosValueCurr[3]; wNeg = mpcwNegValueCurr[3]; break;
    case 4: ShowLo(szCorrEscK_hi); wPos = mpcwPosValueCurr[4]; wNeg = mpcwNegValueCurr[4]; break;
    case 5: ShowLo(szCorrEscK_lo); wPos = mpcwPosValueCurr[5]; wNeg = mpcwNegValueCurr[5]; break;

    case 6: ShowLo(szCorrSMK);     wPos = mpcwPosValueCurr[9]; wNeg = mpcwNegValueCurr[9]; break;
  }

  Delay(1000); Clear();
  sprintf(szLo+1,"+%02u.%02u  -%02u.%02u",
                 (uchar)(wPos / 60),
                 (uchar)(wPos % 60),
                 (uchar)(wNeg / 60),
                 (uchar)(wNeg % 60));
}


// вывод статистики коррекции секунд за текущий мес€ц
void    ShowCorrectCurr2(void)
{
  uint wPos, wNeg;

  switch (ibX)
  {
    case 0: wPos = mpcwPosCountCurr[0]; wNeg = mpcwNegCountCurr[0]; break;
    case 1: wPos = mpcwPosCountCurr[1]; wNeg = mpcwNegCountCurr[1]; break;
    case 2: wPos = mpcwPosCountCurr[2]; wNeg = mpcwNegCountCurr[2]; break;
    case 3: wPos = mpcwPosCountCurr[3]; wNeg = mpcwNegCountCurr[3]; break;
    case 4: wPos = mpcwPosCountCurr[4]; wNeg = mpcwNegCountCurr[4]; break;
    case 5: wPos = mpcwPosCountCurr[5]; wNeg = mpcwNegCountCurr[5]; break;

    case 6: wPos = mpcwPosCountCurr[9]; wNeg = mpcwNegCountCurr[9]; break;
  }

  Clear(); sprintf(szLo+3,"%5u  %-5u",wPos,wNeg);
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

      LoadSlide(pszCorrectCurr);
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
  uint wPos, wNeg;

  switch (ibX)
  {
    case 0: ShowLo(szCorrTotal);   wPos = mpcwPosValuePrev[0]; wNeg = mpcwNegValuePrev[0]; break;
    case 1: ShowLo(szCorrGPS);     wPos = mpcwPosValuePrev[1]; wNeg = mpcwNegValuePrev[1]; break;
    case 2: ShowLo(szCorrKey);     wPos = mpcwPosValuePrev[2]; wNeg = mpcwNegValuePrev[2]; break;
    case 3: ShowLo(szCorrCRC);     wPos = mpcwPosValuePrev[3]; wNeg = mpcwNegValuePrev[3]; break;
    case 4: ShowLo(szCorrEscK_hi); wPos = mpcwPosValuePrev[4]; wNeg = mpcwNegValuePrev[4]; break;
    case 5: ShowLo(szCorrEscK_lo); wPos = mpcwPosValuePrev[5]; wNeg = mpcwNegValuePrev[5]; break;

    case 6: ShowLo(szCorrSMK);     wPos = mpcwPosValuePrev[9]; wNeg = mpcwNegValuePrev[9]; break;
  }

  Delay(1000); Clear();
  sprintf(szLo+1,"+%02u.%02u  -%02u.%02u",
                 (uchar)(wPos / 60),
                 (uchar)(wPos % 60),
                 (uchar)(wNeg / 60),
                 (uchar)(wNeg % 60));
}


// вывод статистики коррекции секунд за предыдущий мес€ц
void    ShowCorrectPrev2(void)
{
  uint wPos, wNeg;

  switch (ibX)
  {
    case 0: wPos = mpcwPosCountPrev[0]; wNeg = mpcwNegCountPrev[0]; break;
    case 1: wPos = mpcwPosCountPrev[1]; wNeg = mpcwNegCountPrev[1]; break;
    case 2: wPos = mpcwPosCountPrev[2]; wNeg = mpcwNegCountPrev[2]; break;
    case 3: wPos = mpcwPosCountPrev[3]; wNeg = mpcwNegCountPrev[3]; break;
    case 4: wPos = mpcwPosCountPrev[4]; wNeg = mpcwNegCountPrev[4]; break;
    case 5: wPos = mpcwPosCountPrev[5]; wNeg = mpcwNegCountPrev[5]; break;

    case 6: wPos = mpcwPosCountPrev[9]; wNeg = mpcwNegCountPrev[9]; break;
  }

  Clear(); sprintf(szLo+3,"%5u  %-5u",wPos,wNeg);
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

      LoadSlide(pszCorrectPrev);
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
