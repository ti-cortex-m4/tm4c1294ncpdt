/*------------------------------------------------------------------------------
KEY_ADDRESSES.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../display/display.h"
#include        "../keyboard.h"
#include        "../../digitals/digitals.h"
#include        "../../flash/files.h"
#include        "../../flash/records.h"



//                                           0123456789ABCDEF
static char const       szAddresses[]     = "Адреса          ",
                        szMaskAddresses[] = "________",
                        szNullAddresses[] = "        ";
                      


void    ShowAddresses(void)
{
  Clear();

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    sprintf(szHi+8,"%8lu",mpdwAddress1[ibX]);
    sprintf(szLo+8,"%8lu",mpdwAddress2[ibX]);
  }
  else
  {
    sprintf(szHi+8,"%8lu",mpdwAddress1[ibX]);
    sprintf(szLo+8,"********");
  }

  sprintf(szLo,"%2u",ibX+1);
}



void    key_SetAddresses(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Number();

      ShowHi(szAddresses);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowAddresses();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowAddresses();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;
      ShowAddresses();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      ulong dw;
      if ((dw = GetLongLo(8,15)) <= 100000000)
      {
        enKeyboard = KBD_POSTENTER;

        AddSysRecordReprogram(EVE_EDIT_ADDRESS20);
        mpdwAddress2[ibX] = dw;
        SaveFile(&flAddress2);
        AddSysRecordReprogram(EVE_EDIT_ADDRESS21);

        if (++ibX >= bCANALS) ibX = 0;
        ShowAddresses();
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) 
        ibX--; 
      else 
        ibX = bCANALS-1;

      ShowAddresses();
    } 
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ulong dw;
      if ((dw = GetLongHi(8,15)) <= 100000000)
      {
        enKeyboard = KBD_INPUT3;
        sprintf(szLo+8,szMaskAddresses);

        AddSysRecordReprogram(EVE_EDIT_ADDRESS10);
        mpdwAddress1[ibX] = dw;
        SaveFile(&flAddress1);
        AddSysRecordReprogram(EVE_EDIT_ADDRESS11);
      }
      else Beep();
    }
    else Beep();
  } 


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
      {
        enKeyboard = KBD_INPUT2;
        sprintf(szHi+8,szMaskAddresses);
        sprintf(szLo+8,szNullAddresses);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftHi(8,15);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(8,15);
    }
    else Beep(); 
  }
  else Beep();
}

