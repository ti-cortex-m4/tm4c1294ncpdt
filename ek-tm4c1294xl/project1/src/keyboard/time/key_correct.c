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
    case 0: ShowLo(szCorrTotal);   wPos = Correct1.mpwPosValueCurr[0]; wNeg = Correct1.mpwNegValueCurr[0]; break;
    case 1: ShowLo(szCorrGPS);     wPos = Correct1.mpwPosValueCurr[1]; wNeg = Correct1.mpwNegValueCurr[1]; break;
    case 2: ShowLo(szCorrKey);     wPos = Correct1.mpwPosValueCurr[2]; wNeg = Correct1.mpwNegValueCurr[2]; break;
    case 3: ShowLo(szCorrCRC);     wPos = Correct1.mpwPosValueCurr[3]; wNeg = Correct1.mpwNegValueCurr[3]; break;
    case 4: ShowLo(szCorrEscK_hi); wPos = Correct1.mpwPosValueCurr[4]; wNeg = Correct1.mpwNegValueCurr[4]; break;
    case 5: ShowLo(szCorrEscK_lo); wPos = Correct1.mpwPosValueCurr[5]; wNeg = Correct1.mpwNegValueCurr[5]; break;

    case 6: ShowLo(szCorrSMK);     wPos = Correct1.mpwPosValueCurr[9]; wNeg = Correct1.mpwNegValueCurr[9]; break;
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
    case 0: wPos = Correct1.mpwPosCountCurr[0]; wNeg = Correct1.mpwNegCountCurr[0]; break;
    case 1: wPos = Correct1.mpwPosCountCurr[1]; wNeg = Correct1.mpwNegCountCurr[1]; break;
    case 2: wPos = Correct1.mpwPosCountCurr[2]; wNeg = Correct1.mpwNegCountCurr[2]; break;
    case 3: wPos = Correct1.mpwPosCountCurr[3]; wNeg = Correct1.mpwNegCountCurr[3]; break;
    case 4: wPos = Correct1.mpwPosCountCurr[4]; wNeg = Correct1.mpwNegCountCurr[4]; break;
    case 5: wPos = Correct1.mpwPosCountCurr[5]; wNeg = Correct1.mpwNegCountCurr[5]; break;

    case 6: wPos = Correct1.mpwPosCountCurr[9]; wNeg = Correct1.mpwNegCountCurr[9]; break;
  }

  Clear();
  sprintf(szLo+3,"%5u  %-5u",wPos,wNeg);

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
    case 0: ShowLo(szCorrTotal);   wPos = Correct1.mpwPosValuePrev[0]; wNeg = Correct1.mpwNegValuePrev[0]; break;
    case 1: ShowLo(szCorrGPS);     wPos = Correct1.mpwPosValuePrev[1]; wNeg = Correct1.mpwNegValuePrev[1]; break;
    case 2: ShowLo(szCorrKey);     wPos = Correct1.mpwPosValuePrev[2]; wNeg = Correct1.mpwNegValuePrev[2]; break;
    case 3: ShowLo(szCorrCRC);     wPos = Correct1.mpwPosValuePrev[3]; wNeg = Correct1.mpwNegValuePrev[3]; break;
    case 4: ShowLo(szCorrEscK_hi); wPos = Correct1.mpwPosValuePrev[4]; wNeg = Correct1.mpwNegValuePrev[4]; break;
    case 5: ShowLo(szCorrEscK_lo); wPos = Correct1.mpwPosValuePrev[5]; wNeg = Correct1.mpwNegValuePrev[5]; break;

    case 6: ShowLo(szCorrSMK);     wPos = Correct1.mpwPosValuePrev[9]; wNeg = Correct1.mpwNegValuePrev[9]; break;
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
    case 0: wPos = Correct1.mpwPosCountPrev[0]; wNeg = Correct1.mpwNegCountPrev[0]; break;
    case 1: wPos = Correct1.mpwPosCountPrev[1]; wNeg = Correct1.mpwNegCountPrev[1]; break;
    case 2: wPos = Correct1.mpwPosCountPrev[2]; wNeg = Correct1.mpwNegCountPrev[2]; break;
    case 3: wPos = Correct1.mpwPosCountPrev[3]; wNeg = Correct1.mpwNegCountPrev[3]; break;
    case 4: wPos = Correct1.mpwPosCountPrev[4]; wNeg = Correct1.mpwNegCountPrev[4]; break;
    case 5: wPos = Correct1.mpwPosCountPrev[5]; wNeg = Correct1.mpwNegCountPrev[5]; break;

    case 6: wPos = Correct1.mpwPosCountPrev[9]; wNeg = Correct1.mpwNegCountPrev[9]; break;
  }

  Clear();
  sprintf(szLo+3,"%5u  %-5u",wPos,wNeg);

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
