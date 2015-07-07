/*------------------------------------------------------------------------------
KEY_KEYS,C

 Задание и просмотр паролей счетчиков №1
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_records.h"
#include "../../digitals/digitals.h"
#include "../../flash/records.h"



//                                         0123456789ABCDEF
static char const       szKeys[]        = "Пароли          ",
                        szMask[]        = "_____________";


static uchar            ibCan, ibPos;



static void Show(void)
{
  Clear();

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
    strcpy(szLo, mpphKeys[ibCan].szNumber);
  else
    strcpy(szLo, "*************");

  sprintf(szLo+14,"%2u",ibCan+1);
}



static void Mask(void)
{
  enKeyboard = KBD_INPUT2;
  ShowLo(szMask);

  ibPos = 0;
}



void    key_SetKeys(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boEnblKeys != true)
      {
        BlockProgram(bSET_ENBL_KEYS);
        return;
      }
      else
      {
        enKeyboard = KBD_INPUT1;
        Canal();

        ShowHi(szKeys);
      }
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibCan = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibCan = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibCan >= bCANALS) ibCan = 0;

      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {      
      if (ibPos > 0)
      {
        enKeyboard = KBD_POSTENTER;

        szLo[ibPos] = 0;

        ibRecordCan = ibCan;
        AddSysRecordReprogram(EVE_EDIT_KEY10);
        AddSysRecordReprogram(EVE_EDIT_KEY11);

        strcpy((char *)mpphKeys[ibCan].szNumber, szLo);
        SaveFile(&flKeys);

        AddSysRecordReprogram(EVE_EDIT_KEY20);
        AddSysRecordReprogram(EVE_EDIT_KEY21);
      }

      if (enKeyboard == KBD_POSTENTER)
      {
        if (++ibCan >= bCANALS) ibCan = 0;

        Show();
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_POSTINPUT2))
    {
      if (enGlobal != GLB_WORK)
        Mask();
      else
        Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibCan > 0) ibCan--; else  ibCan = bCANALS-1;

      Show();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
        Mask();
      else
        Beep();
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

      if (ibPos < bPHONE_SIZE)
        szLo[ibPos++] = szDigits[bKey];
      else
        Beep();
    }
    else Beep(); 
  }
  else Beep();
}
