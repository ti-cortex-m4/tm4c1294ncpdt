/*------------------------------------------------------------------------------
key_auto_flow.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../serial/auto_flow.h"
#include "key_auto_flow.h"



//                                          0123456789ABCDEF
static char const       szMessage[]      = "Авто-транзит ?  ",
                        szMask[]         = "     __ __      ";

static char const       *pszMessages[]   = { szMessage, "" };



static void ShowDate(time  ti)
{
  sprintf(szLo+5,"%02u.%02u",
                 ti.bDay,
                 ti.bMonth);
}


void    key_SetAutoFlow(void)
{
static time tiT;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      LoadSlide(pszMessages);
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      tiT.bDay = GetCharLo(5,6);

      if ((tiT.bDay > 0) && (tiT.bDay <= 31))
      {
        enKeyboard = KBD_INPUT2;
        szLo[7] = '.';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      tiT.bMonth = GetCharLo(8,9);
      tiT.bYear  = GetCurrTimeDate()->bYear;

      if ((tiT.bMonth >= 1) && (tiT.bMonth <= 12))
      {
        if (tiT.bDay <= GetDaysInMonthYM(tiT.bYear, tiT.bMonth))
        {
          enKeyboard = KBD_POSTENTER;

          switch (wProgram)
          {
            case bSET_SUMMER:  tiSummer = tiT; SaveCache(&chSummer); ShowDate(tiSummer);  break;
            case bSET_WINTER:  tiWinter = tiT; SaveCache(&chWinter); ShowDate(tiWinter);  break;
          }
        }
        else
        {  
          enKeyboard = KBD_INPUT1;
          LongBeep();

          ShowLo(szMask);
        }
      }
      else Beep();
    }
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMask);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(8,9);
    }
  }
  else Beep();
}
