/*------------------------------------------------------------------------------
KEY_EXT_41.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"



//                                         0123456789ABCDEF
message         code    szExtended410   = " —писок каналов ",
                code    szExtended411   = "  дл€ загрузки  ",
                code    szExtended412   = "знач. счетчиков ",
                code    szExtended413   = "   по мес€цам   ";

uchar           *code   pszExtended41[] = { szExtended410, szExtended411, szExtended412, szExtended413, "" };



void    ShowExtended41(void)
{
  Clear();
  sprintf(szLo+14,"%2bu",ibX+1);

  if (mpEnblCan4[ibX] == boFalse) 
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetExt41(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt4Flag == boTrue)
      {
        enKeyboard = KBD_INPUT1;
        LoadSlide(pszExtended41);

        Canal();
      }
      else BlockProgram(bSET_EXT4_FLAG);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowExtended41();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowExtended41();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      ShowExtended41();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if (enKeyboard == KBD_POSTENTER)
      {
        mpEnblCan4[ibX] = ~mpEnblCan4[ibX];      
        ShowExtended41();
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
      ShiftLo(10,11);
    }
    else Beep(); 
  }
  else Beep();
}
*/
