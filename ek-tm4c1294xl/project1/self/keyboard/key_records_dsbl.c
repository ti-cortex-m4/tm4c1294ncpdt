/*------------------------------------------------------------------------------
KEY_RECORDS_DSBL!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_records.h"
#include "../flash/records_dsbl.h"
#include "../nvram/cache.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "  Разрешенные   ",
                        szMessage2[]     = "    события     ",
                        szMask[]         = "   номер ?___   ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



static void Show(uint iwRec)
{
  Clear();
  sprintf(szLo+13,"%3u",iwRec);

  if (mpfRecordDsbl[iwRec] == false)
    strcpy(szLo+8,szYes);
  else         
    strcpy(szLo+8,szNo);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetRecordsDsbl(void)
{
static uint iwRec;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      LoadSlide(pszMessages);

      ShowLo(szMask);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      iwRec = 0;
      Show(iwRec);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((iwRec = GetIntLo(10,12)) <= 255)
      {
        enKeyboard = KBD_POSTENTER;
        Show(iwRec);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++iwRec > 255) iwRec = 0;
      Show(iwRec);
    }
  }


  else if (bKey == bKEY_MINUS)
  {
    if (iwRec > 0) iwRec--; else iwRec = 255;
    Show(iwRec);
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if (enKeyboard == KBD_POSTENTER)
      {
        mpfRecordDsbl[iwRec] = InvertBoolean(mpfRecordDsbl[iwRec]);
        Show(iwRec);
        SaveCache(&chRecordDsbl);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,12);
    }
    else Beep(); 
  }
  else Beep();
}
