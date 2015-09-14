/*------------------------------------------------------------------------------
KEY_BULK_DELAY.C

 
------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "keyboard2.h"
#include        "programs2.h"
#include        "bulk.h"



#ifdef  BULK

//                                          0123456789ABCDEF
message         code    szDelayBulk1     = "Таймаут пакетной ",
                        szDelayBulk2     = "    передачи     ",
                        szDelayBulk3     = "     1..1000     ",
                        szMaskDelayBulk  = "     ____ мс     ";

uchar           *code   pszDelayBulk[]   = { szDelayBulk1, szDelayBulk2, szDelayBulk3, "" };
                      


void    ShowDelayBulk(void)
{
  Clear();
  iwA = (ulong)1000*wMaxBulkDelay/wFREQUENCY_T0;
  sprintf(szLo+5,"%4u мс", iwA);
}



void    key_SetBulkDelay(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boEnableBulk == boFalse)
      { 
        BlockProgram2(wSET_BULK_ENBL, 1);
      }
      else
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadSlide(pszDelayBulk); 
        ShowDelayBulk();
      }
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {            
      iwA = GetLong(5,8);
      if ((iwA > 0) && (iwA <= 1000))
      {
        enKeyboard = KBD_POSTENTER;

        wMaxBulkDelay = (ulong)iwA*wFREQUENCY_T0/1000;
        ShowDelayBulk();
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskDelayBulk);        
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
        ShowLo(szMaskDelayBulk);
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
*/
