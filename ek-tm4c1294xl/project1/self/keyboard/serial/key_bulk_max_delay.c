/*------------------------------------------------------------------------------
KEY_BULK_MAX_DELAY.C

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_program.h"
#include "../../serial/bulk.h"



#ifdef ENABLE_BULK

//                                          0123456789ABCDEF
static char const       szMessage1[]     = "Таймаут пакетной ",
                        szMessage2[]     = "    передачи     ",
                        szMessage3[]     = "     5..1000     ",
                        szMask[]         = "     ____ мс     ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



static void Show(void)
{
  Clear();
  uint w = (ulong)1000*wBulkMaxDelay/wFREQUENCY_T0;
  sprintf(szLo+5,"%4u мс", w);
}


void    key_SetBulkMaxDelay(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (fBulkEnbl == false)
      { 
        BlockProgram2(wSET_BULK_ENBL, 1);
      }
      else
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadSlide(pszMessages);
        Show();
      }
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {            
      uint w = GetIntLo(5,8);
      if ((w >= 5) && (w <= 1000))
      {
        enKeyboard = KBD_POSTENTER;

        wBulkMaxDelay = (ulong)w*wFREQUENCY_T0/1000;
        SaveCache(&chBulkMaxDelay);

        Show();
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
      ShiftLo(5,8);
    }
    else Beep(); 
  }
  else Beep();
}

#endif
