/*------------------------------------------------------------------------------
KEY_ADDRESSES!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_records.h"
#include "../../display/display.h"
#include "../keyboard.h"
#include "../../digitals/digitals.h"
#include "../../nvram/cache.h"
#include "../../flash/records.h"



//                                           0123456789ABCDEF
static char const       szAddresses[]     = "Адреса          ",
                        szMaskAddresses[] = "________",
                        szNullAddresses[] = "        ";
                      


static void Show(uchar  ibCan)
{
  Clear();

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    sprintf(szHi+8,"%8lu",mpdwAddress1[ibCan]);
    sprintf(szLo+8,"%8lu",mpdwAddress2[ibCan]);
  }
  else
  {
    sprintf(szHi+8,"%8lu",mpdwAddress1[ibCan]);
    sprintf(szLo+8,"********");
  }

  sprintf(szLo,"%2u",ibCan+1);
}



void    key_SetAddresses(void)
{
static uchar ibCan;

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

      ibCan = 0;
      Show(ibCan);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibCan = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show(ibCan);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibCan >= bCANALS) ibCan = 0;
      Show(ibCan);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      ulong dw;
      if ((dw = GetLongLo(8,15)) <= 100000000)
      {
        enKeyboard = KBD_POSTENTER;

        ibRecordCan = ibCan;
        AddSysRecordReprogram(EVE_EDIT_ADDRESS20);
        mpdwAddress2[ibCan] = dw;
        SaveCache(&chAddress2);
        AddSysRecordReprogram(EVE_EDIT_ADDRESS21);

        if (++ibCan >= bCANALS) ibCan = 0;
        Show(ibCan);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibCan > 0) ibCan--; else ibCan = bCANALS-1;

      Show(ibCan);
    } 
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ulong dw;
      if ((dw = GetLongHi(8,15)) <= 100000000)
      {
        enKeyboard = KBD_INPUT3;
        sprintf(szLo+8,szMaskAddresses);

        ibRecordCan = ibCan;
        AddSysRecordReprogram(EVE_EDIT_ADDRESS10);
        mpdwAddress1[ibCan] = dw;
        SaveCache(&chAddress1);
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

