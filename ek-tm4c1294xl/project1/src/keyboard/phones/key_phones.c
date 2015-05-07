/*------------------------------------------------------------------------------
KEY_PHONES.C

 Задание и просмотр номеров телефонов
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_phones.h"
#include "../../memory/mem_ports.h"
#include "../../display/display.h"
#include "../keyboard.h"
#include "../../digitals/phones.h"
#include "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szPhones[]      = "Телефоны        ",
                        szMaskPhones[]  = "_____________";



void    ShowPhones(void)
{
  Clear();
  strcpy(szLo, mpphPhones[ibX].szNumber);

  sprintf(szLo+14,"%2u",ibX+1);
}



void    ShowMaskPhones(void)
{
  enKeyboard = KBD_INPUT2;
  ShowLo(szMaskPhones);

  ibY = 0;
}



void    key_SetPhones(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Number();

      ShowHi(szPhones);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowPhones();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowPhones();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) 
        ibX = 0;

      ShowPhones();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {      
      if (ibY > 0)
      {
        enKeyboard = KBD_POSTENTER;

        szLo[ibY] = 0;
        strcpy((char *)mpphPhones[ibX].szNumber, szLo);
        SaveFile(&flPhones);
      }

      if (enKeyboard == KBD_POSTENTER)
      {
        if (++ibX >= bCANALS) 
          ibX = 0;

        ShowPhones();
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
        ShowMaskPhones();
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT2)
    {
      if (ibY == 1)
        szLo[ibY++] = 'W';
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
        ShowMaskPhones();
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

      if (ibY < bPHONE_SIZE)
        szLo[ibY++] = szDigits[bKey];
      else Beep();
    }
    else Beep(); 
  }
  else Beep();
}

