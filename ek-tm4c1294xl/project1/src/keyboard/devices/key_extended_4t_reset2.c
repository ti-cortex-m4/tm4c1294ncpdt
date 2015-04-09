/*------------------------------------------------------------------------------
_EXTENDED_4T_RESET2.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "delay.h"
#include        "keyboard.h"
#include        "keyboard2.h"
#include        "programs2.h"
#include        "extended_4t.h"



extern  uchar           code    szCanalsTitle[],
                                szCanalFrom[],
                                szCanalTo[];

extern  uchar           *code   pszExt4TReset[];


//                                         0123456789ABCDEF
message          code   szMonthsTitle   = "Ìוסÿצû:         ";



void    ShowAnswerReset2(void)
{
  ShowBoolean(enKeyboard != KBD_INPUT5);
}



void    key_SetExtended4TReset2(void)
{ 
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boExt4TFlag == boTrue)
      {
        enKeyboard = KBD_SHOW;
        Clear(); 
      
        LoadSlide(pszExt4TReset); 
        szLo[0] = '.';
      }
      else BlockProgram2(wSET_EXT4T_FLAG, 0);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibXmin = GetChar(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetChar(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        enKeyboard = KBD_INPUT3;
        ShowHi(szMonthsTitle); 

        Clear(); 
        strcpy(szLo+0,szCanalFrom);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      ibYmin = GetChar(5,6) - 1;
      if (ibYmin < 12)
      {
        enKeyboard = KBD_INPUT4;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      ibYmax = GetChar(13,14) - 1;
      if ((ibYmax < 12) && (ibYmax >= ibYmin))
      {
        enKeyboard = KBD_INPUT5;

        LoadSlide(pszExt4TReset);

        Clear();
        ShowAnswerReset2();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      for (ibX=ibXmin; ibX<=ibXmax; ibX++)
        for (ibY=ibYmin; ibY<=ibYmax; ibY++)
          ResetExtended4T2(ibY,ibX);
      
      OK();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if (enKeyboard == KBD_SHOW)
      {           
        enKeyboard = KBD_INPUT1;
        fSlide = 0;

        ShowHi(szCanalsTitle);
        strcpy(szLo+0,szCanalFrom);
      }
      else
      if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
      {           
        if (enKeyboard == KBD_INPUT5)
          enKeyboard = KBD_POSTINPUT5;
        else
          enKeyboard = KBD_INPUT5;

        ShowAnswerReset2();
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
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(13,14);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(5,6);
    }
    else
    if ((enKeyboard == KBD_INPUT4) || (enKeyboard == KBD_POSTINPUT4))
    {
      enKeyboard = KBD_POSTINPUT4;
      ShiftLo(13,14);
    }
    else Beep(); 
  }
  else Beep();
}
*/
