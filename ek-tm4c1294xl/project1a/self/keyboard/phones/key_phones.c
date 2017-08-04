/*------------------------------------------------------------------------------
KEY_PHONES,C

 Задание и просмотр номеров телефонов
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_phones.h"
#include "../../memory/mem_ports.h"
#include "../../digitals/phones.h"



//                                         0123456789ABCDEF
static char const       szPhones[]      = "Телефоны        ",
                        szMask[]        = "_____________";


static uchar            ibCan, ibPos;



static void Show(void)
{
  Clear();
  strcpy(szLo, mpphPhones[ibCan].szLine);
  sprintf(szLo+14,"%2u",ibCan+1);
}



static void Mask(void)
{
  enKeyboard = KBD_INPUT2;
  ShowLo(szMask);

  ibPos = 0;
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

        memset((char *)mpphPhones[ibCan].szLine, 0, sizeof(line));
        strncpy((char *)mpphPhones[ibCan].szLine, szLo, ibPos);

        SaveCache(&chPhones);
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
    if (enKeyboard == KBD_POSTINPUT2)
    {
      if (ibPos == 1)
        szLo[ibPos++] = 'W';
      else
        Beep();
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

      if (ibPos < bLINE_SIZE)
        szLo[ibPos++] = szDigits[bKey];
      else
        Beep();
    }
    else Beep(); 
  }
  else Beep();
}
