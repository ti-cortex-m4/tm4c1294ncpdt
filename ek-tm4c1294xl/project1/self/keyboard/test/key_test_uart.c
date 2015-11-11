/*------------------------------------------------------------------------------
KEY_TEST_UART!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
//#include "../../memory/mem_realtime.h"
//#include "../../memory/mem_digitals.h"
//#include "../keyboard.h"
//#include "../../display/display.h"
//#include "../../digitals/digitals.h"
//#include "../../digitals/digitals_messages.h"
//#include "../../serial/ports.h"
//#include "../../serial/modems.h"
#include "key_test_uart.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Тест UART       ",
                        szMessage2[]    = "    тест ?__    ";


static void GetTest0(void)
{
}


static void GetTest1(void)
{
}


static void GetTest2(void)
{
}


static void GetTest(uchar  ibX)
{
  sprintf(szHi+15,"%u",ibX+1); Clear();
  switch (ibX)
  {
    case 0:  GetTest0();  break;
    case 1:  GetTest1();  break;
    case 2:  GetTest2();  break;
  }
}



void    key_TestUART(void)
{
static uchar i;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szMessage1);
      ShowLo(szMessage2);
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      i = 0;
      GetTest(i);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((i = GetChar(10,11) - 1) < 3)
      {
        enKeyboard = KBD_POSTENTER;
        GetTest(i);
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

