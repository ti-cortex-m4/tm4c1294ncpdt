/*------------------------------------------------------------------------------
KEY_CORRECT,C

 ѕросмотр статистики коррекции времени за текущий и предыдущий мес€цы
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_correct1.h"
#include "../../console.h"
#include "../../time/correct1.h"



//                                         0123456789ABCDEF
static char const       szCorrect[]     = " оррекци€ секунд",
                        szCurrMonth[]   = "за текущий мес€ц",
                        szPrevMonth[]   = "за прошлый мес€ц",
                        szTotal[]       = "      всего     ",
                        szGPS[]         = "   с часов GPS  ",
                        szKey[]         = "  с клавиатуры  ",
                        szCRC[]         = " по системе CRC ",
                        szEsc_K[]       = "по запросу Esc K",
                        szEsc_k[]       = "по системе Esc k",
                        szSMK[]         = "   с —»ћЁ -48   ";

static char const       *pszCorrectCurr[] = { szCorrect, szCurrMonth, "" },
                        *pszCorrectPrev[] = { szCorrect, szPrevMonth, "" };



static void ShowCorrectValueCurr(uchar  i)
{
  uint wPos, wNeg;

  switch (i)
  {
    case 0: ShowLo(szTotal); wPos = Correct1.mpwPosValueCurr[0]; wNeg = Correct1.mpwNegValueCurr[0]; break;
    case 1: ShowLo(szGPS);   wPos = Correct1.mpwPosValueCurr[1]; wNeg = Correct1.mpwNegValueCurr[1]; break;
    case 2: ShowLo(szKey);   wPos = Correct1.mpwPosValueCurr[2]; wNeg = Correct1.mpwNegValueCurr[2]; break;
    case 3: ShowLo(szCRC);   wPos = Correct1.mpwPosValueCurr[3]; wNeg = Correct1.mpwNegValueCurr[3]; break;
    case 4: ShowLo(szEsc_K); wPos = Correct1.mpwPosValueCurr[4]; wNeg = Correct1.mpwNegValueCurr[4]; break;
    case 5: ShowLo(szEsc_k); wPos = Correct1.mpwPosValueCurr[5]; wNeg = Correct1.mpwNegValueCurr[5]; break;

    case 6: ShowLo(szSMK);   wPos = Correct1.mpwPosValueCurr[9]; wNeg = Correct1.mpwNegValueCurr[9]; break;
  }

  Delay(1000);

  Clear();
  sprintf(szLo+1,"+%02u.%02u  -%02u.%02u",
                 (uchar)(wPos / 60),
                 (uchar)(wPos % 60),
                 (uchar)(wNeg / 60),
                 (uchar)(wNeg % 60));
}


static void ShowCorrectCountCurr(uchar  i)
{
  uint wPos, wNeg;

  switch (i)
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
  sprintf(szLo+3,"%5u  %-5u", wPos, wNeg);

  Delay(1000);
  ShowCorrectValueCurr(i);
}


void    key_GetCorrectCurr(void)
{
static uchar i;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      LoadSlide(pszCorrectCurr);
      Clear();

      i = 0;
      ShowCorrectValueCurr(i);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++i > 6) i = 0;
      ShowCorrectValueCurr(i);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (i > 0) i--; else i = 6;
      ShowCorrectValueCurr(i);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
      ShowCorrectCountCurr(i);
    else
      Beep();
  }
  else Beep();
}



static void ShowCorrectValuePrev(uchar  i)
{
  uint wPos, wNeg;

  switch (i)
  {
    case 0: ShowLo(szTotal); wPos = Correct1.mpwPosValuePrev[0]; wNeg = Correct1.mpwNegValuePrev[0]; break;
    case 1: ShowLo(szGPS);   wPos = Correct1.mpwPosValuePrev[1]; wNeg = Correct1.mpwNegValuePrev[1]; break;
    case 2: ShowLo(szKey);   wPos = Correct1.mpwPosValuePrev[2]; wNeg = Correct1.mpwNegValuePrev[2]; break;
    case 3: ShowLo(szCRC);   wPos = Correct1.mpwPosValuePrev[3]; wNeg = Correct1.mpwNegValuePrev[3]; break;
    case 4: ShowLo(szEsc_K); wPos = Correct1.mpwPosValuePrev[4]; wNeg = Correct1.mpwNegValuePrev[4]; break;
    case 5: ShowLo(szEsc_k); wPos = Correct1.mpwPosValuePrev[5]; wNeg = Correct1.mpwNegValuePrev[5]; break;

    case 6: ShowLo(szSMK);   wPos = Correct1.mpwPosValuePrev[9]; wNeg = Correct1.mpwNegValuePrev[9]; break;
  }

  Delay(1000);

  Clear();
  sprintf(szLo+1,"+%02u.%02u  -%02u.%02u",
                 (uchar)(wPos / 60),
                 (uchar)(wPos % 60),
                 (uchar)(wNeg / 60),
                 (uchar)(wNeg % 60));
}


static void ShowCorrectCountPrev(uchar  i)
{
  uint wPos, wNeg;

  switch (i)
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
  sprintf(szLo+3,"%5u  %-5u", wPos, wNeg);

  Delay(1000);
  ShowCorrectValuePrev(i);
}


void    key_GetCorrectPrev(void)
{
static uchar i;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      LoadSlide(pszCorrectPrev);
      Clear();

      i = 0;
      ShowCorrectValuePrev(i);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++i > 6) i = 0;
      ShowCorrectValuePrev(i);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (i > 0) i--; else i = 6;
      ShowCorrectValuePrev(i);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if (enKeyboard == KBD_POSTENTER)
      ShowCorrectCountPrev(i);
    else
      Beep();
  }
  else Beep();
}
