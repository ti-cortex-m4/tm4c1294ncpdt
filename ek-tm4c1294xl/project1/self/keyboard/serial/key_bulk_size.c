/*------------------------------------------------------------------------------
_SIZE_BULK.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "display.h"
#include        "keyboard.h"
#include        "keyboard2.h"
#include        "programs2.h"
#include        "bulk.h"



#ifdef  BULK

//                                         0123456789ABCDEF
message         code    szSizeBulk1     = "Размер пакетной ",
                        szSizeBulk2     = "    передачи    ",
                        szSizeBulk3     = "     1..250     ",
                        szMaskSizeBulk  = "      ___       ";
                        
uchar           *code   pszSizeBulk[] = { szSizeBulk1, szSizeBulk2, szSizeBulk3, "" };



void    ShowSizeBulk(void)
{
  Clear();
  sprintf(szLo+6,"%3bu",bMaxBulk);
}


void    key_SetSizeBulk(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boEnableBulk == boFalse)
        BlockProgram2(wSET_BULK_ENBL, 1);
      else
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        LoadSlide(pszSizeBulk); 
        ShowSizeBulk();
      }
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetChar(6,8);
      if ((ibX > 0) && (ibX <= 250))
      {
        bMaxBulk = ibX;

        ShowSizeBulk();
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskSizeBulk);        
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
        ShowLo(szMaskSizeBulk);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
    else Beep(); 
  }
  else Beep();
}

#endif
*/
